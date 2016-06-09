#include "stdafx.h"
#include "resource.h"
#include "Hashing.h"
#include "Authentification.h"

#include <string>

#define testing_password TEXT("5244F0B5889C63853A171BB57C733A5E6CCE2A2DE119F318DDA4F61864697C02")
static BOOL authentificated = FALSE;

BOOL is_authentificated() {
	return authentificated;
}
BOOL Authentificate(TCHAR * password)
{
	std::wstring p = getHashValue(password);
	if (p==std::wstring(testing_password)) {
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
BOOL AuthentificateDialog(HINSTANCE hInst, HWND parent)
{
	DialogBox(hInst, MAKEINTRESOURCE(IDD_LOGIN), parent, AuthDlgProc);
	return TRUE;
}