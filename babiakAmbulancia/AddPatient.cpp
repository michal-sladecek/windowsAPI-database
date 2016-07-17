#include "stdafx.h"
#include "AddPatient.h"

INT_PTR AddPatientDialog::ProcessMessage(UINT message, WPARAM wParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SendMessage(GetDlgItem(m_window, IDC_MENO), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Meno"));
		SendMessage(GetDlgItem(m_window, IDC_RODNECISLO), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Rodn� ��slo"));
		SendMessage(GetDlgItem(m_window, IDC_TELEFONNECISLO), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Telef�nne ��slo"));
		SendMessage(GetDlgItem(m_window, IDC_POZNAMKA), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Pozn�mka"));
		SendMessage(GetDlgItem(m_window, IDC_ZMLUVNAPOISTOVNA), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Zmluvn� pois�ov�a"));
		SendMessage(GetDlgItem(m_window, IDC_ZMLUVNYLEKAR), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Zmluvn� lek�r"));
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

			Patient pac = Patient(std::wstring(meno), std::wstring(rodneCislo), std::wstring(telefonneCislo), std::wstring(zmluvnaPoistovna),
				std::wstring(zmluvnyLekar), std::wstring(poznamka));

			m_database->Add(pac);
			OutputDebugString(pac.ExportSerialize().c_str());
			OutputDebugString(L"\n");
			EndDialog(m_window, LOWORD(wParam));
		}
		else if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(m_window, LOWORD(wParam));
		}
		break;
	}
	return (INT_PTR)FALSE;
}