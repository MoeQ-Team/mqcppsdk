#include "../../include/utils/utils.h"

byte *XBin::Int2Bin(const uint32_t i)
{
    byte *bin = new byte[4];
    bin[0] = i >> 24;
    bin[1] = i >> 16;
    bin[2] = i >> 8;
    bin[3] = (byte)i;
    return bin;
}

void XBin::Int2Bin(const uint32_t i, byte *bin)
{
    bin[0] = i >> 24;
    bin[1] = i >> 16;
    bin[2] = i >> 8;
    bin[3] = (byte)i;
}

uint32_t XBin::Bin2Int(const byte *bin)
{
    return bin[0] << 24 | bin[1] << 16 | bin[2] << 8 | bin[3];
}