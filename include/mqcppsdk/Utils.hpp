#pragma once
#include <Windows.h>
#include <vector>
#include <chrono>
#include <stdint.h>

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned char* LPBYTE;


namespace Utils
{
	long CurrentTimeMillis()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}
};

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

namespace Iconv
{
	/// <summary>
	/// Utf8�ַ���תWindows Unicode
	/// </summary>
	/// <param name="szU8">Utf8�ַ���</param>
	/// <returns>������ʹ����new,�ǵ���delete�ͷ�</returns>
	wchar_t* Utf82Unicode(char* szU8)
	{
		int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);
		//����ռ�Ҫ��'\0'�����ռ䣬MultiByteToWideChar�����'\0'�ռ�
		wchar_t* wszString = new wchar_t[wcsLen + 1];
		//ת��
		::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);
		//������'\0'
		wszString[wcsLen] = '\0';
		return wszString;
	}
}