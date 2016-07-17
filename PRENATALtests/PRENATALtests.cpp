// PRENATALtests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include "Authentification.h"
#include "Hashing.h"
#include <string>
using namespace std;

int main(int argc, char * argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}

