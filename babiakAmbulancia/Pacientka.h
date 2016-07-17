#pragma once
#include <string>
#include "stdafx.h"

#include <vector>
class Patient {
	std::wstring m_name;
	std::wstring m_birthNumber;
	std::wstring m_phoneNumber;
	std::wstring m_insurance;
	std::wstring m_doctor;
	std::wstring m_note;
	//creationTime funguje tiez ako unikatne ID pre pacientky
	time_t m_creationTime;
public:
	Patient() = default;
	Patient(bool nova);
	Patient(std::wstring _meno, std::wstring _rodneCislo, std::wstring _telefonneCislo,
		std::wstring _zmluvnaPoistovna, std::wstring _zmluvnyLekar, std::wstring _poznamka);
	
	time_t getID();
	std::wstring getIDasString();
	std::wstring getNote();
	std::wstring getName();
	std::wstring getBirthNumber();
	std::wstring getPhoneNumber();
	std::wstring getInsurance();
	std::wstring getDoctor();

	std::wstring ExportSerialize();
	void Load(std::wstring);

	void setNote(std::wstring);
	void setName(std::wstring);
	void setBirthNumber(std::wstring);
	void setPhoneNumber(std::wstring);
	void setInsurance(std::wstring);
	void setDoctor(std::wstring);

	uint32_t matchIndex(const std::vector<std::wstring> & hladane) const;
};

Patient LoadCreate(std::wstring data);

