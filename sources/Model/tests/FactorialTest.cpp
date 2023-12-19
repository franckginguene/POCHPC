#include "gtest/gtest.h"
#include "Model/Factorial.h"


TEST(Aurora, Eigen)
{
	somethingWithEigen(0);
}

TEST(Aurora, Parallel)
{
	doSomethingParallel(4);
}

//TEST(FactorialTest, HandlesPositiveInput)
//{
//	EXPECT_EQ(factorial(1), 1);
//	EXPECT_EQ(factorial(2), 2);
//	EXPECT_EQ(factorial(3), 6);
//	EXPECT_EQ(factorial(5), 120);
//	EXPECT_EQ(factorial(10), 3628800);
//}

//TEST(FactorialTest, HandlesNegativeInput)
//{
//	EXPECT_EQ(factorial(-1), 0);
//}
