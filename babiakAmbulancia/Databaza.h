#pragma once
#include "stdafx.h"
#include "Pacientka.h"
#include <vector>

class Databaza {
	std::vector<Pacientka> pacientky;
public:
	std::vector<Pacientka> & as_list();
	void pridaj(Pacientka p);
	std::wstring exportSerialize();
	void load(std::wstring data);

	UINT32 numberEntries();
};