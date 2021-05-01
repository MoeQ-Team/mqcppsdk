#pragma once

#include <vector>

#include <stdint.h>

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned char* LPBYTE;

namespace XBin
{
    byte* Int2Bin(const uint i);
    void Int2Bin(const uint i, byte* bin);
    uint Bin2Int(const byte* bin);
}