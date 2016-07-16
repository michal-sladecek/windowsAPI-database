#pragma once
#include "stdafx.h"
#include "Pacientka.h"
#include <vector>

class Databaza {
	std::vector<Pacientka> pacientky;
	std::vector<uint32_t> query;
public:
	void pridaj(Pacientka p);
	std::wstring exportSerialize();
	void load(std::wstring data);
	
	UINT32 numberEntries();
	

	void queryAll();
	void queryFind(const std::vector<std::wstring> & hladane, size_t num);
	uint32_t querySize();
	Pacientka & queryGet(uint32_t index);
};