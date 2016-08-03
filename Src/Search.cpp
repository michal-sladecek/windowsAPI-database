#include "stdafx.h"
#include "Search.h"
#include "resource.h"


INT_PTR SearchDialog::ProcessMessage(UINT message, WPARAM wParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SendMessage(GetDlgItem(m_window, IDC_MENO), EM_SETCUEBANNER, TRUE, (LPARAM)L"Meno");
		SendMessage(GetDlgItem(m_window, IDC_RODNECISLO), EM_SETCUEBANNER, TRUE, (LPARAM)L"RodnÈ ËÌslo");
		SendMessage(GetDlgItem(m_window, IDC_TELEFONNECISLO), EM_SETCUEBANNER, TRUE, (LPARAM)L"TelefÛnne ËÌslo");
		SendMessage(GetDlgItem(m_window, IDC_POZNAMKA), EM_SETCUEBANNER, TRUE, (LPARAM)L"Pozn·mka");
		SendMessage(GetDlgItem(m_window, IDC_ZMLUVNAPOISTOVNA), EM_SETCUEBANNER, TRUE, (LPARAM)L"Zmluvn· poisùovÚa");
		SendMessage(GetDlgItem(m_window, IDC_ZMLUVNYLEKAR), EM_SETCUEBANNER, TRUE, (LPARAM)L"Zmluvn˝ lek·r");
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			wchar_t meno[50], rodneCislo[20], telefonneCislo[20], zmluvnaPoistovna[50], zmluvnyLekar[50], poznamka[1000];
			GetWindowText(GetDlgItem(m_window, IDC_MENO), meno, 50);
			GetWindowText(GetDlgItem(m_window, IDC_RODNECISLO), rodneCislo, 20);
			GetWindowText(GetDlgItem(m_window, IDC_TELEFONNECISLO), telefonneCislo, 20);
			GetWindowText(GetDlgItem(m_window, IDC_ZMLUVNAPOISTOVNA), zmluvnaPoistovna, 50);
			GetWindowText(GetDlgItem(m_window, IDC_ZMLUVNYLEKAR), zmluvnyLekar, 50);
			GetWindowText(GetDlgItem(m_window, IDC_POZNAMKA), poznamka, 1000);

			std::vector<std::wstring> V = { std::wstring(meno), std::wstring(rodneCislo), std::wstring(telefonneCislo), std::wstring(zmluvnaPoistovna),
				std::wstring(zmluvnyLekar), std::wstring(poznamka) };
			m_database->QueryFindPatients(V, m_numberOfReturnedMatches);
			EndDialog(m_window, LOWORD(wParam));
		}
		else if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(m_window, LOWORD(wParam));
		}
		break;
	}
	return (INT_PTR)FALSE;
}
