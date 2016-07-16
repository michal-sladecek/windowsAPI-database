#include "stdafx.h"
#include "Databaza.h"
#include "Pacientka.h"

#include <utility>
#include <algorithm>

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
		V[i] = { pacientky[i].matching(hladane),i };
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

Pacientka & Databaza::queryGet(uint32_t index)
{
	if (index >= query.size())
	{
		throw std::out_of_range("");
	}
	return pacientky[query[index]];
}
