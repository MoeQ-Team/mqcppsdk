#pragma once
#include "Pack.h"

// Follow is MoeQ dll call defined
#define FUNC(ReturnType, FuncName, ...) static ReturnType(__stdcall *##FuncName)(__VA_ARGS__);
// Get QQ Information
FUNC(LPBYTE, getFriendList, int64_t auth_code)
FUNC(LPBYTE, getGroupList, int64_t auth_code)
FUNC(LPBYTE, getGroupInfo, int64_t auth_code, int32_t group_id)
FUNC(LPBYTE, getGroupMemberList, int64_t auth_code, int32_t group_id)
FUNC(LPBYTE, getGroupMemberInfo, int64_t auth_code, int32_t group_id, int32_t qq)

class MoeQ
{
private:
	int64_t AuthCode;
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

	void SetAuthCode(int64_t _AuthCode);
	/// <summary>
	/// 取好友列表(Auth 130)
	/// </summary>
	/// <returns>记得delete</returns>
	std::vector<MoeQ::FriendInfo>* GetFriendList();
	/// <summary>
	/// 取群列表(Auth 131)
	/// </summary>
	/// <returns>记得delete</returns>
	std::vector<MoeQ::GroupInfo>* GetGroupList();
};

