// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "include\mqcppsdk\mqcppsdk.hpp"

MoeQ MQ;

/// <summary>
/// MoeQ plugin init
/// MoeQ�����ʼ��
/// </summary>
/// <param name="AuthCode">AuthCode ��Ȩ��</param>
/// <returns>Sdk version Sdk�汾</returns>
extern "C" __declspec(dllexport) int __stdcall Initialize(const uint64_t AuthCode)
{
	//Please don't write any code in zhe function
	//�����ڴ˺���д�κδ���
	MQ.SetAuthCode(AuthCode);
	return MOEQ_SDK_VERSION;
}

/// <summary>
/// MoeQ plugin life cycle event(EventID 0,100-103)
/// MoeQ������������¼�(�¼�ID 0,100-103)
/// </summary>
/// <param name="LifeCycleEventType">Life cycle event type ���������¼�����</param>
extern "C" __declspec(dllexport) void __stdcall MQ_LifeCycleEvent(const Event::LifeCycleEvent::LifeCycleEventType LifeCycleEventType)
{
	switch (LifeCycleEventType)
	{
	case Event::LifeCycleEvent::LifeCycleEventType::StartUp:
		// MoeQ starts up(EventID 100)
		// MoeQ����(�¼�ID 100)

		//Write your init code here
		//�ڴ˱�д���ĳ�ʼ������

		break;
	case Event::LifeCycleEvent::LifeCycleEventType::ShutDown:
		// MoeQ shuts down(EventID 101)
		// MoeQ�ر�(�¼�ID 101)

		break;
	case Event::LifeCycleEvent::LifeCycleEventType::PluginEnabled:
		// Plugin was Enabled(EventID 102)
		// ���������(�¼�ID 102)
		// Note:It can be call when MoeQ starts up
		// ��ʾ:���п��ܻ���MoeQQ����ʱ������
	
		break;
	case Event::LifeCycleEvent::LifeCycleEventType::PluginDisabled:
		// Plugin was disabled(EventID 103)
		// �����������(�¼�ID 103)
		// Note:It won't be call when MoeQ shuts down
		// ��ʾ:��������MoeQ�ر�ʱ������
		
		break;
	}
}

/// <summary>
/// MoeQ message event(EventID 1,1000-1002)
/// MoeQ��Ϣ�¼�(�¼�ID 1,1000-1002)
/// </summary>
/// <param name="Target">Sender Information ��������Ϣ</param>
/// <param name="Msg">Received Message �յ���Ϣ</param>
/// <param name="MsgID">Message ID ��ϢID</param>
/// <returns>Block or Ignore ���������</returns>
extern "C" __declspec(dllexport) Event::ReturnType __stdcall MQ_MessageEvent(const Target::Target* Target, const Message::Msg* Msg, const uint MsgID)
{
	switch (Target->TargetType)
	{
	case Target::TargetType::_private:
		//Private message(EventID 1000)
		//˽����Ϣ(�¼�ID 1000)
		break;
	case Target::TargetType::group:
		//Group message(EventID 1001)
		//Ⱥ����Ϣ(�¼�ID 1001)

		//Write your process code here
		//�ڴ�д��Ĵ������
		MQ.SendLike(((Target::group*)Target->Sender)->FromQQ, 1);

		//if you don't want this message to be processed by other plugins
		//����㲻���ô���Ϣ�������������
		//You can uncomment the following code
		//�����ȡ�������������ע��
		//return Event::ReturnType::block;
		break;
	case Target::TargetType::discuss:
		//Discuss message(EventID 1002)
		//��������Ϣ(�¼�ID 1002)
		break;
	}
	return Event::ReturnType::ignore;
}

/// <summary>
/// MoeQ notice event(EventID 2,1003-1007)
/// MoeQ�����¼�(�¼�ID 2,1003-1007)
/// </summary>
/// <param name="NoticeEvent">Notice event information �����¼���Ϣ</param>
/// <returns>Block or Ignore ���������</returns>
extern "C" __declspec(dllexport) Event::ReturnType __stdcall MQ_NoticeEvent(const Event::NoticeEvent::NoticeEvent* NoticeEvent)
{
	switch (NoticeEvent->NoticeEventType)
	{
	case Event::NoticeEvent::NoticeEventType::group_fileupload:
		//Group file upload(EventID 1003)
		//Ⱥ�ļ��ϴ�(�¼�ID 1003)
		break;
	case Event::NoticeEvent::NoticeEventType::group_adminchange:
		//Group administrator changes(EventID 1004)
		//Ⱥ����Ա�䶯(�¼�ID 1004)
		break;
	case Event::NoticeEvent::NoticeEventType::group_memberchange:
		//The change in the number of group members(EventID 1005)
		//Ⱥ��Ա�����䶯(�¼�ID 1005)
		break;
	case Event::NoticeEvent::NoticeEventType::group_mute:
		//Group ban(EventID 1006)
		//Ⱥ����(�¼�ID 1006)
		break;
	case Event::NoticeEvent::NoticeEventType::friend_added:
		//Friend add(EventID 1007)
		//���������(�¼�ID 1007)
		break;
	}
	return Event::ReturnType::ignore;
}

/// <summary>
/// MoeQ notice event(EventID 3,1008-1009)
/// MoeQ�����¼�(�¼�ID 3,1008-1009)
/// </summary>
/// <param name="RequestEvent">Request event information �����¼���Ϣ</param>
/// <returns>Agree,Disagree or Ignore ͬ��,��ͬ������</returns>
extern "C" __declspec(dllexport) Event::RequestEvent::ReturnType __stdcall MQ_RequestEvent(const Event::RequestEvent::RequestEvent* RequestEvent, const uint responseFlag)
{
	switch (RequestEvent->RequestEventType)
	{
	case Event::RequestEvent::RequestEventType::add_friend:
		//Add friend(EventID 1008)
		//�Ӻ���(�¼�ID 1008)
		break;
	case Event::RequestEvent::RequestEventType::add_group:
		//Add group(EventID 1009)
		//��Ⱥ(�¼�ID 1009)
		break;
	}
	return Event::RequestEvent::ReturnType::ignore;
}

/// <summary>
/// User open menu
/// �û��򿪲˵�
/// </summary>
/// <param name="ID">Menu ID �˵�ID</param>
extern "C" __declspec(dllexport) void __stdcall Menu(const uint ID)
{
	switch (ID)
	{
	case 0:
		//Menu1
		//�˵�1

		break;
	case 1:
		//Menu2
		//�˵�2

		break;
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	//Please don't write any code in zhe function
	//�����ڴ˺���д�κδ���
	//Write your init code in the function MQ_LifeCycleEvent
	//�ں���MQ_LifeCycleEvent�б�д���ĳ�ʼ������
	return TRUE;
}