#pragma once
#include "Pack.h"
#include "Event.hpp"
#define MOEQ_SDK_VERSION 1

// Follow is MoeQ dll call defined
#define FUNC(ReturnType, FuncName, ...) static ReturnType(__stdcall *##FuncName)(__VA_ARGS__);
// Get QQ Information
FUNC(LPBYTE, getFriendList, uint64_t auth_code)
FUNC(LPBYTE, getGroupList, uint64_t auth_code)
FUNC(LPBYTE, getGroupInfo, uint64_t auth_code, int32_t group_id)
FUNC(LPBYTE, getGroupMemberList, uint64_t auth_code, int32_t group_id)
FUNC(LPBYTE, getGroupMemberInfo, uint64_t auth_code, int32_t group_id, int32_t qq)

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
	/// 取好友列表(Auth 140)
	/// </summary>
	/// <returns>记得delete</returns>
	std::vector<MoeQ::FriendInfo>* GetFriendList();

	/// <summary>
	/// 取群列表(Auth 141)
	/// </summary>
	/// <returns>记得delete</returns>
	std::vector<MoeQ::GroupInfo>* GetGroupList();
};

