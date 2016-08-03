#include "stdafx.h"
#include "Patient.h"
#include "../Shared/Helpers.h"

#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>
#include <ctime>

#include "../Shared/bytes/StrUtils.h"
#include "../Shared/bytes/ZipBytes.h"

inline Patient::Patient(bool nova) {
	if (nova)
		m_creationTime = time(NULL);
}

Patient::Patient(std::wstring _meno, std::wstring _rodneCislo, std::wstring _telefonneCislo, std::wstring _zmluvnaPoistovna, std::wstring _zmluvnyLekar, std::wstring _poznamka) {
	m_creationTime = time(NULL);
	m_name = _meno;
	m_birthNumber = _rodneCislo;
	m_phoneNumber = _telefonneCislo;
	m_insurance = _zmluvnaPoistovna;
	m_doctor = _zmluvnyLekar;
	m_note = _poznamka;
}

time_t Patient::getID()
{
	return m_creationTime;
}

std::wstring Patient::getIDasString()
{
	return std::to_wstring(m_creationTime);
}

std::wstring Patient::getNote()
{
	return m_note;
}

std::wstring Patient::getName()
{
	return m_name;
}

std::wstring Patient::getBirthNumber()
{
	return m_birthNumber;
}

std::wstring Patient::getPhoneNumber()
{
	return m_phoneNumber;
}

std::wstring Patient::getInsurance()
{
	return m_insurance;
}

std::wstring Patient::getDoctor()
{
	return m_doctor;
}

std::string Patient::ExportSerialize()
{
	std::vector<std::string> strVec = { std::to_string(m_creationTime), GetBytes(m_name), GetBytes(m_birthNumber),
		GetBytes(m_phoneNumber), GetBytes(m_insurance), GetBytes(m_doctor), GetBytes(m_note) };
	return ZipByteVectors(strVec);
}

void Patient::Load(std::string data)
{
	std::vector<std::string> V = UnzipToByteVectors(data);
	m_creationTime = std::stoi(V[0]);
	m_name = BytesToWstring(V[1]);
	m_birthNumber = BytesToWstring(V[2]);
	m_phoneNumber = BytesToWstring(V[3]);
	m_insurance = BytesToWstring(V[4]);
	m_doctor = BytesToWstring(V[5]);
	m_note = BytesToWstring(V[6]);
}

Patient LoadCreate(const std::string & data) {
	Patient p;
	p.Load(data);
	return p;
}

void Patient::setNote(std::wstring _pm)
{
	m_note = _pm;
}

void Patient::setName(std::wstring _meno)
{
	m_name = _meno;
}

void Patient::setBirthNumber(std::wstring _rc)
{
	m_birthNumber = _rc;
}

void Patient::setPhoneNumber(std::wstring _tc)
{
	m_phoneNumber = _tc;
}

void Patient::setInsurance(std::wstring _zp)
{
	m_insurance = _zp;
}

void Patient::setDoctor(std::wstring _zl)
{
	m_doctor = _zl;
}

// Meno, RC, TC, ZP, ZL, Poznamka
uint32_t Patient::MatchIndex(const std::vector<std::wstring> & hladane) const
{
	uint32_t editDistFilters = 0;
	if (hladane.size() != 6) throw std::invalid_argument("The string array doesn't have size 6");
	if (hladane[0] != L"") editDistFilters += StringEditDistance(hladane[0], m_name);
	if (hladane[1] != L"") editDistFilters += StringEditDistance(hladane[1], m_birthNumber);
	if (hladane[2] != L"") editDistFilters += StringEditDistance(hladane[2], m_phoneNumber);
	if (hladane[3] != L"") editDistFilters += StringEditDistance(hladane[3], m_insurance);
	if (hladane[4] != L"") editDistFilters += StringEditDistance(hladane[4], m_doctor);
	if (hladane[5] != L"") editDistFilters += StringEditDistance(hladane[5], m_note);
	return editDistFilters;
}

