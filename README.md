# MoeQ C++ SDK

MoeQ C++ SDK(mqcppsdk)

## Use Way

```cpp
#include <cqcppsdk/mqcppsdk.h>

#if defined(_WIN_PLATFORM_)
#define FUNC(ReturnType, FuncName, ...) extern "C" __declspec(dllexport) ReturnType __stdcall FuncName(__VA_ARGS__)
#endif

#if defined(_LINUX_PLATFORM_)
#define FUNC(ReturnType, FuncName, ...) extern "C" __attribute__((visibility("default"))) ReturnType FuncName(__VA_ARGS__)
#endif

FUNC(Event::ReturnType, MQ_MessageEvent, const Target::Target *Target, const Message::Msg *Msg, const uint64_t MsgID)
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

## Feedback

如果使用过程中遇到任何问题,Bug,或有其它意见或建议,欢迎提 [issue](https://github.com/YuFanXing/mqcppsdk/issues/new).

欢迎加入QQ交流群 940674752 
