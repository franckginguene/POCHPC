#pragma once

namespace Model
{

	/**
	 *	Do something qith Eigen
	 *
	 *	@param[in]	threadID	thread id to print
	 */
	void somethingWithEigen(int threadId);

	/**
	 *	Compute something in parallel 
	 *
	 *	@param[in]	nbThreads	Number of threads to instanciate
	 */
	void doSomethingParallel(const int nbThreads);
}
