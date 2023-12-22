#include "Validator.h"

#include <fstream>

Validator Validator::instance={};

void Validator::compareArrays(const std::filesystem::path& dumpPath,
										std::list<Ref<const Eigen::ArrayXd> > arraysList)
{
	m_status = Status::Running;

	std::filesystem::path cppDumpFilePath = dumpPath / m_cppFileName;			//!< Chemin d'acces au fichier de dump C++
	std::filesystem::path matlabDumpFilePath = dumpPath / m_matlabFileName;		//!< Chemin d'acces au fichier de dump Matlab
	std::filesystem::path resultsFilePath = dumpPath / m_resultsFileName;		//!< Chemin d'acces au fichier de résultat

	//Verification de l'existence des donnees
	if (std::filesystem::exists(matlabDumpFilePath))
	{
		//Verification des tailles des objets
		if (checkArraysListCoherence(arraysList))
		{
			//Generation du fichier de dump cpp
			generateCppDumpFile(cppDumpFilePath, arraysList);
			if (m_status != Status::Running) return;

			//Comparaison des fichiers de dump
			compareDumpFiles(cppDumpFilePath, matlabDumpFilePath, arraysList);
			if (m_status != Status::Running) return;

			//Génération du fichier de résultat
			writeResultsFile(resultsFilePath, arraysList);
			if (m_status != Status::Running) return;

			m_status = Status::Ready;
		}
	}
	else
	{
		m_status = Status::Error;
		m_errorMessage = "The matlab dump file does not exist.";
		return;
	}
};

bool Validator::checkArraysListCoherence(std::list<Ref<const Eigen::ArrayXd> > arraysList)
{
	// Empty list
	if (arraysList.size() == 0)
	{
		m_status = Status::Error;
		m_errorMessage = "The array list is empty. Comparison process stopped.";
		return false;
	}

	// Empty Array(s)
	bool atLeastOneEmpty = std::any_of(arraysList.begin(), arraysList.end(), [](Ref<const Eigen::ArrayXd>& vec) {
		return vec->size() == 0;
	});

	if (atLeastOneEmpty)
	{
		m_status = Status::Error;
		m_errorMessage = "At least one array of the list is empty. Comparison process stopped.";
		return false;

	}
	
	return true;
};

void Validator::generateCppDumpFile(const std::filesystem::path& dumpFilePath,
												std::list<Ref<const Eigen::ArrayXd> > arraysList)
{
	// Ouvre le fichier de dump en mode binaire
	std::ofstream dumpFile(dumpFilePath, std::ios::binary);

	if (!dumpFile.is_open()) {
		m_status = Status::Error;
		m_errorMessage = "Can not open the C++ dump file. Comparison process stopped.";
		return;
	}

	// Itération sur la liste de tableaux
	for (const auto& array : arraysList) {
		// Écriture de la taille du tableau
		dumpFile << array->size();
		// Écriture des données du tableau au format binaire
		dumpFile.write(reinterpret_cast<const char*>(array->data()), array->size() * sizeof(double));
	}

	// Ferme le fichier de dump
	dumpFile.close();
};

void Validator::compareDumpFiles(const std::filesystem::path& cppFilePath,
											const std::filesystem::path& matlabFilePath,
											std::list<Ref<const Eigen::ArrayXd> > arraysList)
{
	// Ouvre les fichiers de dump
	std::ifstream cppDumpFile(cppFilePath, std::ios::binary);
	std::ifstream matlabDumpFile(matlabFilePath, std::ios::binary);

	if (!cppDumpFile.is_open() || !matlabDumpFile.is_open()) {
		// Gestion de l'erreur si l'un des fichiers ne peut pas être ouvert
		m_status = Status::Error;
		m_errorMessage = "Can not open the C++ or Matlab dump file. Comparison process stopped.";
		return;
	}

	// Réinitialiser les erreurs
	m_errors.clear();

	// Itération sur la liste de vecteurs
	for (const auto& array : arraysList) {
		// Lecture des données depuis les fichiers
		Eigen::ArrayXd cppData(array->size());
		Eigen::ArrayXd matlabData(array->size());

		// Récupération des tailles des tableaux et vérification de cohérence
		size_t cppArraySize, matlabArraySize;
		cppDumpFile >> cppArraySize;
		matlabDumpFile >> matlabArraySize;
		if (cppArraySize != matlabArraySize)
		{
			m_status = Status::Error;
			m_errorMessage = "The sizes of the C++ and Matlab arrays are inconsistent. Comparison process stopped.";

			// Ferme les fichiers de dump et sortie
			cppDumpFile.close();
			matlabDumpFile.close();
			return;
		}

		// Lectures des données des tableaux
		cppDumpFile.read(reinterpret_cast<char*>(cppData.data()), cppData.size() * sizeof(double));
		matlabDumpFile.read(reinterpret_cast<char*>(matlabData.data()), matlabData.size() * sizeof(double));

		// Calcul des erreurs relatives et absolues
		Eigen::ArrayXd absoluteError = cppData - matlabData;
		Eigen::ArrayXd relativeError = absoluteError / matlabData;

		// Calcul des valeurs maximales et moyennes des erreurs
		double maxAbsoluteError = absoluteError.abs().maxCoeff();
		double maxRelativeError = relativeError.abs().maxCoeff();
		double meanAbsoluteError = absoluteError.abs().mean();
		double meanRelativeError = relativeError.abs().mean();

		m_errors.push_back(Errors{ meanRelativeError , meanAbsoluteError, maxRelativeError, maxAbsoluteError });
	}

	// Ferme les fichiers de dump
	cppDumpFile.close();
	matlabDumpFile.close();
}

void Validator::writeResultsFile(const std::filesystem::path& resultsFilePath,
											std::list<Ref<const Eigen::ArrayXd> > arraysList)
{
	// Ouvre le fichier de résultats en mode ASCII
	std::ofstream resultsFile(resultsFilePath);

	if (!resultsFile.is_open()) {
		// Gestion de l'erreur si le fichier ne peut pas être ouvert
		m_status = Status::Error;
		m_errorMessage = "Can not open the results file. Comparison process stopped.";
		return;
	}

	// Print header
	printHeader(resultsFile);

	//Impression des erreurs
	int i = 0;
	for (auto & currentArrayErrors : m_errors)
	{
		resultsFile << "Vector : " << i++ << "\n"
			<< "max  abs. error: " << currentArrayErrors.maxAbsoluteError << "\n"
			<< "max  rel. error: " << currentArrayErrors.maxRelativeError << "\n"
			<< "mean abs. error: " << currentArrayErrors.meanAbsoluteError << "\n"
			<< "mean rel. error: " << currentArrayErrors.meanRelativeError << "\n\n";
	}
	resultsFile << "\n\nEnd of validation file";
	
	//Fermeture
	resultsFile.close();
}

void Validator::printHeader(std::ofstream& resultsFile)
{
	// Obtention du temps actuel en utilisant std::chrono
	auto currentTime = std::chrono::system_clock::now();

	// Convertir le temps actuel en format de calendrier
	std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
	std::tm* localTime = std::localtime(&currentTime_t);

	resultsFile << "/////////////////////////////////////////////\n"
				<< "// Validation file\n"
				<< "// Date: ";
	// Affichage de la date et de l'heure
	resultsFile << std::put_time(localTime, "%d-%m-%Y %H-%M-%S") << "\n";

	resultsFile << "/////////////////////////////////////////////\n\n"
				<< "Mean and maximum errors (relative and absolute) on chosen vectors : \n\n";
}
