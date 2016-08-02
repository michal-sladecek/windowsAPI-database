#include "stdafx.h"
#include "Databaza.h"
#include "Patient.h"
#include "Helpers.h"
#include "Shlwapi.h"

#include "../OffsetDB/ZipBytes.h"

#include <utility>
#include <algorithm>

void Database::Add(Patient p)
{
	m_patientList.push_back(p);
}

std::string Database::ExportSerialize()
{
	std::vector<std::string> pacientkyExported;
	for (auto pac : m_patientList)
	{
		std::wstring wstr = pac.ExportSerialize();
		std::string str((const char*)&wstr[0], sizeof(wchar_t) / sizeof(char)*wstr.size());
		pacientkyExported.push_back(str);
	}
	return ZipByteVectors(pacientkyExported);
}

void Database::Load(const std::vector<std::string> & data)
{
	m_patientList.clear();
	for (auto p : data)
	{
		m_patientList.push_back(LoadCreate(p));
	}
}

uint32_t Database::NumberOfPatients()
{
	return m_patientList.size();
}

void Database::SaveToFile(wchar_t * fileName)
{
	std::locale::global(std::locale(""));
	std::string data = ExportSerialize();
	if (PathFileExists(fileName)) 
	{
		int choice = MessageBox(NULL, L"S˙bor uû existuje. Chcete ho prepÌsaù?", L"Naozaj?", MB_YESNO | MB_ICONWARNING);
		if (choice == IDNO)return;
	}
	try
	{
		SaveStringToFile(fileName, data);
	}
	catch (const std::exception & e)
	{
		MessageBox(NULL, L"Could not save to file." , L"Error?", MB_OK);
	}
}

void Database::LoadFromFile(wchar_t * fileName) 
{
	std::string data;
	try
	{
		data = LoadFileIntoString(fileName);
	}
	catch (const std::exception & e)
	{
		MessageBox(NULL, L"Could not save to file.", L"Error?", MB_OK);
		return;
	}
	std::vector<std::string> vec = UnzipToByteVectors(data);
	Load(vec);
}

void Database::QueryAllPatients()
{
	m_lastQuery.clear();
	for (uint32_t i = 0; i < m_patientList.size(); ++i)
	{
		m_lastQuery.push_back(i);
	}
}

void Database::QueryFindPatients(const std::vector<std::wstring>& hladane, size_t num)
{
	std::vector<std::pair<UINT, int> > V(m_patientList.size());
	for (size_t i = 0; i < V.size(); i++) 
	{
		V[i] = { m_patientList[i].MatchIndex(hladane),i };
	}
	sort(V.begin(), V.end());
	m_lastQuery.clear();
	for (size_t i = 0; i < num && i < V.size(); i++)
	{
		m_lastQuery.push_back(V[i].second);
	}
}

uint32_t Database::QuerySize()
{
	return m_lastQuery.size();
}

Patient & Database::QueryGet(uint32_t index)
{
	if (index >= m_lastQuery.size())
	{
		throw std::out_of_range("");
	}
	return m_patientList[m_lastQuery[index]];
}


