#pragma once
#include "stdafx.h"
#include <string>
//Returns hash of the string
std::wstring getHashValue(TCHAR * string);

std::wstring encrypt(std::wstring str, std::wstring pass);
