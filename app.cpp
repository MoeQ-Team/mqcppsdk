// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "include\mqcppsdk\MoeQ.h"

MoeQ MQ;

/// <summary>
/// 
/// MoeQ插件初始化
/// </summary>
/// <param name="AuthCode">授权码</param>
/// <returns></returns>
__declspec(dllexport) int Initialize(int64_t AuthCode)
{
	//Please don't write any code in zhe function
	//请勿在此函数写任何代码
	MQ.SetAuthCode(AuthCode);
	return MOEQ_SDK_VERSION;
}

/// <summary>
/// MoeQ starts up(EventID 100)
/// MoeQ启动(EventID 100)
/// </summary>
__declspec(dllexport) void MQ_StartUp()
{
	//Write your init code here
	//在此编写您的初始化代码

}

/// <summary>
/// MoeQ shuts down(EventID 101)
/// MoeQ关闭(EventID 101)
/// </summary>
__declspec(dllexport) void MQ_ShutDown()
{

}

/// <summary>
/// Plugin was Enabled(EventID 105)
/// 插件已启用(EventID 105)
/// Note:It can be call when MoeQ starts up
/// 提示:它有可能会在MoeQQ启动时被调用
/// </summary>
__declspec(dllexport) void MQ_PluginEnabled()
{

}

/// <summary>
/// Plugin was disabled(EventID 106)
/// 插件将被禁用(EventID 106)
/// Note:It won't be call when MoeQ shuts down
/// 提示:它不会在MoeQ关闭时被调用
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
	//请勿在此函数写任何代码
	//Write your init code in the function MQ_StartUp
	//在函数MQ_StartUp中编写您的初始化代码
	return TRUE;
}