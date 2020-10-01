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
FUNC(char*, getCookies, const uint64_t AuthCode, const char* Host)

FUNC(LPBYTE, getFriendList, const uint64_t AuthCode)
FUNC(LPBYTE, getGroupList, const uint64_t AuthCode)
FUNC(LPBYTE, getGroupMemberList, const uint64_t AuthCode, uint group_code)
FUNC(LPBYTE, getGroupAdminList, const uint64_t AuthCode, uint group_code)

FUNC(void, getGroupMemberInfo, const uint64_t AuthCode, const uint Group, const uint QQ)
FUNC(void, getStrangerInfo, const uint64_t AuthCode, const uint QQ)
FUNC(void, getGroupInfo, const uint64_t AuthCode, const uint Group)
// Friend Action
FUNC(bool, sendLike, const uint64_t AuthCode, const uint QQ, const int Times)
// Group Action
FUNC(bool, setGroupBan, const uint64_t AuthCode, const uint Group, const uint QQ, const uint Time)
FUNC(bool, setGroupKick, const uint64_t AuthCode, const uint Group, const uint QQ, const bool Forever)
FUNC(bool, setGroupAdmin, const uint64_t AuthCode, const uint Group, const uint QQ, const bool Set)
FUNC(bool, setGroupMemberTitle, const uint64_t AuthCode, const uint Group, const uint QQ, const char* Title)
FUNC(bool, setGroupMemberCard, const uint64_t AuthCode, const uint Group, const uint QQ, const char* Card)
// Chat Action
FUNC(bool, setGroupLeave, const uint64_t AuthCode, const uint group_code)
FUNC(bool, setDiscussLeave, const uint64_t AuthCode, const uint group_code)

FUNC(bool, sendPrivateMsg, const uint64_t AuthCode, const uint QQ, const Message::Msg* Msg)
FUNC(bool, sendGroupMsg, const uint64_t AuthCode, const uint Group, const Message::Msg* Msg)
FUNC(bool, sendDisscussMsg, const uint64_t AuthCode, const uint Disscuss, const Message::Msg* Msg)

FUNC(bool, drawPrivateMsg, const uint64_t AuthCode, const uint QQ, const uint MsgID)
FUNC(bool, drawGroupMsg, const uint64_t AuthCode, const uint Group, const uint MsgID)
// Other
FUNC(void, addLog, const uint64_t AuthCode, const Log::LogType LogType, const Log::MsgType MsgType, const wchar_t* Type, const wchar_t* Msg)

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
	/// ȡCookie(skey & Host��Ӧ��p_skey)(Auth 1)
	/// </summary>
	/// <param name="Host">p_skey��Ŀ������</param>
	/// <returns>�ǵ�����</returns>
	char* GetCookies(const char* Host);

	/// <summary>
	/// ����(Auth 2)
	/// </summary>
	/// <param name="QQ"></param>
	/// <param name="Times"></param>
	/// <returns></returns>
	bool SendLike(const uint QQ, const int Times);

	/// <summary>
	/// �˳�Ⱥ(Auth 3)
	/// </summary>
	/// <param name="Group"></param>
	/// <returns></returns>
	bool LeaveGroup(const uint Group);

	/// <summary>
	/// �˳�������(Auth 4)
	/// </summary>
	/// <param name="Disscuss"></param>
	/// <returns></returns>
	bool LeaveDiscuss(const uint Disscuss);

	/// <summary>
	/// ����˽����Ϣ(Auth 5)
	/// </summary>
	/// <param name="QQ"></param>
	/// <param name="Msg"></param>
	/// <returns></returns>
	bool SendPrivateMsg(const uint QQ, const Message::Msg* Msg);

	/// <summary>
	/// ����Ⱥ��Ϣ(Auth 6)
	/// </summary>
	/// <param name="Group"></param>
	/// <param name="Msg"></param>
	/// <returns></returns>
	bool SendGroupMsg(const uint Group, const Message::Msg* Msg);

	/// <summary>
	/// ������������Ϣ(Auth 7)
	/// </summary>
	/// <param name="Disscuss"></param>
	/// <param name="Msg"></param>
	/// <returns></returns>
	bool SendDiscussMsg(const uint Disscuss, const Message::Msg* Msg);

	/// <summary>
	/// ����Ⱥ����Ϣ(Auth 8)
	/// </summary>
	/// <param name="Group"></param>
	/// <param name="Msg"></param>
	/// <returns></returns>
	bool DrawGroupMsg(const uint Group, const uint MsgID);

	/// <summary>
	/// ����˽����Ϣ(Auth 8)
	/// </summary>
	/// <param name="QQ"></param>
	/// <param name="Msg"></param>
	/// <returns></returns>
	bool DrawPrivateMsg(const uint QQ, const uint MsgID);

	/// <summary>
	/// ��Ⱥ����(Auth 9)
	/// </summary>
	/// <param name="Group"></param>
	/// <param name="QQ"></param>
	/// <param name="Time"></param>
	/// <returns></returns>
	bool SetGroupBan(const uint Group, const uint QQ, const uint Time);

	/// <summary>
	/// �Ƴ�ȺԱ(Auth 10)
	/// </summary>
	/// <param name="Group"></param>
	/// <param name="QQ"></param>
	/// <param name="Forever"></param>
	/// <returns></returns>
	bool SetGroupKick(const uint Group, const uint QQ, const bool Forever);

	/// <summary>
	/// ��Ⱥ����Ա(Auth 11)
	/// </summary>
	/// <param name="Group"></param>
	/// <param name="QQ"></param>
	/// <param name="Set"></param>
	/// <returns></returns>
	bool SetGroupAdmin(const uint Group, const uint QQ, const bool Set);

	/// <summary>
	/// ��Ⱥ��Աͷ��(Auth 12)
	/// </summary>
	/// <param name="Group"></param>
	/// <param name="QQ"></param>
	/// <param name="Title"></param>
	/// <returns></returns>
	bool SetGroupMemberTitle(const uint Group, const uint QQ, const char* Title);
	
	/// <summary>
	/// ��Ⱥ��Ա��Ƭ(Auth 13)
	/// </summary>
	/// <param name="Group"></param>
	/// <param name="QQ"></param>
	/// <param name="Card"></param>
	/// <returns></returns>
	bool SetGroupMemberCard(const uint Group, const uint QQ, const char* Card);

	/// <summary>
	/// ȡȺ��Ա��Ϣ(Auth 14)
	/// </summary>
	/// <param name="Group"></param>
	/// <param name="QQ"></param>
	/// <returns></returns>
	void GetGroupMemberInfo(const uint Group, const uint QQ);

	/// <summary>
	/// ȡİ������Ϣ(Auth 15)
	/// </summary>
	/// <param name="QQ"></param>
	/// <returns></returns>
	void GetStrangerInfo(const uint QQ);

	/// <summary>
	/// ȡȺ��Ϣ(Auth 16)
	/// </summary>
	/// <param name="Group"></param>
	/// <returns></returns>
	void GetGroupInfo(const uint Group);

	/// <summary>
	/// ȡ�����б�(Auth 17)
	/// </summary>
	/// <returns>�ǵ�����</returns>
	std::vector<MoeQ::FriendInfo>* GetFriendList();

	/// <summary>
	/// ȡȺ�б�(Auth 18)
	/// </summary>
	/// <returns>�ǵ�����</returns>
	std::vector<MoeQ::GroupInfo>* GetGroupList();

	/// <summary>
	/// ȡȺ��Ա�б�(Auth 19)
	/// </summary>
	/// <param name="group_code"></param>
	/// <returns>�ǵ�����</returns>
	std::vector<MoeQ::GroupMemberInfo>* GetGroupMemberList(const uint group_code);

	/// <summary>
	/// ȡȺ����Ա�б�(Auth 20)
	/// </summary>
	/// <param name="group_code"></param>
	/// <returns>�ǵ�����</returns>
	std::vector<uint>* GetGroupAdminList(const uint group_code);

	void AddLog(const Log::LogType LogType, const Log::MsgType MsgType, const wchar_t* Type, const wchar_t* Msg);
};