#include "stdafx.h"
#include "Backup.h"
#include "resource.h"


INT_PTR CALLBACK BackupDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
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
			EndDialog(hDlg, LOWORD(wParam));
		}
		else if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
		}
		break;
	}
	return (INT_PTR)FALSE;
}
BOOL BackupDialog(HINSTANCE hInst)
{
	DialogBox(hInst, MAKEINTRESOURCE(IDD_ZALOHA), NULL, BackupDlgProc);
	return TRUE;
}