#include "DatabazaAPacienti.h"
#include "stdafx.h"
#include "resource.h"
#include "Pacientka.h"
#include "Databaza.h"


#include <Commctrl.h>
#include <string>
static Databaza * curDatabaza;

//Testuje èi sa pacient loadol spravne
void testLoad(std::wstring data) {
	Pacientka p;
	p.load(data);
	_ASSERTE(data == p.exportSerialize());
}

INT_PTR CALLBACK NovyPaciendDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		SendMessage(GetDlgItem(hDlg, IDC_MENO), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Meno"));
		SendMessage(GetDlgItem(hDlg, IDC_RODNECISLO), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Rodné èíslo"));
		SendMessage(GetDlgItem(hDlg, IDC_TELEFONNECISLO), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Telefónne èíslo"));
		SendMessage(GetDlgItem(hDlg, IDC_POZNAMKA), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Poznámka"));
		SendMessage(GetDlgItem(hDlg, IDC_ZMLUVNAPOISTOVNA), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Zmluvná poisovòa"));
		SendMessage(GetDlgItem(hDlg, IDC_ZMLUVNYLEKAR), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Zmluvný lekár"));
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

			Pacientka pac = Pacientka(std::wstring(meno), std::wstring(rodneCislo), std::wstring(telefonneCislo), std::wstring(zmluvnaPoistovna),
				std::wstring(zmluvnyLekar), std::wstring(poznamka));

			testLoad(pac.exportSerialize());
			curDatabaza->pridaj(pac);
			OutputDebugString(pac.exportSerialize().c_str());
			OutputDebugString(L"\n");
			EndDialog(hDlg, LOWORD(wParam));
		}
		else if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void NovyPacientDialog(Databaza * p, HWND parent)
{
	curDatabaza = p;
	DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_NOVAPACIENTKA), parent, NovyPaciendDlgProc);
}
