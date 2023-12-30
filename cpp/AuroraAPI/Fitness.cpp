#include "Fitness.h"

#include <iostream>
#include <thread>

#include <MDD/Types.h>

#include <proxyInclude/spdlog>
#include <proxyInclude/backward>

namespace Fitness {

    // Fonction pour effectuer un gros calcul avec la bibliothèque Eigen
    void doSomethingWithEigen() {
        ArrayType original = ArrayType::Random(10'000'000);
	    // Calcul de la transposée
        ArrayType transposed = original.transpose().exp().sin().acos();

	    // Multiplication de la matrice originale avec sa transposée
        ArrayType result = original * transposed;

        // Affichage du résultat (à titre d'exemple)
        // TODO remplacer par spdlog
        spdlog::info("Résultat du calcul avec Eigen \n");
    }

}  // namespace Fitness