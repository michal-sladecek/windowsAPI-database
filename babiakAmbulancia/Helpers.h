#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include <fstream>

uint32_t StringEditDistance(std::wstring str1, std::wstring str2);
bool DoesDirectoryExist(LPCTSTR szPath);
std::wstring LoadFileIntoWstring(const std::wstring & path);
void SaveWstringToFile(const std::wstring & path, const std::wstring & data);