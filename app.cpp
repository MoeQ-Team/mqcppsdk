#include "include/mqcppsdk/mqcppsdk.h"

#if defined(_WIN_PLATFORM_)
#define FUNC(ReturnType, FuncName, ...) extern "C" __declspec(dllexport) ReturnType __stdcall FuncName(__VA_ARGS__)
#endif

#if defined(_LINUX_PLATFORM_)
#define FUNC(ReturnType, FuncName, ...) extern "C" __attribute__((visibility("default"))) ReturnType FuncName(__VA_ARGS__)
#endif

MoeQ MQ;

/// <summary>
/// MoeQ plugin init
/// MoeQ插件初始化
/// </summary>
/// <param name="AuthCode">AuthCode 授权码</param>
/// <returns>Sdk version Sdk版本</returns>
FUNC(int, Initialize, const uint64_t AuthCode)
{
    //Please don't write any code in the function
    //请勿在此函数写任何代码
    MQ.Initialize();
    MQ.SetAuthCode(AuthCode);
    return MOEQ_SDK_VERSION;
}

/// <summary>
/// MoeQ plugin life cycle event(EventID 0,100-103)
/// MoeQ插件生命周期事件(事件ID 0,100-103)
/// </summary>
/// <param name="LifeCycleEventType">Life cycle event type 生命周期事件类型</param>
FUNC(void, MQ_LifeCycleEvent, const Event::LifeCycleEvent::LifeCycleEventType LifeCycleEventType)
{
    switch (LifeCycleEventType)
    {
    case Event::LifeCycleEvent::LifeCycleEventType::StartUp:
        // MoeQ starts up(EventID 100)
        // MoeQ启动(事件ID 100)

        //Write your init code here
        //在此编写您的初始化代码

        break;
    case Event::LifeCycleEvent::LifeCycleEventType::ShutDown:
        // MoeQ shuts down(EventID 101)
        // MoeQ关闭(事件ID 101)

        break;
    case Event::LifeCycleEvent::LifeCycleEventType::PluginEnabled:
        // Plugin was Enabled(EventID 102)
        // 插件已启用(事件ID 102)
        // Note:It can be call when MoeQ starts up
        // 提示:此函数可在MoeQQ启动时被调用

        break;
    case Event::LifeCycleEvent::LifeCycleEventType::PluginDisabled:
        // Plugin was disabled(EventID 103)
        // 插件将被禁用(事件ID 103)
        // Note:It can be call when MoeQ shuts down
        // 提示:此函数可在MoeQQ关闭时被调用

        break;
    }
}

/// <summary>
/// MoeQ message event(EventID 1,1000-1002)
/// MoeQ消息事件(事件ID 1,1000-1002)
/// </summary>
/// <param name="Target">Sender Information 发送者信息</param>
/// <param name="Msg">Received Message 收到消息</param>
/// <param name="MsgID">Message ID 消息ID</param>
/// <returns>Block or Ignore 阻塞或忽略</returns>
FUNC(Event::ReturnType, MQ_MessageEvent, const Target::Target *Target, const Message::Msg *Msg, const uint64_t MsgID)
{
    switch (Target->TargetType)
    {
    case Target::TargetType::_private:
        //Private message(EventID 1000)
        //私聊消息(事件ID 1000)
        break;
    case Target::TargetType::group:
        //Group message(EventID 1001)
        //群聊消息(事件ID 1001)

        //Write your process code here
        //在此写你的处理代码

        //MQ.SendLike(((Target::group *)Target->Sender)->FromQQ, 1);

        //if you don't want this message to be processed by other plugins
        //如果你不想让此消息被其他插件处理
        //You can uncomment the following code
        //你可以取消下面这句代码的注释

        //return Event::ReturnType::block;

        break;
    case Target::TargetType::discuss:
        //Discuss message(EventID 1002)
        //讨论组消息(事件ID 1002)
        break;
    }
    return Event::ReturnType::ignore;
}

/// <summary>
/// MoeQ notice event(EventID 2,1003-1007)
/// MoeQ提醒事件(事件ID 2,1003-1007)
/// </summary>
/// <param name="NoticeEvent">Notice event information 提醒事件信息</param>
/// <returns>Block or Ignore 阻塞或忽略</returns>
FUNC(Event::ReturnType, MQ_NoticeEvent, const Event::NoticeEvent::NoticeEvent *NoticeEvent)
{
    switch (NoticeEvent->NoticeEventType)
    {
    case Event::NoticeEvent::NoticeEventType::group_fileupload:
        //Group file upload(EventID 1003)
        //群文件上传(事件ID 1003)
        break;
    case Event::NoticeEvent::NoticeEventType::group_adminchange:
        //Group administrator changes(EventID 1004)
        //群管理员变动(事件ID 1004)
        break;
    case Event::NoticeEvent::NoticeEventType::group_memberchange:
        //The change in the number of group members(EventID 1005)
        //群成员数量变动(事件ID 1005)
        break;
    case Event::NoticeEvent::NoticeEventType::group_mute:
        //Group ban(EventID 1006)
        //群禁言(事件ID 1006)
        break;
    case Event::NoticeEvent::NoticeEventType::friend_added:
        //Friend add(EventID 1007)
        //好友已添加(事件ID 1007)
        break;
    }
    return Event::ReturnType::ignore;
}

/// <summary>
/// MoeQ notice event(EventID 3,1008-1009)
/// MoeQ请求事件(事件ID 3,1008-1009)
/// </summary>
/// <param name="RequestEvent">Request event information 请求事件信息</param>
/// <returns>Agree,Disagree or Ignore 同意,不同意或忽略</returns>
FUNC(Event::RequestEvent::ReturnType, MQ_RequestEvent, const Event::RequestEvent::RequestEvent *RequestEvent, const uint32_t responseFlag)
{
    switch (RequestEvent->RequestEventType)
    {
    case Event::RequestEvent::RequestEventType::add_friend:
        //Add friend(EventID 1008)
        //加好友(事件ID 1008)
        break;
    case Event::RequestEvent::RequestEventType::add_group:
        //Add group(EventID 1009)
        //加群(事件ID 1009)
        break;
    }
    return Event::RequestEvent::ReturnType::ignore;
}

/// <summary>
/// User open menu
/// 用户打开菜单
/// </summary>
/// <param name="ID">Menu ID 菜单ID</param>
FUNC(void, Menu, const uint32_t ID)
{
    switch (ID)
    {
    case 0:
        //Menu1
        //菜单1

        break;
    case 1:
        //Menu2
        //菜单2

        break;
        //...
    }
}

#undef FUNC