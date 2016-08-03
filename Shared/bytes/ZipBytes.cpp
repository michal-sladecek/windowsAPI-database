#include "stdafx.h"
#include "ZipBytes.h"
#include "StrUtils.h"

#include <exception>
#include <fstream>

std::string ZipByteVectors(const std::vector<std::string> & toExport)
{
	std::string exported = "";
	exported.append(GetBytes(toExport.size()));
	for (auto str : toExport)
	{
		exported.append(GetBytes(str.length()));
		exported.append(str.data(), str.length());
	}
	return exported;
}
std::vector<std::string> UnzipToByteVectors(std::string & str)
{
	std::vector<std::string> returnVal;
	const char * ptr = str.data();
	uint32_t numItems = *(reinterpret_cast<const uint32_t *>(ptr));
	ptr += sizeof(numItems);
	for (uint32_t i = 0; i < numItems; ++i)
	{
		uint32_t len = *(reinterpret_cast<const uint32_t *>(ptr));
		ptr += sizeof(numItems);
		returnVal.emplace_back(std::string(ptr, len));
		ptr += len;
	}
	return returnVal;
}

std::string LoadFileIntoString(const std::wstring & path)
{
	std::string data;
	std::ifstream subor;
	subor.open(path, std::ios::in);
	if (!subor.is_open()) {
		throw std::runtime_error("File could not be opened");
	}
	data.assign((std::istreambuf_iterator<char>(subor)), std::istreambuf_iterator<char>());
	return data;
}

void SaveStringToFile(const std::wstring & path, const std::string & data)
{
	std::ofstream subor;
	subor.open(path, std::ios::out | std::ios::trunc | std::ios::binary);
	if (!subor.is_open()) {
		throw std::runtime_error("File could not be opened");
	}
	subor.write(data.data(), data.size());
}