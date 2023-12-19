#pragma once

//! Do something with Eigen
//! @param[in]	threadId	thread id to print
void somethingWithEigen(int threadId);

//! Compute something in parallel
//! @param[in]	nbThreads	Number of threads to instanciate
void doSomethingParallel(const int nbThreads);
