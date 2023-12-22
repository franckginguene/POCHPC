#pragma once

#include <filesystem>
#include <iostream>
#include <vector>
#include <MDD/Types.h>

#include <proxyInclude/eigen>

/**
	* @brief Comparaison Matlab-C++ de tableaux de flottants. Matlab est considéré comme la référence
	Les dumps Matlab sont nommés dump_mat et doivent être disponibles avant d'exécuter le Validator.
	En sortie, on récupère les erreurs relatives et absolues, max et moyenne pour chacun des vecteurs.
	Note sur l'erreur relative : dans le cas où des éléments des vecteurs matlab sont inférieurs à epsilon, 
	ces éléments sont ignorés des calculs. L'erreurs relative moyenne et max est calculée sur les autres éléments.
	Si tous les éléments d'un vecteur Matlab sont inférieurs à epsilon, alors les erreurs relatives 
	moyenne et absolue valent "inf"
*/
class Validator{
	// Constructeur privé pour empêcher l'instanciation directe
	Validator(){};
	// Supprimer les fonctions de copie et d'affectation pour garantir l'unicité
	Validator(const Validator&) = delete;
	Validator& operator=(const Validator&) = delete;
public:
	static Validator instance;

	enum class Status{
		Ready,
		Running,
		Error
	};

	//! Structure pour le stockage des erreurs
	struct Errors{
		double meanRelativeError;
		double meanAbsoluteError;
		double maxRelativeError;
		double maxAbsoluteError;
	};

	/**
		* @brief Comparaison Matlab-C++ de tableaux de flottants
		* Les fichiers cpp sont nommés dump_cpp
		* Les fichiers matlab sont nommés dump_mat
		* @param [in] dumpPath		Path pour les fichiers de dump
		* @param [in] arraysList	Liste des vecteurs à tester
	*/
	void compareArrays(const std::filesystem::path& dumpFilePath,
							 std::list<Ref<const Eigen::ArrayXd> > arraysList);

	/**
	* @brief Getters
	*/
	[[nodiscard]] const std::string& errorMessage() const noexcept { return m_errorMessage; };
	[[nodiscard]] const std::vector<Errors>& errors() const noexcept { return m_errors; };
	[[nodiscard]] const Status& status() const noexcept { return m_status; };

private:
	/**
	 * @brief Vérification de l'intégrité de la liste de tableaux
	 * @param [in] Liste de tableau à vérifier
	 */
	[[nodiscard]] bool checkArraysListCoherence(std::list<Ref<const Eigen::ArrayXd>> arraysList);

	/**
	 * @brief Generation du fichier de dump C++
	 * @param cppFile Nom du fichier C++
	 * @param pvectorList Ensemble des QVector vecteurs
	 */
	void generateCppDumpFile(const std::filesystem::path& dumpFilePath,
									 std::list<Ref<const Eigen::ArrayXd>> arraysList);

	/**
	 * @brief Comparaison des fichiers de validation
	 * @param cppFile Nom du fichier C++
	 * @param matlabFile Nom du fichier Matlab
	 * @param pvectorList Ensemble des vecteurs
	 */
	void compareDumpFiles(const std::filesystem::path& cppFilePath,
								 const std::filesystem::path& matlabFilePath,
								 std::list<Ref<const Eigen::ArrayXd>> arraysList);
	
	/**
	 * @brief Impression des resultats dans un fichier
	 * @param validationFile Nom du fichier de validation
	 * @param casTest string contenant le nom du cas-test
	 * @param pvectorList Ensemble des vecteurs
	 */
	void writeResultsFile(const std::filesystem::path& cppFilePath,
								 std::list<Ref<const Eigen::ArrayXd>> arraysList);

	/**
	 * @brief Impression d'une entête pour les fichiers de résultats
	 */
	void printHeader(std::ofstream& resultsFile);

	/**
	 * @brief Membres
	 */
	Status m_status = Status::Ready;
	std::string m_errorMessage;
	std::vector<Errors> m_errors;
	const std::string m_cppFileName = "dump_cpp";
	const std::string m_matlabFileName = "dump_mat";
	const std::string m_resultsFileName = "results.txt";
};
