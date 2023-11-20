#include "gtest/gtest.h"
#include "Model/Factorial.h"

using namespace Model;

// Tests factorial of 0.
TEST(FactorialTest, HandlesZeroInput)
{
	EXPECT_EQ(factorial(0), 1);
}

// Tests factorial of positive numbers.
TEST(FactorialTest, HandlesPositiveInput)
{
	EXPECT_EQ(factorial(1), 1);
	EXPECT_EQ(factorial(2), 2);
	EXPECT_EQ(factorial(3), 6);
	EXPECT_EQ(factorial(5), 120);
	EXPECT_EQ(factorial(10), 3628800);
}

// Tests factorial of negative numbers.
TEST(FactorialTest, HandlesNegativeInput)
{
	EXPECT_EQ(factorial(-1), 0);
}
