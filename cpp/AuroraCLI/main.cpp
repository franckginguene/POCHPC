#include <iostream>

#include "AuroraAPI/Factorial.h"

#include <proxyInclude/spdlog>

int main()
{
	// Configurer le logger
	spdlog::set_pattern("[%H:%M:%S] [%t] %v");
	spdlog::info("Logger initialized");

	const int nbThreads = 1;
	doSomethingParallel(nbThreads);

	return 0;
}
