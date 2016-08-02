#include "stdafx.h"
#include "Hashing.h"

#include "crypto50\sha.h"
#include "crypto50\filters.h"
#include "crypto50\hex.h"
#include "../OffsetDB/StrUtils.h"


std::string GetHashValue(const std::wstring & string)
{
	CryptoPP::SHA256 hash;
	std::string digest;
	std::string str = GetBytes(string);
	CryptoPP::StringSource s(str, true, new CryptoPP::HashFilter(hash,new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

	return digest;
}
