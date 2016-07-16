#pragma once
#include <string>
#include <vector>
#include "Doktor.h"
const std::wstring SETTINGS_DIR = L"prenatalNastavenia";
const std::wstring SETTINGS_FILE = L"settings.txt";

class Settings {
	std::vector<Doktor> doktori;
	void loadSettingsFile(std::wstring path);
	void createSettingsFile(std::wstring path);
public:
	Settings();
	std::wstring exportSerialize();
	void load(std::wstring);
};