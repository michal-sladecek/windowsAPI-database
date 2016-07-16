#include "Settings.h"
#include "stdafx.h"
#include "Settings.h"
#include "Helpers.h"
#include "Shlwapi.h"


void Settings::loadSettingsFile(std::wstring path)
{

}

void Settings::createSettingsFile(std::wstring path)
{
}

Settings::Settings()
{
	std::wstring path = SETTINGS_DIR + L"\\" + SETTINGS_FILE;
	if (PathFileExistsW(path.c_str()))
	{
		loadSettingsFile(path);
	}
	else
	{
		createSettingsFile(path);
	}
}

std::wstring Settings::exportSerialize()
{
	return std::wstring(L"[]");
}

void Settings::load(std::wstring)
{
}
