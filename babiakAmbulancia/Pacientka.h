#pragma once
#include <string>
#include "stdafx.h"

class Pacientka {
	std::wstring meno;
	std::wstring rodneCislo;
	std::wstring telefonneCislo;
	std::wstring zmluvnaPoistovna;
	std::wstring zmluvnyLekar;
	std::wstring poznamka;
	time_t creationTime;
public:
	Pacientka();
	Pacientka(BOOL nova);
	Pacientka(std::wstring _meno, std::wstring _rodneCislo, std::wstring _telefonneCislo,
		std::wstring _zmluvnaPoistovna, std::wstring _zmluvnyLekar, std::wstring _poznamka);
	time_t getID();
	std::wstring getPoznamka();
	std::wstring getMeno();
	std::wstring getRodneCislo();
	std::wstring getTelCislo();
	std::wstring getZmluvnaPoistovna();
	std::wstring getZmluvnyLekar();

	std::wstring exportSerialize();
	void load(std::wstring);

	void setPoznamka(std::wstring);
	void setMeno(std::wstring);
	void setRodneCislo(std::wstring);
	void setTelCislo(std::wstring);
	void setZmluvnaPoistovna(std::wstring);
	void setZmluvnyLekar(std::wstring);
};

Pacientka loadCreate(std::wstring data);

