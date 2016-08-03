#include "stdafx.h"

#include "Patient.h"
#include "EditPatient.h"

INT_PTR EditPatientDialog::ProcessMessage(UINT message, WPARAM wParam)
{
	Patient & editedPatient = m_database->QueryGet(m_index);
	switch (message)
	{
	case WM_INITDIALOG:
		SetWindowText(GetDlgItem(m_window, IDC_MENO), editedPatient.getName().c_str());

		SetWindowText(GetDlgItem(m_window, IDC_MENO),editedPatient.getName().c_str());
		SetWindowText(GetDlgItem(m_window, IDC_RODNECISLO), editedPatient.getBirthNumber().c_str());
		SetWindowText(GetDlgItem(m_window, IDC_TELEFONNECISLO), editedPatient.getPhoneNumber().c_str());
		SetWindowText(GetDlgItem(m_window, IDC_POZNAMKA), editedPatient.getNote().c_str());
		SetWindowText(GetDlgItem(m_window, IDC_ZMLUVNAPOISTOVNA), editedPatient.getInsurance().c_str());
		SetWindowText(GetDlgItem(m_window, IDC_ZMLUVNYLEKAR), editedPatient.getDoctor().c_str());
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

			editedPatient.setName(meno);
			editedPatient.setBirthNumber(rodneCislo);
			editedPatient.setPhoneNumber(telefonneCislo);
			editedPatient.setInsurance(zmluvnaPoistovna);
			editedPatient.setDoctor(zmluvnyLekar);
			editedPatient.setNote(poznamka);

			EndDialog(m_window, LOWORD(wParam));
		}
		else if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(m_window, LOWORD(wParam));
		}
		break;
	}
	return (INT_PTR)FALSE;
}
