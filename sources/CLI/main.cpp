#include <iostream>
#include <spdlog/spdlog.h>
#include "Model/Factorial.h"

int main()
{
	// Configurer le logger
	spdlog::set_pattern("[%H:%M:%S] [%t] %v");
	spdlog::info("Logger initialized");

	const int nbThreads = 1;
	doSomethingParallel(nbThreads);

	return 0;
}
