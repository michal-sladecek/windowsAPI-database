#include "stdafx.h"
#include "Databaza.h"
#include "Pacientka.h"


std::vector<Pacientka> & Databaza::as_list() {
	return pacientky;
}
void Databaza::pridaj(Pacientka p)
{
	pacientky.push_back(p);
}

std::wstring Databaza::exportSerialize()
{
	std::wstring beg = L"{", en = L"}", oddelovac = L"|";
	std::wstring writeout = beg;
	for (auto p : pacientky) {
		writeout += p.exportSerialize() + oddelovac;
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
			pacientky.push_back(loadCreate(data.substr(beg, i - beg + 1)));
		}
		else if (data[i] == '[') beg = i;
	}
}

UINT32 Databaza::numberEntries()
{
	return pacientky.size();
}
