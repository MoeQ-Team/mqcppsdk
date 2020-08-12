# MoeQ C++ SDK

MoeQ C++ SDK(��� mqcppsdk,MQCPPSDK)

## ����ʾ��

```cpp
#include <cqcppsdk/mqcppsdk.h>

extern "C" __declspec(dllexport) Event::ReturnType __stdcall MQ_MessageEvent(const Target::Target* Target, const Message::Msg* Msg, const uint MsgID)
{
	switch (Target->TargetType)
	{
	case Target::TargetType::group:
		if (!MQ.SendGroupMsg(((Target::group*)Target->Sender)->FromGroup, Msg)) MQ.AddLog(Log::LogType::WARNING,Log::MsgType::PROGRAM,L"Ⱥ��", L"����ʧ��");
		break;
	}
	return Event::ReturnType::ignore;
}

```

## ���ⷴ��

���ʹ�ù����������κ�����,Bug,���������������,��ӭ�� [issue](https://github.com/YuFanXing/mqcppsdk/issues/new)��
