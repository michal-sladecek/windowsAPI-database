#include "stdafx.h"
#include "Backup.h"
#include "resource.h"
#include "Databaza.h"
#include "Shlwapi.h"

#include <string>
#include <fstream>

static Databaza * curDatabaza;
void saveDatabaza(WCHAR * fileName) {
	std::locale::global(std::locale(""));
	std::wstring data = curDatabaza->exportSerialize();
	if (PathFileExists(fileName)) {
		int choice = MessageBox(NULL, L"S˙bor uû existuje. Chcete ho prepÌsaù?", L"Naozaj?", MB_YESNO | MB_ICONWARNING);
		if (choice == IDNO)return;
	}
	std::wofstream subor;
	subor.open(fileName, std::ios::out | std::ios::trunc | std::ios::binary);
	if (!subor.is_open()) {
		MessageBox(NULL, L"S˙bor sa nepodarilo otvoriù.", L"Chyba?", MB_OK);
		return;
	}
	subor << data;
	subor.close();
}
void loadDatabaza(WCHAR * fileName) {
	std::locale::global(std::locale(""));
	std::wifstream subor;
	subor.open(fileName, std::ios::in);
	if (!subor.is_open()) {
		MessageBox(NULL, L"S˙bor sa nepodarilo otvoriù.", L"Chyba?", MB_OK);
		return;
	}
	std::wstring data;
	data.assign((std::istreambuf_iterator<wchar_t>(subor)), std::istreambuf_iterator<wchar_t>());
	subor.close();
	curDatabaza->load(data);
}
INT_PTR CALLBACK BackupDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hDlg, IDC_OUTPUT, IDC_INPUT, IDC_OUTPUT);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_CHOOSEFILE) {

			TCHAR szFileName[MAX_PATH]=TEXT("");
			OPENFILENAME ofn;

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.hInstance = GetModuleHandle(NULL);
			ofn.lpstrFile = szFileName;

			ofn.lpstrFilter = TEXT("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;

			
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER;
			ofn.lpstrDefExt = TEXT("txt");

			if (GetOpenFileName(&ofn)==TRUE) {
				HWND fileNameTextBox = GetDlgItem(hDlg, IDC_PATHFILE);
				SetWindowText(fileNameTextBox,szFileName);
			}
			break;
		}
		if (LOWORD(wParam) == IDOK)
		{
			WCHAR text[MAX_PATH];
			GetWindowText(GetDlgItem(hDlg, IDC_PATHFILE),text,MAX_PATH-1);
			if (IsDlgButtonChecked(hDlg, IDC_OUTPUT) == BST_CHECKED)
				saveDatabaza(text);
			else if (IsDlgButtonChecked(hDlg, IDC_INPUT) == BST_CHECKED)
				loadDatabaza(text);
			EndDialog(hDlg, LOWORD(wParam));
		}
		else if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
		}
		break;
	}
	return (INT_PTR)FALSE;
}
BOOL BackupDialog(Databaza * p)
{
	curDatabaza = p;
	DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ZALOHA), NULL, BackupDlgProc);
	return TRUE;
}