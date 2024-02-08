#pragma once

#include <functional>
#include <thread>
#include <vector>

#include <proxyInclude/spdlog>

class __declspec(dllexport) Simulation {
public:
    // Constructeur
    Simulation();

    // Destructeur
    ~Simulation();

    // Fonction pour lancer la simulation
    void launch(std::function<void()> specificFunction);

protected:
    // Fonction d'initialisation
    void initialize();

private:
    unsigned int _numThreads;
};