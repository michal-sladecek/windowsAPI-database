#pragma once
#include "Dialog.h"
#include "Databaza.h"

#include <memory>

namespace BackupSystem
{
	class BackupDialog : public Dialog
	{
	private:
		std::shared_ptr<Databaza> m_database;
		INT_PTR ProcessMessage(UINT message, WPARAM wParam);
	public:
		BackupDialog(HWND parent, std::shared_ptr<Databaza> database) :
			Dialog(parent), m_database(database)
		{
			m_template = IDD_ZALOHA;
		}
	};
}