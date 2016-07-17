#pragma once
#include "stdafx.h"
#include "Databaza.h"
#include <vector>
#include <string>

class SearchDialog : public Dialog
{
private:
	std::shared_ptr<Database> m_database;
	uint32_t m_numberOfReturnedMatches = 10;
	INT_PTR ProcessMessage(UINT message, WPARAM wParam);
public:
	SearchDialog(HWND parent, std::shared_ptr<Database> database) :
		Dialog(parent), m_database(database)
	{
		m_template = IDD_VYHLADAVANIE;
	}
};