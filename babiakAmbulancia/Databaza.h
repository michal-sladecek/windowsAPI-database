#pragma once
#include "stdafx.h"
#include "Patient.h"
#include "Dialog.h"
#include <vector>

class Database {
	std::vector<Patient> m_patientList;
	std::vector<uint32_t> m_lastQuery;
public:
	void Add(Patient p);
	std::string ExportSerialize();
	void Database::Load(const std::vector<std::string> & data);
	uint32_t NumberOfPatients();

	void SaveToFile(wchar_t * fileName);

	void LoadFromFile(wchar_t * fileName);

	void QueryAllPatients();
	void QueryFindPatients(const std::vector<std::wstring> & hladane, size_t num);
	uint32_t QuerySize();
	Patient & QueryGet(uint32_t index);

};

