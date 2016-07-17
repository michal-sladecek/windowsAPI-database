#pragma once
#include "stdafx.h"
#include "Pacientka.h"
#include "Dialog.h"
#include <vector>




class Databaza {
	std::vector<Patient> pacientky;
	std::vector<uint32_t> query;
public:
	void pridaj(Patient p);
	std::wstring exportSerialize();
	void load(std::wstring data);	
	uint32_t numberEntries();
	
	void saveToFile(wchar_t * fileName);

	void loadFromFile(wchar_t * fileName);

	void queryAll();
	void queryFind(const std::vector<std::wstring> & hladane, size_t num);
	uint32_t querySize();
	Patient & queryGet(uint32_t index);

};


class AddPatientDialog : public Dialog
{
private:
	std::shared_ptr<Databaza> m_database;
	INT_PTR ProcessMessage(UINT message, WPARAM wParam);
public:
	AddPatientDialog(HWND parent, std::shared_ptr<Databaza> database) :
		Dialog(parent), m_database(database)
	{
		m_template = IDD_NOVAPACIENTKA;
	}
};