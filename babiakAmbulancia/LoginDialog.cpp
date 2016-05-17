#include "stdafx.h"
#include "LoginDialog.h"
#include "resource.h"

BOOL Authentificate(TCHAR * key);
INT_PTR CALLBACK LoginDialogWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


INT_PTR CALLBACK LoginDialogWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			TCHAR * wndText = new TCHAR[100];
			GetWindowText(hDlg, wndText, 99);
			BOOL result = Authentificate(wndText);

			if (result == TRUE) {
				EndDialog(hDlg, IDOK);
			}
		}
		else {
			EndDialog(hDlg, IDCANCEL);
		}
		break;
	}
	return (INT_PTR)FALSE;
}

BOOL Login(HINSTANCE hInstance) {

}

BOOL Authentificate(TCHAR * key) {

}