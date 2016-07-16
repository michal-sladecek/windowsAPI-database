#include "stdafx.h"
#include "Helpers.h"

BOOL DirectoryExists(LPCTSTR szPath)
{
	DWORD dwAttrib = GetFileAttributes(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

std::wstring loadFileIntoWstring(const std::wstring & path)
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

void saveWstringToFile(const std::wstring & path, const std::wstring & data)
{
	std::wofstream subor;
	subor.open(path, std::ios::out | std::ios::trunc | std::ios::binary);
	if (!subor.is_open()) {
		MessageBox(NULL, L"S˙bor sa nepodarilo otvoriù.", L"Chyba?", MB_OK);
		return;
	}
	subor << data;
}
