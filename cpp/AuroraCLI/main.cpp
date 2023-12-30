#include <iostream>

#include "AuroraAPI/Simulation.h"
#include "AuroraAPI/Fitness.h"

#include <proxyInclude/spdlog>

int main()
{
	// Configurer le logger
	spdlog::set_pattern("[%H:%M:%S] [%t] %v");
	spdlog::info("Logger initialized");

	Simulation simulation;
	simulation.launch(Fitness::doSomethingWithEigen);

	return 0;
}
