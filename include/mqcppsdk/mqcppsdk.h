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
// Get QQ Information
FUNC(LPBYTE, getFriendList, uint64_t auth_code)
FUNC(LPBYTE, getGroupList, uint64_t auth_code)
FUNC(LPBYTE, getGroupMemberList, uint64_t auth_code, int32_t group_id)
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

	void SetAuthCode(uint64_t _AuthCode);

	/// <summary>
	/// 取好友列表(Auth 262144)
	/// </summary>
	/// <returns>记得delete</returns>
	std::vector<MoeQ::FriendInfo>* GetFriendList();

	/// <summary>
	/// 取群列表(Auth 524288)
	/// </summary>
	/// <returns>记得delete</returns>
	std::vector<MoeQ::GroupInfo>* GetGroupList();

	void AddLog(const Log::LogType LogType, const Log::MsgType MsgType, const wchar_t* Type, const wchar_t* Msg);
};

