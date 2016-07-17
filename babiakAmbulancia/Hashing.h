#pragma once
#include "stdafx.h"
#include <string>
//Returns hash of the string
std::wstring GetHashValue(const wchar_t * string);

std::wstring EncryptString(const std::wstring & str, const std::wstring & pass);
std::wstring DecryptString(const std::wstring &str, const std::wstring &pass);