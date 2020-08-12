# MoeQ C++ SDK

MoeQ C++ SDK(或称 mqcppsdk,MQCPPSDK)

## 极简示例

```cpp
#include <cqcppsdk/mqcppsdk.h>

extern "C" __declspec(dllexport) Event::ReturnType __stdcall MQ_MessageEvent(const Target::Target* Target, const Message::Msg* Msg, const uint MsgID)
{
	switch (Target->TargetType)
	{
	case Target::TargetType::group:
		if (!MQ.SendGroupMsg(((Target::group*)Target->Sender)->FromGroup, Msg)) MQ.AddLog(Log::LogType::WARNING,Log::MsgType::PROGRAM,L"群聊", L"复读失败");
		break;
	}
	return Event::ReturnType::ignore;
}

```

## 问题反馈

如果使用过程中遇到任何问题,Bug,或有其它意见或建议,欢迎提 [issue](https://github.com/YuFanXing/mqcppsdk/issues/new)。
