#pragma once
#include <string>
#include <vector>
#include "Doktor.h"
class Settings {
	std::vector<Doktor> doktori;
public:
	std::wstring exportSerialize();
	void load(std::wstring);
};