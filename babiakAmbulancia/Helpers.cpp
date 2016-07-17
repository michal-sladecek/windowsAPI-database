#include "stdafx.h"
#include "Helpers.h"

uint32_t StringEditDistance(std::wstring str1, std::wstring str2)
{
	size_t l1 = str1.length(), l2 = str2.length();
	std::vector<std::vector<uint32_t> > dp(l1 + 1, std::vector<uint32_t>(l2 + 1, 0));
	for (size_t i = 0; i <= l1; i++) {
		for (size_t j = 0; j <= l2; j++) {
			if (i == 0)dp[i][j] = j;
			else if (j == 0)dp[i][j] = i;
			else if (str1[i - 1] == str2[j - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = 1 + min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]);
		}
	}
	return dp[l1][l2];
}

bool DoesDirectoryExist(LPCTSTR szPath)
{
	DWORD dwAttrib = GetFileAttributes(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

std::wstring LoadFileIntoWstring(const std::wstring & path)
{
	std::locale::global(std::locale(""));
	std::wifstream subor;
	subor.open(path, std::ios::in);
	if (!subor.is_open()) {
		MessageBox(NULL, L"S˙bor sa nepodarilo otvoriù.", L"Chyba?", MB_OK);
		return L"";
	}
	std::wstring data;
	data.assign((std::istreambuf_iterator<wchar_t>(subor)), std::istreambuf_iterator<wchar_t>());
	return data;
}

void SaveWstringToFile(const std::wstring & path, const std::wstring & data)
{
	std::wofstream subor;
	subor.open(path, std::ios::out | std::ios::trunc | std::ios::binary);
	if (!subor.is_open()) {
		MessageBox(NULL, L"S˙bor sa nepodarilo otvoriù.", L"Chyba?", MB_OK);
		return;
	}
	subor << data;
}
