#include "stdafx.h"
#include "resource.h"
#include "Authentification.h"

#define testing_password TEXT("TESTING")
static BOOL authentificated = FALSE;

BOOL is_authentificated() {
	return authentificated;
}
BOOL Authentificate(TCHAR * password)
{
	if (_tcscmp(password, testing_password) == 0) {
		authentificated = TRUE;
		return TRUE;
	}
	return FALSE;
}
INT_PTR CALLBACK FailedLoginProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK AuthDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			HWND textInput = GetDlgItem(hDlg, IDC_PASSWORD);
			TCHAR stringFromInput[100];
			GetWindowText(textInput, stringFromInput, 99);
			if (Authentificate(stringFromInput) == FALSE) {
				DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_FAILED_LOGIN), hDlg, FailedLoginProc);
			}
			else {
				EndDialog(hDlg, LOWORD(wParam));
			}
		}
		else if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
		}
		break;
	}
	return (INT_PTR)FALSE;
}
BOOL AuthentificateDialog(HINSTANCE hInst)
{
	DialogBox(hInst, MAKEINTRESOURCE(IDD_LOGIN), NULL, AuthDlgProc);
	return TRUE;
}
