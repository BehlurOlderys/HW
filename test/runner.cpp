/*
 * runner.cpp
 *
 *  Created on: 22 Dec 2016
 *      Author: Bartek
 */

#include <stdio.h>
#include "gtest/gtest.h"

class TestFixture : public ::testing::Test
{

};

TEST(firstTests, shouldPass)
{
	EXPECT_EQ(2, 2);
}

TEST(firstTests, shouldFail)
{
	EXPECT_FALSE(true);
}

TEST(firstTests, last)
{
	EXPECT_EQ(0, 0);
}

GTEST_API_ int main(int argc, char *argv[])
{
  printf("Running main() from gtest_main.cc\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
