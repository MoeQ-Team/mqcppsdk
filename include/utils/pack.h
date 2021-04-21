#pragma once

#include <string>

#include "utils.h"

class ByteInputStream
{
private:
	const byte* Buffer;
	uint Offset;
public:
	ByteInputStream(const byte* buffer);
public:
	bool Check(const uint len, const uint i);
	void Set(const byte* buffer);
	void Skip(const uint i);
	uint8_t GetByte();
	uint16_t GetShort();
	uint32_t GetInt();
	uint64_t GetLong();
	float GetFloat();
	double GetDouble();
	const byte* GetBin(const uint len);
	const byte* GetCurrentPoint();
	uint GetReadedLength();
};

class UnPack :public ByteInputStream
{
private:
	uint BufferLen;
public:
	UnPack(const byte* buffer, const uint bufferlen) :ByteInputStream(buffer)
	{
		BufferLen = bufferlen;
	};
	UnPack(const LPBYTE buffer) :ByteInputStream(buffer)//自动跳掉长度
	{
		ByteInputStream::Skip(4);
		BufferLen = XBin::Bin2Int(buffer);
	};
public:
	void Reset(const byte* buffer, const uint bufferlen);
	void Reset(const LPBYTE buffer);
	void Reset(const std::vector<byte>* buffer);
	uint8_t GetByte();
	uint16_t GetShort();
	uint32_t GetInt();
	uint64_t GetLong();
	float GetFloat();
	double GetDouble();
	const char* GetStr(const uint len);
	const byte* GetBin(const uint len);
	const LPBYTE GetBin();
	uint GetLeftLength();
};