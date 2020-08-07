#pragma once
#include "Defined.h"

#include <Windows.h>
#include <vector>
#include <chrono>

namespace Utils
{
	byte* MD5(const byte* bin, const size_t length);

	long CurrentTimeMillis();
};

namespace XBin
{
	byte* Int2Bin(const uint i);
	void Int2Bin(const uint i, byte* bin);
	uint Bin2Int(const byte* bin);
}

namespace Iconv
{
	wchar_t* Utf82Unicode(char* szU8);
}
