#pragma once
#include <Windows.h>
#include <vector>
#include <stdint.h>

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned char* LPBYTE;

namespace XBin
{
	byte* Int2Bin(const uint i)
	{
		byte* bin = new byte[4];
		bin[0] = i >> 24;
		bin[1] = i >> 16;
		bin[2] = i >> 8;
		bin[3] = (byte)i;
		return bin;
	}

	void Int2Bin(const uint i, byte* bin)
	{
		bin[0] = i >> 24;
		bin[1] = i >> 16;
		bin[2] = i >> 8;
		bin[3] = (byte)i;
	}

	uint Bin2Int(const byte* bin)
	{
		return bin[0] << 24 | bin[1] << 16 | bin[2] << 8 | bin[3];
	}
}