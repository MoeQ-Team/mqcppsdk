#include "../../include/mqcppsdk/mqcppsdk.h"

// Following is functions of MoeQ declared

#if defined(_WIN_PLATFORM_)
#define FUNC(ReturnType, FuncName, ...)                                         \
    typedef ReturnType(__stdcall *__##FuncName)(const uint64_t, ##__VA_ARGS__); \
    __##FuncName FuncName;
#endif

#if defined(_LINUX_PLATFORM_)
#define FUNC(ReturnType, FuncName, ...)                                \
    typedef ReturnType (*__##FuncName)(const uint64_t, ##__VA_ARGS__); \
    __##FuncName FuncName;
#endif

#include "../../include/mqcppsdk/api_func.inc"

#undef FUNC

void MoeQ::Initialize()
{

#if defined(_WIN_PLATFORM_)
    HMODULE Handle = LoadLibrary(L"MoeQ.exe");
    if (Handle == NULL)
        exit(-1);
#define FUNC(ReturnType, FuncName, ...) FuncName = (__##FuncName)GetProcAddress(Handle, #FuncName);

#endif
#if defined(_LINUX_PLATFORM_)
    void *Handle = dlopen("MoeQ", RTLD_NOW);
    if (Handle == NULL)
        exit(-1);
#define FUNC(ReturnType, FuncName, ...) FuncName = (__##FuncName)dlsym(Handle, #FuncName);
#endif

#include "../../include/mqcppsdk/api_func.inc"

#undef FUNC
}

void MoeQ::SetAuthCode(uint64_t _AuthCode)
{
    AuthCode = _AuthCode;
}

bool MoeQ::GetDataPath(char8_t *pPath)
{
    return getDataPath(AuthCode, pPath);
};

uint32_t MoeQ::GetUin()
{
    return getUin(AuthCode);
}

char8_t *MoeQ::GetCookies(const char8_t *Host)
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

bool MoeQ::SendPrivateMsg(const uint32_t QQ, const Message::Msg *Msg)
{
    return sendPrivateMsg(AuthCode, QQ, Msg);
}

bool MoeQ::SendGroupMsg(const uint32_t Group, const Message::Msg *Msg)
{
    return sendGroupMsg(AuthCode, Group, Msg);
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

bool MoeQ::SetGroupMemberTitle(const uint32_t Group, const uint32_t QQ, const char8_t *Title)
{
    return setGroupMemberTitle(AuthCode, Group, QQ, Title);
}

bool MoeQ::SetGroupMemberCard(const uint32_t Group, const uint32_t QQ, const char8_t *Card)
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
        (*FriendList)[i].Nick = (char8_t *)UnPack.GetLong();
        (*FriendList)[i].status = UnPack.GetInt();
        (*FriendList)[i].Remark = (char8_t *)UnPack.GetLong();
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
        (*GroupList)[i].GroupName = (const char8_t *)UnPack.GetStr(UnPack.GetInt());
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

void MoeQ::AddLog(const Log::LogType LogType, const char8_t *Type, const char8_t *Msg)
{
    addLog(AuthCode, LogType, Type, Msg);
}