#pragma once

#include "Dialog.h"
#include "Databaza.h"

#include <memory>
class EditPatientDialog : public Dialog
{
	std::shared_ptr<Database> m_database;
	uint32_t m_index;
	INT_PTR ProcessMessage(UINT message, WPARAM wParam);
public:
	EditPatientDialog(HWND parent, std::shared_ptr<Database> database, uint32_t index) :
		Dialog(parent), m_database(database), m_index(index)
	{
		m_template = IDD_NOVAPACIENTKA;
	}
};