#include "stdafx.h"
#include "Backup.h"
#include "resource.h"
#include "Databaza.h"
#include "Shlwapi.h"
#include "Helpers.h"

#include <string>
#include <fstream>

static Databaza * curDatabaza;
void saveDatabaza(WCHAR * fileName) {
	std::locale::global(std::locale(""));
	std::wstring data = curDatabaza->exportSerialize();
	if (PathFileExists(fileName)) {
		int choice = MessageBox(NULL, L"Súbor už existuje. Chcete ho prepísa?", L"Naozaj?", MB_YESNO | MB_ICONWARNING);
		if (choice == IDNO)return;
	}
	saveWstringToFile(fileName, data);
}
void loadDatabaza(WCHAR * fileName) {
	std::wstring data = loadFileIntoWstring(fileName);
	curDatabaza->load(data);
}
INT_PTR CALLBACK BackupDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		CheckRadioButton(hDlg, IDC_OUTPUT, IDC_INPUT, IDC_OUTPUT);
		HANDLE hIcon1 = LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SMALL),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
		SendMessage(GetDlgItem(hDlg, IDC_CHOOSEFILE), BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIcon1);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_CHOOSEFILE) {

			TCHAR szFileName[MAX_PATH]=TEXT("");
			OPENFILENAME ofn;

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.hInstance = GetModuleHandle(NULL);
			ofn.lpstrFile = szFileName;

			ofn.lpstrFilter = TEXT("All Files (*.*)\0*.*\0");
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
BOOL BackupDialog(Databaza * p, HWND parent)
{
	curDatabaza = p;
	DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ZALOHA), parent, BackupDlgProc);
	return TRUE;
}