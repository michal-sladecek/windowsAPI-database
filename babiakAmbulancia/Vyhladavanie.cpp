#include "stdafx.h"
#include "Vyhladavanie.h"
#include "resource.h"
#define NUM_TO_FIND 5
static Databaza * curDatabaza;
static std::vector<Pacientka> najdene;
INT_PTR CALLBACK vyhladavanieDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		SendMessage(GetDlgItem(hDlg, IDC_MENO), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Meno"));
		SendMessage(GetDlgItem(hDlg, IDC_RODNECISLO), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("RodnÈ ËÌslo"));
		SendMessage(GetDlgItem(hDlg, IDC_TELEFONNECISLO), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("TelefÛnne ËÌslo"));
		SendMessage(GetDlgItem(hDlg, IDC_POZNAMKA), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Pozn·mka"));
		SendMessage(GetDlgItem(hDlg, IDC_ZMLUVNAPOISTOVNA), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Zmluvn· poisùovÚa"));
		SendMessage(GetDlgItem(hDlg, IDC_ZMLUVNYLEKAR), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Zmluvn˝ lek·r"));
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			WCHAR meno[50], rodneCislo[20], telefonneCislo[20], zmluvnaPoistovna[50], zmluvnyLekar[50], poznamka[1000];
			GetWindowText(GetDlgItem(hDlg, IDC_MENO), meno, 50);
			GetWindowText(GetDlgItem(hDlg, IDC_RODNECISLO), rodneCislo, 20);
			GetWindowText(GetDlgItem(hDlg, IDC_TELEFONNECISLO), telefonneCislo, 20);
			GetWindowText(GetDlgItem(hDlg, IDC_ZMLUVNAPOISTOVNA), zmluvnaPoistovna, 50);
			GetWindowText(GetDlgItem(hDlg, IDC_ZMLUVNYLEKAR), zmluvnyLekar, 50);
			GetWindowText(GetDlgItem(hDlg, IDC_POZNAMKA), poznamka, 1000);

			std::vector<std::wstring> V = { std::wstring(meno), std::wstring(rodneCislo), std::wstring(telefonneCislo), std::wstring(zmluvnaPoistovna),
				std::wstring(zmluvnyLekar), std::wstring(poznamka) };
			najdene = curDatabaza->find(V, NUM_TO_FIND);
			EndDialog(hDlg, LOWORD(wParam));
		}
		else if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
		}
		break;
	}
	return (INT_PTR)FALSE;
}
std::vector<Pacientka> vyhladavaciDialog(Databaza * p)
{
	curDatabaza = p;
	DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_VYHLADAVANIE), NULL, vyhladavanieDlgProc);
	return najdene;
}
