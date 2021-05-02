#pragma once

#include <string>

#include "utils.h"

class ByteInputStream
{
private:
	const byte* Buffer;
	uint32_t Offset;
public:
	ByteInputStream(const byte* buffer);
public:
	bool Check(const uint32_t len, const uint32_t i);
	void Set(const byte* buffer);
	void Skip(const uint32_t i);
	uint8_t GetByte();
	uint16_t GetShort();
	uint32_t GetInt();
	uint64_t GetLong();
	float GetFloat();
	double GetDouble();
	const byte* GetBin(const uint32_t len);
	const byte* GetCurrentPoint();
	uint32_t GetReadedLength();
};

class UnPack :public ByteInputStream
{
private:
	uint32_t BufferLen;
public:
	UnPack(const byte* buffer, const uint32_t bufferlen) :ByteInputStream(buffer)
	{
		BufferLen = bufferlen;
	};
	UnPack(const LPBYTE buffer) :ByteInputStream(buffer)//自动跳掉长度
	{
		ByteInputStream::Skip(4);
		BufferLen = XBin::Bin2Int(buffer);
	};
public:
	void Reset(const byte* buffer, const uint32_t bufferlen);
	void Reset(const LPBYTE buffer);
	void Reset(const std::vector<byte>* buffer);
	uint8_t GetByte();
	uint16_t GetShort();
	uint32_t GetInt();
	uint64_t GetLong();
	float GetFloat();
	double GetDouble();
	const char* GetStr(const uint32_t len);
	const byte* GetBin(const uint32_t len);
	const LPBYTE GetBin();
	uint32_t GetLeftLength();
};