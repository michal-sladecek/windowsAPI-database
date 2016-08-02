#pragma once
#include <string>

template<typename T>
inline std::string GetBytes(const T & obj)
{
	return std::string(reinterpret_cast<const char *>(&obj), sizeof(obj));
}

inline std::string GetBytes(const std::wstring & obj)
{
	return std::string(reinterpret_cast<const char *>(obj.data()), sizeof(wchar_t)*obj.length());
}

inline std::wstring BytesToWstring(const std::string & data)
{
	return std::wstring(reinterpret_cast<const wchar_t *>(data.data()), data.length() / (sizeof(wchar_t)));
}