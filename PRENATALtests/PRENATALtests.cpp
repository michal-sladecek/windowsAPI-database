// PRENATALtests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include "Authentification.h"
#include "Hashing.h"
#include <string>
using namespace std;


TEST(Authentification, shouldNotBeAuthentificated)
{
	ASSERT_FALSE(is_authentificated());
}
TEST(Authentification, cannotAuthentificateWithWrongPass)
{
	Authentificate(L"TEST");
	ASSERT_FALSE(is_authentificated());
	Authentificate(L"TESTINGS");
	ASSERT_FALSE(is_authentificated());
	Authentificate(L"TESTS");
	ASSERT_FALSE(is_authentificated());
	Authentificate(L"");
	ASSERT_FALSE(is_authentificated());
	Authentificate(L" ");
	ASSERT_FALSE(is_authentificated());
	Authentificate(L"1234556666");
	ASSERT_FALSE(is_authentificated());
	std::wstring longPass = L"";
	for (int i = 0; i < 10000; ++i)
		longPass += L'a';
	Authentificate(longPass.c_str());
	ASSERT_FALSE(is_authentificated());
}
TEST(Authentification, canAuthentificateWithRightPass)
{
	Authentificate(L"TESTING");
	ASSERT_TRUE(is_authentificated());
}
TEST(Hashing, twoStringsSameHash)
{
	ASSERT_EQ(getHashValue(L"A"), getHashValue(L"A"));
	ASSERT_EQ(getHashValue(L""), getHashValue(L""));
	ASSERT_EQ(getHashValue(L"AAAAAAAAAAAAAAAA"), getHashValue(L"AAAAAAAAAAAAAAAA"));
}
TEST(Hashing, twoStringsDifferentHash)
{
	ASSERT_NE(getHashValue(L"A"), getHashValue(L"B"));
	ASSERT_NE(getHashValue(L""), getHashValue(L" "));
	ASSERT_NE(getHashValue(L"AAAAAAAAAAAAAAAA"), getHashValue(L""));
}
int main(int argc, char * argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}

