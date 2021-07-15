#include "../../include/utils/utils.h"

uint8_t *XBin::Int2Bin(const uint32_t i)
{
    uint8_t *bin = new uint8_t[4];
    bin[0] = i >> 24;
    bin[1] = i >> 16;
    bin[2] = i >> 8;
    bin[3] = (uint8_t)i;
    return bin;
}

void XBin::Int2Bin(const uint32_t i, uint8_t *bin)
{
    bin[0] = i >> 24;
    bin[1] = i >> 16;
    bin[2] = i >> 8;
    bin[3] = (uint8_t)i;
}

uint32_t XBin::Bin2Int(const uint8_t *bin)
{
    return bin[0] << 24 | bin[1] << 16 | bin[2] << 8 | bin[3];
}