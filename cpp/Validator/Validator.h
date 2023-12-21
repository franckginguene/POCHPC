#pragma once

#include <filesystem>
#include <Eigen/Eigen>
#include <iostream>
#include <vector>

class Validator
{
protected:
	/**
		* @brief Structure pour le stockage des erreurs
	*/
	struct Errors
	{
		double meanRelativeError;
		double meanAbsoluteError;
		double maxRelativeError;
		double maxAbsoluteError;
	};

public:
	/**
	* @brief Status du validator
	*/
	enum class Status
	{
		Ready,
		Running,
		Error
	};

private:
	/**
		* @brief Constructeur privé pour empêcher l'instanciation directe
	*/
	Validator() {};

public:
	/**
		* @brief Fonction statique pour obtenir l'instance unique
	*/
	static Validator& getInstance() {
		static Validator validatorUniqueInstance; // Création unique de l'instance lors du premier appel
		return validatorUniqueInstance;
	}
	// Supprimer les fonctions de copie et d'affectation pour garantir l'unicité
	Validator(const Validator&) = delete;
	Validator& operator=(const Validator&) = delete;

public:
	/**
		* @brief Comparaison Matlab-C++ de tableaux de flottants
		* Les fichiers cpp sont nommés dump_cpp
		* Les fichiers matlab sont nommés dump_mat
		* @param [in] dumpPath		Path pour les fichiers de dump
		* @param [in] arraysList	Liste des vecteurs à tester
	*/
	void compareArrays(	const std::filesystem::path& dumpFilePath,
						const std::list<const Eigen::ArrayXd*>& arraysList);
protected:
	/**
	 * @brief Vérification de l'intégrité de la liste de tableaux
	 * @param [in] Liste de tableau à vérifier
	 */
	[[nodiscard]] bool checkArraysListCoherence(const std::list<const Eigen::ArrayXd*>& arraysList);

	/**
	 * @brief Generation du fichier de dump C++
	 * @param cppFile Nom du fichier C++
	 * @param pvectorList Ensemble des QVector vecteurs
	 */
	void generateCppDumpFile(	const std::filesystem::path& dumpFilePath,
								const std::list<const Eigen::ArrayXd*>& arraysList);

	/**
	 * @brief Comparaison des fichiers de validation
	 * @param cppFile Nom du fichier C++
	 * @param matlabFile Nom du fichier Matlab
	 * @param pvectorList Ensemble des vecteurs
	 */
	void compareDumpFiles(	const std::filesystem::path& cppFilePath,
							const std::filesystem::path& matlabFilePath,
							const std::list<const Eigen::ArrayXd*>& arraysList);
	
	/**
	 * @brief Impression des resultats dans un fichier
	 * @param validationFile Nom du fichier de validation
	 * @param casTest string contenant le nom du cas-test
	 * @param pvectorList Ensemble des vecteurs
	 */
	void writeResultsFile(	const std::filesystem::path& cppFilePath,
							const std::list<const Eigen::ArrayXd*>& arraysList);

	/**
	 * @brief Impression d'une entête pour les fichiers de résultats
	 */
	void printHeader(std::ofstream& resultsFile);

public:
	[[nodiscard]] const std::string& getErrorMessage() const noexcept { return m_errorMessage; };
	[[nodiscard]] const std::vector<Errors>& getErrors() const noexcept { return m_errors; };
	[[nodiscard]] const Status& getStatus() const noexcept { return m_status; };

protected:
	Status m_status = Status::Ready;
	std::string m_errorMessage;
	std::vector<Errors> m_errors;
	const std::string m_cppFileName = "dump_cpp";
	const std::string m_matlabFileName = "dump_mat";
	const std::string m_resultsFileName = "results.txt";
};
