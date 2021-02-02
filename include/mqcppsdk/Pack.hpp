#pragma once
#include "Utils.hpp"

class ByteInputStream
{
private:
	const byte* Buffer;
	uint Offset;
public:
	ByteInputStream(const byte* buffer)
	{
		Buffer = buffer;
		Offset = 0;
	}
public:
	bool Check(const uint len, const uint i)
	{
		return len >= Offset + i;
	}

	void Set(const byte* buffer)
	{
		Buffer = buffer;
		Offset = 0;
	}

	void Skip(uint i)
	{
		Offset += i;
	}

	unsigned __int8 GetByte()
	{
		return Buffer[Offset++];
	}

	unsigned __int16 GetShort()
	{
		unsigned __int16 i;
		i = Buffer[Offset] << 8;
		i |= Buffer[++Offset];
		++Offset;
		return i;
	}

	unsigned __int32 GetInt()
	{
		unsigned __int32 i;
		i = Buffer[Offset] << 24;
		i |= Buffer[++Offset] << 16;
		i |= Buffer[++Offset] << 8;
		i |= Buffer[++Offset];
		++Offset;
		return  i;
	}

	unsigned __int64 GetLong()
	{
		unsigned __int64 i;
		i = (unsigned long long)Buffer[Offset] << 56;
		i |= (unsigned long long)Buffer[++Offset] << 48;
		i |= (unsigned long long)Buffer[++Offset] << 40;
		i |= (unsigned long long)Buffer[++Offset] << 32;
		i |= (unsigned long long)Buffer[++Offset] << 24;
		i |= (unsigned long long)Buffer[++Offset] << 16;
		i |= (unsigned long long)Buffer[++Offset] << 8;
		i |= (unsigned long long)Buffer[++Offset];
		++Offset;
		return i;
	}

	float GetFloat()
	{
		return 0.0f;
	}

	double GetDouble()
	{
		return 0.0;
	}

	const byte* GetBin(const uint len)
	{
		uint tmp = Offset;
		Skip(len);
		return Buffer + tmp;
	}

	const byte* GetCurrentPoint()
	{
		return Buffer + Offset;
	}

	uint GetReadedLength()
	{
		return Offset;
	}
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
		Skip(4);
		BufferLen = XBin::Bin2Int(buffer);
	};
public:
	void Reset(const byte* buffer, const uint bufferlen)
	{
		ByteInputStream::Set(buffer);
		BufferLen = bufferlen;
	}

	//自动跳长度
	void Reset(const LPBYTE buffer)
	{
		ByteInputStream::Set(buffer);
		ByteInputStream::Skip(4);
		BufferLen = XBin::Bin2Int(buffer);
	}

	void Reset(const std::vector<byte>* buffer)
	{
		ByteInputStream::Set((*buffer).data());
		BufferLen = (*buffer).size();
	}

	unsigned __int8 GetByte()
	{
		if (Check(BufferLen, 1)) return ByteInputStream::GetByte();
	}

	unsigned __int16 GetShort()
	{
		if (Check(BufferLen, 2)) return ByteInputStream::GetShort();
	}

	unsigned __int32 GetInt()
	{
		if (Check(BufferLen, 4)) return ByteInputStream::GetInt();
	}

	unsigned __int64 GetLong()
	{
		if (Check(BufferLen, 8)) return ByteInputStream::GetLong();
	}

	float GetFloat()
	{
		if (Check(BufferLen, 4)) return ByteInputStream::GetFloat();
	}

	double GetDouble()
	{
		if (Check(BufferLen, 8)) return ByteInputStream::GetDouble();
	}

	const char* GetStr(const uint len)
	{
		if (Check(BufferLen, len)) return (const char*)ByteInputStream::GetBin(len);
	}

	const byte* GetBin(const uint len)
	{
		if (Check(BufferLen, len)) return ByteInputStream::GetBin(len);
	}

	const LPBYTE GetBin()
	{
		uint len = GetInt() - 4;
		if (Check(BufferLen, len)) return (const LPBYTE)(ByteInputStream::GetBin(len) - 4);
	}

	uint GetLeftLength()
	{
		return BufferLen - ByteInputStream::GetReadedLength();
	}


};

class ByteOutputStream
{
private:
	byte* Buffer;
	uint Offset;
public:
	ByteOutputStream(byte* buffer)
	{
		Buffer = buffer;
		Offset = 0;
	}
public:
	bool Check(const uint len, const uint i)
	{
		return len >= Offset + i;
	}

	void Reset()
	{
		Offset = 0;
	}

	void Set(byte* buffer)
	{
		Buffer = buffer;
	}

	void Skip(const uint i)
	{
		Offset += i;
	}

	void SetByte(const unsigned __int8 i)
	{
		Buffer[Offset++] = i;
	}

	void SetShort(const unsigned __int16 i)
	{
		Buffer[Offset] = i >> 8;
		Buffer[++Offset] = i;
		++Offset;
	}

	void SetInt(const unsigned __int32 i)
	{
		Buffer[Offset] = i >> 24;
		Buffer[++Offset] = i >> 16;
		Buffer[++Offset] = i >> 8;
		Buffer[++Offset] = i;
		++Offset;
	}

	void SetLong(const unsigned __int64 i)
	{
		Buffer[Offset] = i >> 56;
		Buffer[++Offset] = i >> 48;
		Buffer[++Offset] = i >> 40;
		Buffer[++Offset] = i >> 32;
		Buffer[++Offset] = i >> 24;
		Buffer[++Offset] = i >> 16;
		Buffer[++Offset] = i >> 8;
		Buffer[++Offset] = i;
		++Offset;
	}

	void SetFloat(const float i)
	{
		Buffer[++Offset] = (byte)(&i + 3);
		Buffer[++Offset] = (byte)(&i + 2);
		Buffer[++Offset] = (byte)(&i + 1);
		Buffer[++Offset] = (byte)&i;
		++Offset;
	}

	void SetDouble(const double i)
	{
		Buffer[Offset] = (byte)(&i + 7);
		Buffer[++Offset] = (byte)(&i + 6);
		Buffer[++Offset] = (byte)(&i + 5);
		Buffer[++Offset] = (byte)(&i + 4);
		Buffer[++Offset] = (byte)(&i + 3);
		Buffer[++Offset] = (byte)(&i + 2);
		Buffer[++Offset] = (byte)(&i + 1);
		Buffer[++Offset] = (byte)&i;
		++Offset;
	}

	void SetBin(const byte* bin, const uint len)
	{
		memcpy(Buffer + Offset, bin, len);
		Offset += len;
	}

	//带长度写入
	void SetBin(const LPBYTE bin)
	{
		memcpy(Buffer + Offset, bin, XBin::Bin2Int(bin));
		Offset += XBin::Bin2Int(bin);
	}

	byte* GetCurrentPoint()
	{
		return Buffer + Offset;
	}

	uint Length()
	{
		return Offset;
	}

	byte* GetAll()
	{
		return Buffer;
	}

	uint GetAll(byte*& buf)
	{
		buf = Buffer;
		return Offset;
	}

};

#define CheckBufferLen(len) if (!Check(BufferLen, len)) Expansion (!Check(BufferLen + 300, len) ? len : 300)

class Pack :public ByteOutputStream
{
private:
	uint BufferLen;
public:
	Pack(const uint bufferlen = 300, bool Length = false) :ByteOutputStream(new byte[bufferlen])
	{
		if (Length) Skip(4);
		BufferLen = bufferlen;
	};
public:
	void SetLength()
	{
		uint len = ByteOutputStream::Length();
		byte* Buffer = ByteOutputStream::GetAll();
		Buffer[0] = len >> 24;
		Buffer[1] = len >> 16;
		Buffer[2] = len >> 8;
		Buffer[3] = len;
	}

	void Expansion(uint len)
	{
		BufferLen += len;
		byte* tmp = new byte[BufferLen];
		memcpy(tmp, ByteOutputStream::GetAll(), ByteOutputStream::Length());
		delete[] ByteOutputStream::GetAll();
		ByteOutputStream::Set(tmp);
	}

	void SetByte(const unsigned __int8 i)
	{
		CheckBufferLen(1);
		ByteOutputStream::SetByte(i);
	}

	void SetShort(const unsigned __int16 i)
	{
		CheckBufferLen(2);
		ByteOutputStream::SetShort(i);
	}

	void SetInt(const unsigned __int32 i)
	{
		CheckBufferLen(4);
		ByteOutputStream::SetInt(i);
	}

	void SetLong(const unsigned __int64 i)
	{
		CheckBufferLen(8);
		ByteOutputStream::SetLong(i);
	}

	void SetFloat(const float i)
	{
		CheckBufferLen(4);
		ByteOutputStream::SetFloat(i);
	}

	void SetDouble(const double i)
	{
		CheckBufferLen(8);
		ByteOutputStream::SetDouble(i);
	}

	void SetStr(const char* str)
	{
		unsigned int len = strlen(str);
		CheckBufferLen(len);
		ByteOutputStream::SetBin((byte*)str, len);
	}

	void SetBin(const byte* bin, const uint len)
	{
		CheckBufferLen(len);
		ByteOutputStream::SetBin(bin, len);
	}

	//带长度写入
	void SetBin(const LPBYTE bin)
	{
		CheckBufferLen(XBin::Bin2Int(bin));
		ByteOutputStream::SetBin(bin);
	}

	void SetBin(const std::vector<byte>* bin)
	{
		uint len = (*bin).size();
		CheckBufferLen(len);
		ByteOutputStream::SetBin((*bin).data(), len);
	}

	//会自动delete参数
	void SetBin_(const byte* bin, const uint len)
	{
		CheckBufferLen(len);
		ByteOutputStream::SetBin(bin, len);
		delete[] bin;
	}

	//带长度写入,会自动delete参数
	void SetBin_(const LPBYTE bin)
	{
		CheckBufferLen(XBin::Bin2Int(bin));
		ByteOutputStream::SetBin(bin);
		delete[] bin;
	}

	//申请新的内存返回且清空
	byte* GetAll_(bool Length)
	{
		byte* bin = new byte[ByteOutputStream::Length()];
		memcpy(bin, ByteOutputStream::GetAll(), ByteOutputStream::Length());
		ByteOutputStream::Reset();
		if (Length) ByteOutputStream::Skip(4);
		return bin;
	}

	uint GetAll_(byte*& bin, bool Length)
	{
		uint len = ByteOutputStream::Length();
		bin = new byte[len];
		memcpy(bin, ByteOutputStream::GetAll(), len);
		ByteOutputStream::Reset();
		if (Length) ByteOutputStream::Skip(4);
		return len;
	}

	uint GetLeftSpace()
	{
		return BufferLen - ByteOutputStream::Length();
	}
};

#undef CheckBufferLen