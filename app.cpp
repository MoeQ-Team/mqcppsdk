// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "include\mqcppsdk\MoeQ.h"

MoeQ MQ;

/// <summary>
/// 
/// MoeQ�����ʼ��
/// </summary>
/// <param name="AuthCode">��Ȩ��</param>
/// <returns></returns>
__declspec(dllexport) int Initialize(int64_t AuthCode)
{
	//Please don't write any code in zhe function
	//�����ڴ˺���д�κδ���
	MQ.SetAuthCode(AuthCode);
	return MOEQ_SDK_VERSION;
}

/// <summary>
/// MoeQ starts up(EventID 100)
/// MoeQ����(EventID 100)
/// </summary>
__declspec(dllexport) void MQ_StartUp()
{
	//Write your init code here
	//�ڴ˱�д���ĳ�ʼ������

}

/// <summary>
/// MoeQ shuts down(EventID 101)
/// MoeQ�ر�(EventID 101)
/// </summary>
__declspec(dllexport) void MQ_ShutDown()
{

}

/// <summary>
/// Plugin was Enabled(EventID 105)
/// ���������(EventID 105)
/// Note:It can be call when MoeQ starts up
/// ��ʾ:���п��ܻ���MoeQQ����ʱ������
/// </summary>
__declspec(dllexport) void MQ_PluginEnabled()
{

}

/// <summary>
/// Plugin was disabled(EventID 106)
/// �����������(EventID 106)
/// Note:It won't be call when MoeQ shuts down
/// ��ʾ:��������MoeQ�ر�ʱ������
/// </summary>
__declspec(dllexport) void MQ_PluginDisabled()
{

}

__declspec(dllexport) uint MQ_Message()
{

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