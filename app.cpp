// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "include\mqcppsdk\MoeQ.h"

MoeQ MQ;

__declspec(dllexport) int Initialize(int64_t AuthCode)
{
	MQ.SetAuthCode(AuthCode);
	return 1;
}

__declspec(dllexport) void MQ_StartUp()
{
	//Write your init code here
	//在此编写您的初始化代码

}



BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	//Please don't write any code in zhe function
	//请勿在此函数写任何代码
	//Write your init code in the function MQ_StartUp
	//在函数MQ_StartUp中编写您的初始化代码
	return TRUE;
}