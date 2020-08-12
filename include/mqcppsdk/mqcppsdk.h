#pragma once
#include "Pack.h"
#include "Event.hpp"
#define MOEQ_SDK_VERSION 1

namespace Log {
	enum class LogType
	{
		__DEBUG = 0,
		INFORMATION = 1,
		NOTICE = 2,
		WARNING = 3,
		_ERROR = 4
	};

	enum class MsgType
	{
		SERVER = 0,
		PROGRAM = 1,
		PRIVATE = 2,
		_GROUP = 3,
		OTHER = 4
	};
}

// Follow is MoeQ dll call defined
#define FUNC(ReturnType, FuncName, ...) extern "C" __declspec(dllexport) ReturnType __stdcall FuncName(__VA_ARGS__);
// QQ Information
FUNC(char*, getCookies, const uint64_t auth_code, const char* Host)

FUNC(LPBYTE, getFriendList, const uint64_t auth_code)
FUNC(LPBYTE, getGroupList, const uint64_t auth_code)
FUNC(LPBYTE, getGroupMemberList, const uint64_t auth_code, uint group_code)
FUNC(LPBYTE, getGroupAdminList, const uint64_t auth_code, uint group_code)
// Friend Action
FUNC(bool, sendLike, const uint64_t auth_code, const uint QQ, const int Times)
// Group Action
FUNC(bool, setGroupBan, const uint64_t auth_code, const uint Group, const uint QQ, const uint Time)
FUNC(bool, setGroupKick, const uint64_t auth_code, const uint Group, const uint QQ, const bool Forever)
FUNC(bool, setGroupAdmin, const uint64_t auth_code, const uint Group, const uint QQ, const bool Set)
FUNC(bool, setGroupMemberTitle, const uint64_t auth_code, const uint Group, const uint QQ, const char* Title)
FUNC(bool, setGroupMemberCard, const uint64_t auth_code, const uint Group, const uint QQ, const char* Card)
// Chat Action
FUNC(bool, sendPrivateMsg, const uint64_t AuthCode, const uint QQ, const Message::Msg* Msg)
FUNC(bool, sendGroupMsg, const uint64_t AuthCode, const uint Group, const Message::Msg* Msg)
FUNC(bool, drawPrivateMsg, const uint64_t AuthCode, const uint QQ, const uint MsgID)
FUNC(bool, drawGroupMsg, const uint64_t AuthCode, const uint Group, const uint MsgID)
// Other
FUNC(void, addLog, const uint64_t auth_code, const Log::LogType, const Log::MsgType, const wchar_t* Type, const wchar_t* Msg)

//#pragma comment(lib, "MoeQ.lib")

class MoeQ
{
private:
	uint64_t AuthCode;
public:
	struct FriendInfo
	{
		uint QQ;
		char* Nick;
		int32_t status;
		char* Remark;
	};
	struct GroupInfo
	{
		uint GroupCode;
		char* GroupName;
		uint MasterQQ;
		int16_t MemberCount;
		byte SelfIdentity;
	};
	struct GroupMemberInfo
	{
		uint QQ;
		char* Nick;
	};

	void SetAuthCode(uint64_t _AuthCode);

	/// <summary>
	/// 取Cookie(skey,p_skey)(Auth 1)
	/// </summary>
	/// <param name="Host">p_skey的目标域名</param>
	/// <returns>记得销毁</returns>
	char* GetCookies(const char* Host);

	/// <summary>
	/// 点赞(Auth 2)
	/// </summary>
	/// <param name="QQ"></param>
	/// <param name="Times"></param>
	/// <returns></returns>
	bool SendLike(const uint QQ, const int Times);

	/// <summary>
	/// 发送群消息(Auth 7)
	/// </summary>
	/// <param name="Group"></param>
	/// <param name="Msg"></param>
	/// <returns></returns>
	bool SendGroupMsg(const uint Group, const Message::Msg* Msg);

	/// <summary>
	/// 取好友列表(Auth 17)
	/// </summary>
	/// <returns>记得销毁</returns>
	std::vector<MoeQ::FriendInfo>* GetFriendList();

	/// <summary>
	/// 取群列表(Auth 28)
	/// </summary>
	/// <returns>记得销毁</returns>
	std::vector<MoeQ::GroupInfo>* GetGroupList();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="group_code"></param>
	/// <returns></returns>
	std::vector<MoeQ::GroupMemberInfo>* GetGroupMemberList(const uint group_code);

	std::vector<uint>* GetGroupAdminList(const uint group_code);

	void AddLog(const Log::LogType LogType, const Log::MsgType MsgType, const wchar_t* Type, const wchar_t* Msg);
};