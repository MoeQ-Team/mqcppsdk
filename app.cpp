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
	//�ڴ˱�д���ĳ�ʼ������

}



BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	//Please don't write any code in zhe function
	//�����ڴ˺���д�κδ���
	//Write your init code in the function MQ_StartUp
	//�ں���MQ_StartUp�б�д���ĳ�ʼ������
	return TRUE;
}