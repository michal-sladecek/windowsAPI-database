#include "stdafx.h"
#include "Databaza.h"
#include "Patient.h"
#include "Helpers.h"
#include "Shlwapi.h"


#include <utility>
#include <algorithm>

void Database::Add(Patient p)
{
	m_patientList.push_back(p);
}

std::wstring Database::ExportSerialize()
{
	std::wstring beg = L"{", en = L"}", oddelovac = L"|";
	std::wstring writeout = beg;
	for (auto p : m_patientList) {
		writeout += p.ExportSerialize() + oddelovac;
	}
	writeout.pop_back();
	return writeout + en;
}

void Database::Load(std::wstring data)
{
	m_patientList.clear();
	size_t len = data.length();
	if (data[0] != '{')throw std::invalid_argument("Database is not in the right format");
	if (data[len - 1] != '}')throw std::invalid_argument("Database is not in the right format");
	int beg = 0;
	for (size_t i = 1; i < len - 1; i++) {
		if (data[i] == ']') {
			m_patientList.push_back(LoadCreate(data.substr(beg, i - beg + 1)));
		}
		else if (data[i] == '[') beg = i;
	}
}

uint32_t Database::NumberOfPatients()
{
	return m_patientList.size();
}

void Database::SaveToFile(wchar_t * fileName) {
	std::locale::global(std::locale(""));
	std::wstring data = ExportSerialize();
	if (PathFileExists(fileName)) {
		int choice = MessageBox(NULL, L"Súbor už existuje. Chcete ho prepísa?", L"Naozaj?", MB_YESNO | MB_ICONWARNING);
		if (choice == IDNO)return;
	}
	SaveWstringToFile(fileName, data);
}
void Database::LoadFromFile(wchar_t * fileName) {
	std::wstring data = LoadFileIntoWstring(fileName);
	Load(data);
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


