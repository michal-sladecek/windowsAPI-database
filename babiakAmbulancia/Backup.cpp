#include "stdafx.h"
#include "Backup.h"
#include "Databaza.h"

INT_PTR BackupSystem::BackupDialog::ProcessMessage(UINT message, WPARAM wParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		CheckRadioButton(m_window, IDC_OUTPUT, IDC_INPUT, IDC_OUTPUT);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_CHOOSEFILE) {

			wchar_t szFileName[MAX_PATH];
			OPENFILENAME ofn = {};

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = m_window;
			ofn.hInstance = GetModuleHandle(NULL);
			ofn.lpstrFile = szFileName;

			ofn.lpstrFilter = L"All Files (*.*)\0*.*\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;


			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER;
			ofn.lpstrDefExt = L"txt";

			if (GetOpenFileName(&ofn) == TRUE) 
			{
				HWND fileNameTextBox = GetDlgItem(m_window, IDC_PATHFILE);
				SetWindowText(fileNameTextBox, szFileName);
			}
			break;
		}
		if (LOWORD(wParam) == IDOK)
		{
			wchar_t text[MAX_PATH];
			GetWindowText(GetDlgItem(m_window, IDC_PATHFILE), text, MAX_PATH - 1);
			if (IsDlgButtonChecked(m_window, IDC_OUTPUT) == BST_CHECKED)
			{
				m_database->saveToFile(text);
			}
			else if (IsDlgButtonChecked(m_window, IDC_INPUT) == BST_CHECKED)
			{
				m_database->loadFromFile(text);
			}
			EndDialog(m_window, LOWORD(wParam));
		}
		else if (LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(m_window, LOWORD(wParam));
		}
		break;
	}
	return (INT_PTR)FALSE;
}
