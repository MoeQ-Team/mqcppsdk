#pragma once

#include "definition.h"
#include "../utils/pack.h"

#if defined(_WIN_PLATFORM_)
#include <Winbase.h>
#endif

#if defined(_LINUX_PLATFORM_)
#include <dlfcn.h>
#endif

class MoeQ
{
private:
    uint64_t AuthCode;

public:
    void Initialize();

    void SetAuthCode(uint64_t _AuthCode);

    /// <summary>
    /// 取登录账号的QQ号
    /// </summary>
    /// <returns></returns>
    uint32_t GetUin();

    /// <summary>
    /// 取Cookie(skey & Host对应的p_skey)(Auth 1)
    /// </summary>
    /// <param name="Host">p_skey的目标域名</param>
    /// <returns>记得销毁</returns>
    char *GetCookies(const char *Host);

    /// <summary>
    /// 点赞(Auth 2)
    /// </summary>
    /// <param name="QQ"></param>
    /// <param name="Times"></param>
    /// <returns></returns>
    bool SendLike(const uint32_t QQ, const int Times);

    /// <summary>
    /// 退出群(Auth 3)
    /// </summary>
    /// <param name="Group"></param>
    /// <returns></returns>
    bool LeaveGroup(const uint32_t Group);

    /// <summary>
    /// 退出讨论组(Auth 4)
    /// </summary>
    /// <param name="Disscuss"></param>
    /// <returns></returns>
    bool LeaveDiscuss(const uint32_t Disscuss);

    /// <summary>
    /// 发送私聊消息(Auth 5)
    /// </summary>
    /// <param name="QQ"></param>
    /// <param name="Msg"></param>
    /// <returns></returns>
    bool SendPrivateMsg(const uint32_t QQ, const Message::Msg *Msg);

    /// <summary>
    /// 发送群消息(Auth 6)
    /// </summary>
    /// <param name="Group"></param>
    /// <param name="Msg"></param>
    /// <returns></returns>
    bool SendGroupMsg(const uint32_t Group, const Message::Msg *Msg);

    /// <summary>
    /// 发送讨论组消息(Auth 7)
    /// </summary>
    /// <param name="Disscuss"></param>
    /// <param name="Msg"></param>
    /// <returns></returns>
    bool SendDiscussMsg(const uint32_t Disscuss, const Message::Msg *Msg);

    /// <summary>
    /// 撤回群聊消息(Auth 8)
    /// </summary>
    /// <param name="Group"></param>
    /// <param name="Msg"></param>
    /// <returns></returns>
    bool DrawGroupMsg(const uint32_t Group, const uint32_t MsgID);

    /// <summary>
    /// 撤回私聊消息(Auth 8)
    /// </summary>
    /// <param name="QQ"></param>
    /// <param name="Msg"></param>
    /// <returns></returns>
    bool DrawPrivateMsg(const uint32_t QQ, const uint32_t MsgID);

    /// <summary>
    /// 置群禁言(Auth 9)
    /// </summary>
    /// <param name="Group"></param>
    /// <param name="QQ"></param>
    /// <param name="Time"></param>
    /// <returns></returns>
    bool SetGroupBan(const uint32_t Group, const uint32_t QQ, const uint32_t Time);

    /// <summary>
    /// 移除群员(Auth 10)
    /// </summary>
    /// <param name="Group"></param>
    /// <param name="QQ"></param>
    /// <param name="Forever"></param>
    /// <returns></returns>
    bool SetGroupKick(const uint32_t Group, const uint32_t QQ, const bool Forever);

    /// <summary>
    /// 置群管理员(Auth 11)
    /// </summary>
    /// <param name="Group"></param>
    /// <param name="QQ"></param>
    /// <param name="Set"></param>
    /// <returns></returns>
    bool SetGroupAdmin(const uint32_t Group, const uint32_t QQ, const bool Set);

    /// <summary>
    /// 置群成员头衔(Auth 12)
    /// </summary>
    /// <param name="Group"></param>
    /// <param name="QQ"></param>
    /// <param name="Title"></param>
    /// <returns></returns>
    bool SetGroupMemberTitle(const uint32_t Group, const uint32_t QQ, const char *Title);

    /// <summary>
    /// 置群成员名片(Auth 13)
    /// </summary>
    /// <param name="Group"></param>
    /// <param name="QQ"></param>
    /// <param name="Card"></param>
    /// <returns></returns>
    bool SetGroupMemberCard(const uint32_t Group, const uint32_t QQ, const char *Card);

    /// <summary>
    /// 取群成员信息(Auth 14)
    /// </summary>
    /// <param name="Group"></param>
    /// <param name="QQ"></param>
    /// <returns></returns>
    void GetGroupMemberInfo(const uint32_t Group, const uint32_t QQ);

    /// <summary>
    /// 取陌生人信息(Auth 15)
    /// </summary>
    /// <param name="QQ"></param>
    /// <returns></returns>
    void GetStrangerInfo(const uint32_t QQ);

    /// <summary>
    /// 取群信息(Auth 16)
    /// </summary>
    /// <param name="Group"></param>
    /// <returns></returns>
    void GetGroupInfo(const uint32_t Group);

    /// <summary>
    /// 取好友列表(Auth 17)
    /// </summary>
    /// <returns>记得销毁</returns>
    std::vector<Information::FriendInfo> *GetFriendList();

    /// <summary>
    /// 取群列表(Auth 18)
    /// </summary>
    /// <returns>记得销毁</returns>
    std::vector<Information::GroupInfo> *GetGroupList();

    /// <summary>
    /// 取群成员列表(Auth 19)
    /// </summary>
    /// <param name="group_code"></param>
    /// <returns>记得销毁</returns>
    std::vector<Information::GroupMemberInfo> *GetGroupMemberList(const uint32_t group_code);

    /// <summary>
    /// 取群管理员列表(Auth 20)
    /// </summary>
    /// <param name="group_code"></param>
    /// <returns>记得销毁</returns>
    std::vector<uint32_t> *GetGroupAdminList(const uint32_t group_code);

    /// <summary>
    /// 取群管理员列表(Auth 20)
    /// </summary>
    /// <param name="group_code"></param>
    /// <returns></returns>
    void AddLog(const Log::LogType LogType, const Log::MsgType MsgType, const char8_t *Type, const char8_t *Msg);
};