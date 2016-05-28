#include "stdafx.h"
#include "Pacientka.h"
#include "Helpers.h"

#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>
#include <ctime>


inline Pacientka::Pacientka() {

}

inline Pacientka::Pacientka(BOOL nova) {
	if (nova)
		creationTime = time(NULL);
}

Pacientka::Pacientka(std::wstring _meno, std::wstring _rodneCislo, std::wstring _telefonneCislo, std::wstring _zmluvnaPoistovna, std::wstring _zmluvnyLekar, std::wstring _poznamka) {
	creationTime = time(NULL);
	meno = _meno;
	rodneCislo = _rodneCislo;
	telefonneCislo = _telefonneCislo;
	zmluvnaPoistovna = _zmluvnaPoistovna;
	zmluvnyLekar = _zmluvnyLekar;
	poznamka = _poznamka;
}

time_t Pacientka::getID()
{
	return creationTime;
}

std::wstring Pacientka::getIDstr()
{
	return std::to_wstring(creationTime);
}

std::wstring Pacientka::getPoznamka()
{
	return poznamka;
}

std::wstring Pacientka::getMeno()
{
	return meno;
}

std::wstring Pacientka::getRodneCislo()
{
	return rodneCislo;
}

std::wstring Pacientka::getTelCislo()
{
	return telefonneCislo;
}

std::wstring Pacientka::getZmluvnaPoistovna()
{
	return zmluvnaPoistovna;
}

std::wstring Pacientka::getZmluvnyLekar()
{
	return zmluvnyLekar;
}

std::wstring Pacientka::exportSerialize()
{
	std::wstring serialized;
	std::wstring beg(TEXT("[")), en(TEXT("]")), oddelovac(TEXT("|"));
	serialized = beg+ std::to_wstring(creationTime) + oddelovac+ meno + oddelovac + rodneCislo + oddelovac + telefonneCislo + oddelovac + zmluvnaPoistovna + oddelovac + zmluvnyLekar + oddelovac + poznamka + en;
	return serialized;
}

void Pacientka::load(std::wstring data)
{
	size_t len = data.length();
	if (data[0] != '[')throw std::invalid_argument("Pacientka is not in the right format");
	if (data[len - 1] != ']')throw std::invalid_argument("Pacientka is not in the right format");
	size_t beg = 1;
	std::vector<std::wstring> V;
	for (size_t i = 1; i < len; i++) {
		if (data[i] == '|' || data[i]==']') {
			V.push_back(data.substr(beg, i - beg));
			beg = i + 1;
		}
	}
	creationTime = std::stoi(V[0]);
	meno = V[1];
	rodneCislo = V[2];
	telefonneCislo = V[3];
	zmluvnaPoistovna = V[4];
	zmluvnyLekar = V[5];
	poznamka = V[6];
}
Pacientka loadCreate(std::wstring data) {
	Pacientka p;
	p.load(data);
	return p;
}
void Pacientka::setPoznamka(std::wstring _pm)
{
	poznamka = _pm;
}

void Pacientka::setMeno(std::wstring _meno)
{
	meno = _meno;
}

void Pacientka::setRodneCislo(std::wstring _rc)
{
	rodneCislo = _rc;
}

void Pacientka::setTelCislo(std::wstring _tc)
{
	telefonneCislo = _tc;
}

void Pacientka::setZmluvnaPoistovna(std::wstring _zp)
{
	zmluvnaPoistovna = _zp;
}

void Pacientka::setZmluvnyLekar(std::wstring _zl)
{
	zmluvnyLekar = _zl;
}

// Meno, RC, TC, ZP, ZL, Poznamka
UINT Pacientka::matching(const std::vector<std::wstring> & hladane) const
{
	UINT editDistFilters = 0;
	if (hladane.size() != 6) throw std::invalid_argument("The string array doesn't have size 6");
	if (hladane[0] != L"") editDistFilters += editDist(hladane[0], meno);
	if (hladane[1] != L"") editDistFilters += editDist(hladane[1], rodneCislo);
	if (hladane[2] != L"") editDistFilters += editDist(hladane[2], telefonneCislo);
	if (hladane[3] != L"") editDistFilters += editDist(hladane[3], zmluvnaPoistovna);
	if (hladane[4] != L"") editDistFilters += editDist(hladane[4], zmluvnyLekar);
	if (hladane[5] != L"") editDistFilters += editDist(hladane[5], poznamka);
	return editDistFilters;
}

