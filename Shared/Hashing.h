#pragma once
#include <string>
//Returns hash of the string
std::string GetHashValue(const std::wstring & string);

std::wstring EncryptString(const std::wstring & str, const std::wstring & pass);
std::wstring DecryptString(const std::wstring &str, const std::wstring &pass);