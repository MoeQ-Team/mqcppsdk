#pragma once

#include <vector>
#include <stdint.h>

typedef unsigned char *LPBYTE;

namespace XBin
{
    uint8_t* Int2Bin(const uint32_t i);
    void Int2Bin(const uint32_t i, uint8_t* bin);
    uint32_t Bin2Int(const uint8_t* bin);
}