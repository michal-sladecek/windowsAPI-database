#include "stdafx.h"
#include "Doktor.h"
#include <vector>

std::wstring Doktor::exportSerialize()
{
	std::wstring serialized;
	std::wstring beg(TEXT("(")), en(TEXT(")")), oddelovac(TEXT("|"));
	serialized = beg +meno+oddelovac+authHash+en;
	return serialized;
}

void Doktor::load(std::wstring data)
{
	size_t len = data.length();
	if (data[0] != '(')throw std::invalid_argument("Doktor is not in the right format");
	if (data[len - 1] != ')')throw std::invalid_argument("Doktor is not in the right format");

	size_t beg = 1;
	std::vector<std::wstring> V;
	for (size_t i = 1; i < len; i++) {
		if (data[i] == '|' || data[i] == ']') {
			V.push_back(data.substr(beg, i - beg));
			beg = i + 1;
		}
	}
	meno = V[0];
	authHash = V[1];
}
