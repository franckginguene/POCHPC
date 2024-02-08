#include "Simulation.h"

#include <iostream>

// Constructeur
Simulation::Simulation() {
    initialize();
}

// Destructeur
Simulation::~Simulation() {
}

// Fonction d'initialisation
void Simulation::initialize() {
    // Si on est en débug, on reste sur 1 thread, sinon, autant de threads que de coeurs logiques
#ifdef _DEBUG
    _numThreads = 1;
#else
    _numThreads = std::thread::hardware_concurrency();
#endif
}

// Fonction pour lancer la simulation
void Simulation::launch(std::function<void()> specificFunction) {
    // Vérifier si le vecteur de threads est vide
    std::vector<std::thread> threads (_numThreads);
    if (threads.empty()) {
        std::cerr << "Aucun thread disponible." << std::endl;
        return;
    }

    // Lancer les threads
    for (auto& thread : threads) {
        thread = std::thread(specificFunction);
    }

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}