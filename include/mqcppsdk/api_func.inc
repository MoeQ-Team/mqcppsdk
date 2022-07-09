// Plugin Information
FUNC(bool, getDataPath, const char8_t *)

// QQ Information
FUNC(uint32_t, getUin)
FUNC(char *, getCookies, const char *)

FUNC(LPBYTE, getFriendList)
FUNC(LPBYTE, getGroupList)
FUNC(LPBYTE, getGroupMemberList, const uint32_t)
FUNC(LPBYTE, getGroupAdminList, const uint32_t)

FUNC(void, getGroupMemberInfo, const uint32_t, const uint32_t)
FUNC(void, getStrangerInfo, const uint32_t)
FUNC(void, getGroupInfo, const uint32_t)
// Friend Action
FUNC(bool, sendLike, const uint32_t, const int)
// Action
FUNC(bool, setGroupBan, const uint32_t, const uint32_t, const uint32_t)
FUNC(bool, setGroupKick, const uint32_t, const uint32_t, const bool)
FUNC(bool, setGroupAdmin, const uint32_t, const uint32_t, const bool)
FUNC(bool, setGroupMemberTitle, const uint32_t, const uint32_t, const char *)
FUNC(bool, setGroupMemberCard, const uint32_t, const uint32_t, const char *)
// Chat Action
FUNC(bool, setGroupLeave, const uint32_t)

FUNC(bool, sendPrivateMsg, const uint32_t, const Message::Msg *)
FUNC(bool, sendGroupMsg, const uint32_t, const Message::Msg *)

FUNC(bool, drawPrivateMsg, const uint32_t, const uint64_t)
FUNC(bool, drawGroupMsg, const uint32_t, const uint64_t)
// Other
FUNC(void, addLog, const Log::LogType, const char8_t *, const char8_t *)