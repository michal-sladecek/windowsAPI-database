#pragma once
#include <string>


class File
{
private:
	std::string m_content;
	std::wstring m_name;
public:
	File() = default;
	File(std::wstring path);
	void OpenFromDisk(std::wstring path);
	void OpenInDefault();

};