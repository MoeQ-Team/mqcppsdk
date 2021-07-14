#include "../../include/mqcppsdk/mqcppsdk.h"

// Follow is MoeQ dll call defined

#if defined(_WIN_PLATFORM_)
#define FUNC(ReturnType, FuncName, ...) extern "C" __declspec(dllimport) ReturnType __stdcall FuncName(__VA_ARGS__);
#endif

#if defined(_LINUX_PLATFORM_)
#define FUNC(ReturnType, FuncName, ...) extern "C" ReturnType FuncName(__VA_ARGS__);
#endif

// QQ Information
FUNC(char *, getCookies, const uint64_t AuthCode, const char *Host)

FUNC(LPBYTE, getFriendList, const uint64_t AuthCode)
FUNC(LPBYTE, getGroupList, const uint64_t AuthCode)
FUNC(LPBYTE, getGroupMemberList, const uint64_t AuthCode,const uint32_t group_code)
FUNC(LPBYTE, getGroupAdminList, const uint64_t AuthCode,const uint32_t group_code)

FUNC(void, getGroupMemberInfo, const uint64_t AuthCode, const uint32_t Group, const uint32_t QQ)
FUNC(void, getStrangerInfo, const uint64_t AuthCode, const uint32_t QQ)
FUNC(void, getGroupInfo, const uint64_t AuthCode, const uint32_t Group)
// Friend Action
FUNC(bool, sendLike, const uint64_t AuthCode, const uint32_t QQ, const int Times)
// Group Action
FUNC(bool, setGroupBan, const uint64_t AuthCode, const uint32_t Group, const uint32_t QQ, const uint32_t Time)
FUNC(bool, setGroupKick, const uint64_t AuthCode, const uint32_t Group, const uint32_t QQ, const bool Forever)
FUNC(bool, setGroupAdmin, const uint64_t AuthCode, const uint32_t Group, const uint32_t QQ, const bool Set)
FUNC(bool, setGroupMemberTitle, const uint64_t AuthCode, const uint32_t Group, const uint32_t QQ, const char *Title)
FUNC(bool, setGroupMemberCard, const uint64_t AuthCode, const uint32_t Group, const uint32_t QQ, const char *Card)
// Chat Action
FUNC(bool, setGroupLeave, const uint64_t AuthCode, const uint32_t group_code)
FUNC(bool, setDiscussLeave, const uint64_t AuthCode, const uint32_t group_code)

FUNC(bool, sendPrivateMsg, const uint64_t AuthCode, const uint32_t QQ, const Message::Msg *Msg)
FUNC(bool, sendGroupMsg, const uint64_t AuthCode, const uint32_t Group, const Message::Msg *Msg)
FUNC(bool, sendDisscussMsg, const uint64_t AuthCode, const uint32_t Disscuss, const Message::Msg *Msg)

FUNC(bool, drawPrivateMsg, const uint64_t AuthCode, const uint32_t QQ, const uint64_t MsgID)
FUNC(bool, drawGroupMsg, const uint64_t AuthCode, const uint32_t Group, const uint64_t MsgID)
// Other
FUNC(void, addLog, const uint64_t AuthCode, const Log::LogType LogType, const Log::MsgType MsgType, const char8_t *Type, const char8_t *Msg)

#undef FUNC

void MoeQ::SetAuthCode(uint64_t _AuthCode)
{
    AuthCode = _AuthCode;
}

char *MoeQ::GetCookies(const char *Host)
{
    return getCookies(AuthCode, Host);
}

bool MoeQ::SendLike(const uint32_t QQ, const int Times)
{
    return sendLike(AuthCode, QQ, Times);
}

bool MoeQ::LeaveGroup(const uint32_t Group)
{
    return setGroupLeave(AuthCode, Group);
}

bool MoeQ::LeaveDiscuss(const uint32_t Disscuss)
{
    return setDiscussLeave(AuthCode, Disscuss);
}

bool MoeQ::SendPrivateMsg(const uint32_t QQ, const Message::Msg *Msg)
{
    return sendPrivateMsg(AuthCode, QQ, Msg);
}

bool MoeQ::SendGroupMsg(const uint32_t Group, const Message::Msg *Msg)
{
    return sendGroupMsg(AuthCode, Group, Msg);
}

bool MoeQ::SendDiscussMsg(const uint32_t Disscuss, const Message::Msg *Msg)
{
    return sendDisscussMsg(AuthCode, Disscuss, Msg);
}

bool MoeQ::DrawGroupMsg(const uint32_t Group, const uint32_t MsgID)
{
    return drawGroupMsg(AuthCode, Group, MsgID);
}

bool MoeQ::DrawPrivateMsg(const uint32_t QQ, const uint32_t MsgID)
{
    return drawPrivateMsg(AuthCode, QQ, MsgID);
}

bool MoeQ::SetGroupBan(const uint32_t Group, const uint32_t QQ, const uint32_t Time)
{
    return setGroupBan(AuthCode, Group, QQ, Time);
}

bool MoeQ::SetGroupKick(const uint32_t Group, const uint32_t QQ, const bool Forever)
{
    return setGroupKick(AuthCode, Group, QQ, Forever);
}

bool MoeQ::SetGroupAdmin(const uint32_t Group, const uint32_t QQ, const bool Set)
{
    return setGroupAdmin(AuthCode, Group, QQ, Set);
}

bool MoeQ::SetGroupMemberTitle(const uint32_t Group, const uint32_t QQ, const char *Title)
{
    return setGroupMemberTitle(AuthCode, Group, QQ, Title);
}

bool MoeQ::SetGroupMemberCard(const uint32_t Group, const uint32_t QQ, const char *Card)
{
    return setGroupMemberCard(AuthCode, Group, QQ, Card);
}

void MoeQ::GetGroupMemberInfo(const uint32_t Group, const uint32_t QQ)
{
    return getGroupMemberInfo(AuthCode, Group, QQ);
}

void MoeQ::GetStrangerInfo(const uint32_t QQ)
{
    return getStrangerInfo(AuthCode, QQ);
}

void MoeQ::GetGroupInfo(const uint32_t Group)
{
    return getGroupInfo(AuthCode, Group);
}

std::vector<Information::FriendInfo> *MoeQ::GetFriendList()
{
    LPBYTE bin = getFriendList(AuthCode);
    UnPack UnPack(bin);
    uint32_t length = UnPack.GetInt();
    std::vector<Information::FriendInfo> *FriendList = new std::vector<Information::FriendInfo>;
    FriendList->resize(length);
    for (size_t i = 0; i < length; i++)
    {
        (*FriendList)[i].QQ = UnPack.GetInt();
        (*FriendList)[i].Nick = (char *)UnPack.GetLong();
        (*FriendList)[i].Nick = (char *)UnPack.GetInt();
        (*FriendList)[i].status = UnPack.GetInt();
        (*FriendList)[i].Remark = (char *)UnPack.GetLong();
        (*FriendList)[i].Remark = (char *)UnPack.GetInt();
    }
    delete[] bin;
    return FriendList;
}

std::vector<Information::GroupInfo> *MoeQ::GetGroupList()
{
    LPBYTE bin = getGroupList(AuthCode);
    UnPack UnPack(bin);
    uint32_t length = UnPack.GetInt();
    std::vector<Information::GroupInfo> *GroupList = new std::vector<Information::GroupInfo>;
    GroupList->resize(length);
    for (size_t i = 0; i < length; i++)
    {
        (*GroupList)[i].GroupCode = UnPack.GetInt();
        (*GroupList)[i].GroupName = (char *)UnPack.GetLong();
        (*GroupList)[i].GroupName = (char *)UnPack.GetInt();
        (*GroupList)[i].MasterQQ = UnPack.GetInt();
        (*GroupList)[i].MemberCount = UnPack.GetShort();
        (*GroupList)[i].SelfIdentity = UnPack.GetByte();
    }
    delete[] bin;
    return GroupList;
}

std::vector<Information::GroupMemberInfo> *MoeQ::GetGroupMemberList(const uint32_t group_code)
{
    LPBYTE bin = getGroupMemberList(AuthCode, group_code);
    UnPack UnPack(bin);
    uint32_t length = UnPack.GetInt();
    std::vector<Information::GroupMemberInfo> *GroupMemberList = new std::vector<Information::GroupMemberInfo>;
    GroupMemberList->resize(length);
    for (size_t i = 0; i < length; i++)
    {
    }
    delete[] bin;
    return GroupMemberList;
}

std::vector<uint32_t> *MoeQ::GetGroupAdminList(const uint32_t group_code)
{
    LPBYTE bin = getGroupAdminList(AuthCode, group_code);
    UnPack UnPack(bin);
    uint32_t length = UnPack.GetInt();
    std::vector<uint32_t> *GroupAdminList = new std::vector<uint32_t>;
    GroupAdminList->resize(length);
    for (size_t i = 0; i < length; i++)
    {
        (*GroupAdminList)[i] = UnPack.GetInt();
    }
    delete[] bin;
    return GroupAdminList;
}

void MoeQ::AddLog(const Log::LogType LogType, const Log::MsgType MsgType, const char8_t *Type, const char8_t *Msg)
{
    addLog(AuthCode, LogType, MsgType, Type, Msg);
}