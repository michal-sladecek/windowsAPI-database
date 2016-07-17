#include "stdafx.h"
#include "Hashing.h"
#include "Authentification.h"

#include <string>

const wchar_t testing_password[] = L"5244F0B5889C63853A171BB57C733A5E6CCE2A2DE119F318DDA4F61864697C02";

namespace
{
	bool authentificated = false;
	bool Authentificate(const wchar_t * password)
	{
		std::wstring p = GetHashValue(password);
		if (p == std::wstring(testing_password)) 
		{
			authentificated = true;
			return true;
		}
		return false;
	}
}
bool AuthentificationSystem::IsAuthentificated()
{
	return authentificated;
}

INT_PTR AuthentificationSystem::AuthentificateDialog::ProcessMessage(UINT message, WPARAM wParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			HWND textInput = GetDlgItem(m_window, IDC_PASSWORD);
			wchar_t stringFromInput[100];
			GetWindowText(textInput, stringFromInput, 99);
			if (Authentificate(stringFromInput) == false) {
				MessageBox(m_window, L"Password not correct", L"Error", MB_OK);
			}
			else {
				EndDialog(m_window, LOWORD(wParam));
			}
		}
		else if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(m_window, LOWORD(wParam));
		}
		break;
	}
	return (INT_PTR)FALSE;
}
