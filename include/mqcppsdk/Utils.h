#pragma once
#include "Defined.h"

#include <Windows.h>
#include <winnls.h>
#include <vector>
#include <chrono>

#include "..\openssl\md5.h"

#pragma comment(lib, "crypt32.lib")
#if _WIN64
#pragma comment(lib, "lib\\openssl_lib_windows\\x64\\libcrypto.lib")
#else
#pragma comment(lib, "..\\lib\\openssl_lib_windows\\x86\\libcrypto.lib")
#endif




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
