#pragma once
#include "Dialog.h"
#include "Databaza.h"

class AddPatientDialog : public Dialog
{
private:
	std::shared_ptr<Database> m_database;
	INT_PTR ProcessMessage(UINT message, WPARAM wParam);
public:
	AddPatientDialog(HWND parent, std::shared_ptr<Database> database) :
		Dialog(parent), m_database(database)
	{
		m_template = IDD_NOVAPACIENTKA;
	}
};