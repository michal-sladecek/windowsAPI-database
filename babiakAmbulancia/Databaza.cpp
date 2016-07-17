#include "stdafx.h"
#include "Databaza.h"
#include "Pacientka.h"
#include "Helpers.h"
#include "Shlwapi.h"


#include <utility>
#include <algorithm>

void Databaza::pridaj(Patient p)
{
	pacientky.push_back(p);
}

std::wstring Databaza::exportSerialize()
{
	std::wstring beg = L"{", en = L"}", oddelovac = L"|";
	std::wstring writeout = beg;
	for (auto p : pacientky) {
		writeout += p.ExportSerialize() + oddelovac;
	}
	writeout.pop_back();
	return writeout + en;
}

void Databaza::load(std::wstring data)
{
	pacientky.clear();
	size_t len = data.length();
	if (data[0] != '{')throw std::invalid_argument("Database is not in the right format");
	if (data[len - 1] != '}')throw std::invalid_argument("Database is not in the right format");
	int beg = 0;
	for (size_t i = 1; i < len - 1; i++) {
		if (data[i] == ']') {
			pacientky.push_back(LoadCreate(data.substr(beg, i - beg + 1)));
		}
		else if (data[i] == '[') beg = i;
	}
}

uint32_t Databaza::numberEntries()
{
	return pacientky.size();
}

void Databaza::saveToFile(wchar_t * fileName) {
	std::locale::global(std::locale(""));
	std::wstring data = exportSerialize();
	if (PathFileExists(fileName)) {
		int choice = MessageBox(NULL, L"Súbor už existuje. Chcete ho prepísa?", L"Naozaj?", MB_YESNO | MB_ICONWARNING);
		if (choice == IDNO)return;
	}
	SsaveWstringToFile(fileName, data);
}
void Databaza::loadFromFile(wchar_t * fileName) {
	std::wstring data = LoadFileIntoWstring(fileName);
	load(data);
}

void Databaza::queryAll()
{
	query.clear();
	for (uint32_t i = 0; i < pacientky.size(); ++i)
	{
		query.push_back(i);
	}
}

void Databaza::queryFind(const std::vector<std::wstring>& hladane, size_t num)
{
	std::vector<std::pair<UINT, int> > V(pacientky.size());
	for (size_t i = 0; i < V.size(); i++) 
	{
		V[i] = { pacientky[i].matchIndex(hladane),i };
	}
	sort(V.begin(), V.end());
	query.clear();
	for (size_t i = 0; i < num && i < V.size(); i++)
	{
		query.push_back(V[i].second);
	}
}

uint32_t Databaza::querySize()
{
	return query.size();
}

Patient & Databaza::queryGet(uint32_t index)
{
	if (index >= query.size())
	{
		throw std::out_of_range("");
	}
	return pacientky[query[index]];
}

INT_PTR AddPatientDialog::ProcessMessage(UINT message, WPARAM wParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SendMessage(GetDlgItem(m_window, IDC_MENO), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Meno"));
		SendMessage(GetDlgItem(m_window, IDC_RODNECISLO), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Rodné èíslo"));
		SendMessage(GetDlgItem(m_window, IDC_TELEFONNECISLO), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Telefónne èíslo"));
		SendMessage(GetDlgItem(m_window, IDC_POZNAMKA), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Poznámka"));
		SendMessage(GetDlgItem(m_window, IDC_ZMLUVNAPOISTOVNA), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Zmluvná poisovòa"));
		SendMessage(GetDlgItem(m_window, IDC_ZMLUVNYLEKAR), EM_SETCUEBANNER, TRUE, (LPARAM)TEXT("Zmluvný lekár"));
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

			m_database->pridaj(pac);
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
