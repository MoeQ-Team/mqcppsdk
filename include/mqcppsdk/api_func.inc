// QQ Information
FUNC(uint32_t, getUin, const uint64_t)
FUNC(char *, getCookies, const uint64_t, const char *)

FUNC(LPBYTE, getFriendList, const uint64_t)
FUNC(LPBYTE, getGroupList, const uint64_t)
FUNC(LPBYTE, getGroupMemberList, const uint64_t,const uint32_t)
FUNC(LPBYTE, getGroupAdminList, const uint64_t,const uint32_t)

FUNC(void, getGroupMemberInfo, const uint64_t, const uint32_t, const uint32_t)
FUNC(void, getStrangerInfo, const uint64_t, const uint32_t)
FUNC(void, getGroupInfo, const uint64_t, const uint32_t)
// Friend Action
FUNC(bool, sendLike, const uint64_t, const uint32_t, const int)
// Action
FUNC(bool, setGroupBan, const uint64_t, const uint32_t, const uint32_t, const uint32_t)
FUNC(bool, setGroupKick, const uint64_t, const uint32_t, const uint32_t, const bool)
FUNC(bool, setGroupAdmin, const uint64_t, const uint32_t, const uint32_t, const bool)
FUNC(bool, setGroupMemberTitle, const uint64_t, const uint32_t, const uint32_t, const char *)
FUNC(bool, setGroupMemberCard, const uint64_t, const uint32_t, const uint32_t, const char *)
// Chat Action
FUNC(bool, setGroupLeave, const uint64_t, const uint32_t)
FUNC(bool, setDiscussLeave, const uint64_t, const uint32_t)

FUNC(bool, sendPrivateMsg, const uint64_t, const uint32_t, const Message::Msg *)
FUNC(bool, sendGroupMsg, const uint64_t, const uint32_t, const Message::Msg *)
FUNC(bool, sendDisscussMsg, const uint64_t, const uint32_t, const Message::Msg *)

FUNC(bool, drawPrivateMsg, const uint64_t, const uint32_t, const uint64_t)
FUNC(bool, drawGroupMsg, const uint64_t, const uint32_t, const uint64_t)
// Other
FUNC(void, addLog, const uint64_t, const Log::LogType, const Log::MsgType, const char8_t *, const char8_t *)