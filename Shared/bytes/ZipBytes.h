#pragma once
#include <vector>
#include <string>

std::string ZipByteVectors(const std::vector<std::string> & toExport);
std::vector<std::string> UnzipToByteVectors(std::string & str);

std::string LoadFileIntoString(const std::wstring & path);
void SaveStringToFile(const std::wstring & path, const std::string & data);