#pragma once
#include <string>
class Doktor {
	std::wstring meno;
	std::wstring authHash;
	std::wstring encrypted_pass;
public:
	std::wstring exportSerialize();
	void load(std::wstring);
};