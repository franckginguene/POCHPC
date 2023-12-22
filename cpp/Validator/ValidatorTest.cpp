#include "Validator.h"

#include <proxyInclude/gtest>

// Classe de test
class ValidatorTest : public ::testing::Test {
protected:
	// Définition des objets communs pour les tests
	void SetUp() override {
		//char* tmp = std::getenv("PROJECT_PATH");
		absoluteDataValidationPath = VALIDATOR_DATA_PATH;
	}

	// Nettoyage des ressources allouées dans SetUp
	void TearDown() override {
		// Code de nettoyage commun
	}
protected:
	std::filesystem::path absoluteDataValidationPath;
};

TEST_F(ValidatorTest, NominalCase) {
	// Chemins des fichiers de test
	auto dumpPath = std::filesystem::path(VALIDATOR_DATA_PATH) / "NominalCase";

	// Le fichier de dump Matlab contient 2 Arrays :
	// 1. 2. 3.
	// 4. 5. 6.

	// Ajoutez des vecteurs à la liste, par exemple :
	Eigen::ArrayXd array1(3);
	Eigen::ArrayXd array2(3);
	array1 << 1.1, 2.1, 3.1;
	array2 << -4.0, 5.0, 6.0;

	// Comparaison
	Validator::instance.compareArrays(dumpPath, {array1, array2});

	// Tests du status
	EXPECT_EQ(Validator::instance.status(), Validator::Status::Ready);

	// Tests sur les données
	constexpr double epsilon = std::numeric_limits<double>::epsilon();
	const auto& errors = Validator::instance.errors();
	// Premier vecteur
	EXPECT_NEAR(errors[0].maxAbsoluteError, 0.1, epsilon);
	EXPECT_NEAR(errors[0].maxRelativeError, 0.1, epsilon);
	EXPECT_NEAR(errors[0].meanAbsoluteError, 0.1, epsilon);
	EXPECT_NEAR(errors[0].meanRelativeError, 0.061111111111111165, epsilon);
	// Deuxième vecteur
	EXPECT_NEAR(errors[1].maxAbsoluteError, 8., epsilon);
	EXPECT_NEAR(errors[1].maxRelativeError, 2., epsilon);
	EXPECT_NEAR(errors[1].meanAbsoluteError, 8./3., epsilon);
	EXPECT_NEAR(errors[1].meanRelativeError, 2./3., epsilon);
}

TEST_F(ValidatorTest, ZerosCase) {
	// Chemins des fichiers de test
	auto dumpPath = std::filesystem::path(VALIDATOR_DATA_PATH) / "ZerosCase";

	// Le fichier de dump Matlab contient 2 Arrays :
	// 1. 0. 3.
	// 0. 0. 0.

	// Ajoutez des vecteurs à la liste, par exemple :
	Eigen::ArrayXd array1(3);
	Eigen::ArrayXd array2(3);
	array1 << 1.0, 0.0, 0.0;
	array2 << 4.0, 0.0, 0.1;

	// Comparaison
	Validator::instance.compareArrays(dumpPath, { array1, array2 });

	// Tests du status
	EXPECT_EQ(Validator::instance.status(), Validator::Status::Ready);

	// Tests sur les données
	constexpr double epsilon = std::numeric_limits<double>::epsilon();
	constexpr double infinity = std::numeric_limits<double>::infinity();
	const auto& errors = Validator::instance.errors();
	// Premier vecteur
	EXPECT_NEAR(errors[0].maxAbsoluteError, 3., epsilon);
	EXPECT_NEAR(errors[0].maxRelativeError, 1., epsilon);
	EXPECT_NEAR(errors[0].meanAbsoluteError, 1., epsilon);
	EXPECT_NEAR(errors[0].meanRelativeError, 0.5, epsilon);
	// Deuxième vecteur
	EXPECT_NEAR(errors[1].maxAbsoluteError, 4., epsilon);
	EXPECT_EQ(errors[1].maxRelativeError, infinity);
	EXPECT_NEAR(errors[1].meanAbsoluteError, 41./30., epsilon);
	EXPECT_EQ(errors[1].meanRelativeError, infinity);
}

TEST_F(ValidatorTest, AtLeastOneEmptyArray) {
	// Chemins des fichiers de test
	std::filesystem::path dumpPath = absoluteDataValidationPath / "AtLeastOneEmptyArray";

	// Le fichier de dump Matlab contient 2 Arrays :
	// 1. 2. 3.
	// 4. 5. 6.

	// un vecteur vide : erreur
	Eigen::ArrayXd array1(3);
	Eigen::ArrayXd array2(0);

	Validator::instance.compareArrays(dumpPath, {array1, array2});

	// Tests du status
	EXPECT_EQ(Validator::instance.status(), Validator::Status::Error);

	// Test du message d'erreur
	EXPECT_EQ(Validator::instance.errorMessage(), "At least one array of the list is empty. Comparison process stopped.");
}

TEST_F(ValidatorTest, InconsistentArraySizes) {
	// Chemins des fichiers de test
	std::filesystem::path dumpPath = absoluteDataValidationPath / "InconsistentArraySizes";

	// Le fichier de dump Matlab contient 2 Arrays :
	// 1. 2. 3.
	// 4. 5. 6.

	// un vecteur vide : erreur
	Eigen::ArrayXd array1(3);
	Eigen::ArrayXd array2(2);

	Validator::instance.compareArrays(dumpPath, {array1, array2});

	// Tests du status
	EXPECT_EQ(Validator::instance.status(), Validator::Status::Error);

	// Test du message d'erreur
	EXPECT_EQ(Validator::instance.errorMessage(), "The sizes of the C++ and Matlab arrays are inconsistent. Comparison process stopped.");
}

TEST_F(ValidatorTest, MissingMatlabDump) {
	// Chemins des fichiers de test
	std::filesystem::path dumpPath = absoluteDataValidationPath / "MissingMatlabDump";

	// un vecteur vide : erreur
	Eigen::ArrayXd array1(3);
	Eigen::ArrayXd array2(3);

	Validator::instance.compareArrays(dumpPath, {array1, array2});

	// Tests du status
	EXPECT_EQ(Validator::instance.status(), Validator::Status::Error);

	// Test du message d'erreur
	EXPECT_EQ(Validator::instance.errorMessage(), "The matlab dump file does not exist.");
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
