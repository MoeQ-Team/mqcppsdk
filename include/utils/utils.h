#pragma once

#include <vector>

#include"../mqcppsdk/definition.h"

typedef unsigned char byte;
typedef unsigned char* LPBYTE;

namespace XBin
{
    byte* Int2Bin(const uint32_t i);
    void Int2Bin(const uint32_t i, byte* bin);
    uint32_t Bin2Int(const byte* bin);
}