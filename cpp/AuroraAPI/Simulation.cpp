#include "Simulation.h"

#include <iostream>

// Constructeur
Simulation::Simulation() {
    initialize();
}

// Destructeur
Simulation::~Simulation() {
    joinThreads();
}

// Fonction d'initialisation
void Simulation::initialize() {
    // Si on est en débug, on reste sur 1 thread, sinon, autant de threads que de coeurs logiques
#ifdef _DEBUG
    unsigned int numThreads = 1;
#else
    unsigned int numThreads = std::thread::hardware_concurrency();
#endif

    // Allouer des threads dans le vecteur
    threads_.resize(numThreads);
}

// Fonction pour lancer la simulation
void Simulation::launch(std::function<void()> specificFunction) {
    // Vérifier si le vecteur de threads est vide
    if (threads_.empty()) {
        std::cerr << "Aucun thread disponible." << std::endl;
        return;
    }

    // Lancer les threads
    for (auto& thread : threads_) {
        thread = std::thread(specificFunction);
    }

    // Attendre la fin de tous les threads
    joinThreads();
}

// Fonction pour attendre la fin de tous les threads
void Simulation::joinThreads() {
    for (auto& thread : threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}