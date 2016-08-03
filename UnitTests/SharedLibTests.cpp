#include "stdafx.h"
#include "gtest\gtest.h"

#include "Hashing.h"
#include "Helpers.h"
#include "bytes\StrUtils.h"
#include "bytes\ZipBytes.h"

TEST(Hashing, HashingTest)
{
	EXPECT_EQ(GetHashValue(L"Ahoj"), GetHashValue(L"Ahoj"));
	EXPECT_NE(GetHashValue(L"Ahoj"), GetHashValue(L"Aho"));
	EXPECT_NE(GetHashValue(L"Ahoj"), GetHashValue(L"Ahok"));
	EXPECT_NE(GetHashValue(L"Ahoj"), GetHashValue(L"Ahojp"));
}


TEST(Helpers, StringEditDist)
{
	EXPECT_EQ(StringEditDistance(L"Ahoj", L"Ahoj"), 0);
	EXPECT_EQ(StringEditDistance(L"", L""), 0);
	EXPECT_EQ(StringEditDistance(L"A", L"B"), 1);
	EXPECT_EQ(StringEditDistance(L"aaa", L"aaab"), 1);
	EXPECT_EQ(StringEditDistance(L"book", L"back"), 2);
	EXPECT_EQ(StringEditDistance(L"dsgfsdgsfdv", L"dsafwfwererewfw"), 12);
}

TEST(Helpers, DoesDirectoryExist)
{
	EXPECT_EQ(DoesDirectoryExist(L"sadsaodds"), false);
	EXPECT_EQ(DoesDirectoryExist(L"C:\\afa"), false);
	EXPECT_EQ(DoesDirectoryExist(L"C:\\Users\\USER\\Documents\\Visual Studio 2015\\Projects\\babiakAmbulancia"), true);
	EXPECT_EQ(DoesDirectoryExist(L"C:\\Windows"), true);
}


TEST(StrUtils, WstringToBytes)
{
	std::wstring wstr = L"abcd, \\] 2343··ÈæööæËöæùûùöËùÙÙÙ";
	std::string bytes = GetBytes(wstr);
	EXPECT_EQ(wstr, BytesToWstring(bytes));
}

TEST(StrUtils, IntToBytes)
{
	uint32_t integer = 1234;
	std::string bytes = GetBytes(integer);
	EXPECT_EQ(bytes.length(), sizeof(integer));
	EXPECT_EQ(integer, *(reinterpret_cast<const uint32_t *>(bytes.data())));

	char c = 0;
	bytes = GetBytes(c);
	EXPECT_EQ(bytes.length(), sizeof(c));
	EXPECT_EQ(c, *(reinterpret_cast<const char *>(bytes.data())));
}

TEST(ZipBytes, ZipUnzip)
{
	std::vector<std::string> V = { "A","", "", "sajfdlswnkc","1234321452435","Alpha","", "BigWooodenCock" };
	std::string zipped = ZipByteVectors(V);
	std::vector<std::string> unzipped = UnzipToByteVectors(zipped);
	EXPECT_EQ(V.size(), unzipped.size());
	for (uint16_t i = 0; i < V.size(); ++i)
	{
		EXPECT_EQ(V[i], unzipped[i]);
	}
}

TEST(ZipBytes, SaveToFile)
{
	std::vector<std::string> V = { "A","sajfdlswnkc","1234321452435","Alpha","BigWooodenCock" };
	std::string zipped = ZipByteVectors(V);

	std::wstring filename = L"temporaryFileUsedForTests";
	SaveStringToFile(filename, zipped);

	std::string loaded = LoadFileIntoString(filename);
	EXPECT_EQ(loaded, zipped);
}
