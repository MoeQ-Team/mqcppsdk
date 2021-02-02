#pragma once
#include "Pack.hpp"

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

namespace Message
{
	enum class MsgType
	{
		text = 1,
		classcal_face = 2,
		expression = 6,
		picture = 8,
		xml = 12,
		reply = 45,
		json = 51,
		red_packet = 56,
	};

	struct Msg
	{
		MsgType MsgType;
		Msg* NextPoint = nullptr;
		void* Message;
	};

	struct text
	{
		char* text;
		uint AtQQ; //if text == nullptr,this is a at,0=AtAll
	};
	struct classcal_face
	{
		uint id = NULL;
	};
	struct expression
	{
		uint id = NULL;
		byte* MD5 = nullptr;
	};
	struct picture
	{
		uint Width = NULL;
		uint Height = NULL;
		uint Length = NULL;
		byte* MD5 = nullptr;
		char* URL = nullptr;
	};
	struct xml
	{
		char* text = nullptr;
		char* description = nullptr;
	};
	struct json
	{
		char* text = nullptr;
		char* description = nullptr;
	};
	struct reply
	{
		uint MsgId;
		uint QQ;
		uint Time;
		Message::Msg* Msg = nullptr;
	};
	//void DestoryMsg(Message::Msg* Msg);
};

namespace Target
{
	enum class TargetType
	{
		_private = 0,
		group = 1,
		discuss = 2,
	};

	struct Target
	{
		TargetType TargetType;
		void* Sender;
	};

	struct _private
	{
		uint FromQQ;
		// 0 FromFriend 1 From Online State 2 From Group 3 From Discuss
		// 0 来自好友 1 来自在线状态 2 来自群 3来自讨论组
		uint FromType;
	};
	struct group
	{
		uint FromGroup;
		uint FromQQ;
	};
	struct discuss
	{
		uint FromDiscuss;
		uint FromQQ;
	};
}

namespace Event
{
	enum class ReturnType
	{
		ignore, //Ignore 忽略
		block, //Block 阻塞
	};

	namespace LifeCycleEvent
	{
		enum class LifeCycleEventType {
			StartUp,
			ShutDown,
			PluginEnabled,
			PluginDisabled
		};
	}

	namespace NoticeEvent
	{
		enum class NoticeEventType {
			group_fileupload, //Group file upload 群文件上传
			group_adminchange, //Group administrator changes 群管理员变动
			group_memberchange, //The change in the number of group members 群成员数量变动
			group_mute, //Group ban 群禁言
			friend_added, //Friend added 好友已添加
		};


		struct NoticeEvent
		{
			Event::NoticeEvent::NoticeEventType NoticeEventType;
			void* Information;
		};

		struct FileInfo
		{
			char* Name;
			char* ID;
			unsigned long long size;
		};

		struct group_fileupload
		{
			uint FromGroup;
			uint FromQQ;
			FileInfo File;
		};
		struct group_adminchange
		{
			uint FromGroup;
			uint FromQQ;
			uint Type; // 0 Set up administrator 被设置管理员 1 Cancelled administrator 被取消管理员
		};
		struct group_memberchange
		{
			uint FromGroup;
			uint FromQQ;
			uint OperateQQ;
			uint Type; // 0 Increase 增加 1 Decrease(Don't include kicked) 减少(不包括被踢) 2 Kicked 被踢
		};
		struct group_mute
		{
			uint FromGroup;
			uint FromQQ;
			uint OperateQQ;
			uint Type; // 0 Ban 被禁言 1 Free 被解禁 
		};
		struct friend_added
		{
			uint FromQQ;
		};
	}

	namespace RequestEvent
	{
		enum class RequestEventType {
			add_friend,
			add_group
		};

		enum class ReturnType
		{
			agree, //Agree 同意
			disagree, //Disagree 不同意
			ignore, //Ignore 忽略
		};

		struct RequestEvent
		{
			Event::RequestEvent::RequestEventType RequestEventType;
			void* Information;
		};

		struct add_friend
		{
			uint FromQQ;
			char* msg;
		};
		struct add_group
		{
			uint FromGroup;
			uint FromQQ;
			char* msg;
			uint Type; // 0 Others apply to join the group 他人申请入群 1 Myself was invited to join the group 自己受邀入群
		};
	}
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


	void SetAuthCode(uint64_t _AuthCode)
	{
		AuthCode = _AuthCode;
	}

	/// <summary>
	/// 取Cookie(skey & Host对应的p_skey)(Auth 1)
	/// </summary>
	/// <param name="Host">p_skey的目标域名</param>
	/// <returns>记得销毁</returns>
	char* GetCookies(const char* Host)
	{
		return getCookies(AuthCode, Host);
	}

	/// <summary>
	/// 点赞(Auth 2)
	/// </summary>
	/// <param name="QQ"></param>
	/// <param name="Times"></param>
	/// <returns></returns>
	bool SendLike(const uint QQ, const int Times)
	{
		return sendLike(AuthCode, QQ, Times);
	}

	/// <summary>
	/// 退出群(Auth 3)
	/// </summary>
	/// <param name="Group"></param>
	/// <returns></returns>
	bool LeaveGroup(const uint Group)
	{
		return setGroupLeave(AuthCode, Group);
	}

	/// <summary>
	/// 退出讨论组(Auth 4)
	/// </summary>
	/// <param name="Disscuss"></param>
	/// <returns></returns>
	bool LeaveDiscuss(const uint Disscuss)
	{
		return setDiscussLeave(AuthCode, Disscuss);
	}

	/// <summary>
	/// 发送私聊消息(Auth 5)
	/// </summary>
	/// <param name="QQ"></param>
	/// <param name="Msg"></param>
	/// <returns></returns>
	bool SendPrivateMsg(const uint QQ, const Message::Msg* Msg)
	{
		return sendPrivateMsg(AuthCode, QQ, Msg);
	}

	/// <summary>
	/// 发送群消息(Auth 6)
	/// </summary>
	/// <param name="Group"></param>
	/// <param name="Msg"></param>
	/// <returns></returns>
	bool SendGroupMsg(const uint Group, const Message::Msg* Msg)
	{
		return sendGroupMsg(AuthCode, Group, Msg);
	}

	/// <summary>
	/// 发送讨论组消息(Auth 7)
	/// </summary>
	/// <param name="Disscuss"></param>
	/// <param name="Msg"></param>
	/// <returns></returns>
	bool SendDiscussMsg(const uint Disscuss, const Message::Msg* Msg)
	{
		return sendDisscussMsg(AuthCode, Disscuss, Msg);
	}

	/// <summary>
	/// 撤回群聊消息(Auth 8)
	/// </summary>
	/// <param name="Group"></param>
	/// <param name="Msg"></param>
	/// <returns></returns>
	bool DrawGroupMsg(const uint Group, const uint MsgID)
	{
		return drawGroupMsg(AuthCode, Group, MsgID);
	}

	/// <summary>
	/// 撤回私聊消息(Auth 8)
	/// </summary>
	/// <param name="QQ"></param>
	/// <param name="Msg"></param>
	/// <returns></returns>
	bool DrawPrivateMsg(const uint QQ, const uint MsgID)
	{
		return drawPrivateMsg(AuthCode, QQ, MsgID);
	}

	/// <summary>
	/// 置群禁言(Auth 9)
	/// </summary>
	/// <param name="Group"></param>
	/// <param name="QQ"></param>
	/// <param name="Time"></param>
	/// <returns></returns>
	bool SetGroupBan(const uint Group, const uint QQ, const uint Time)
	{
		return setGroupBan(AuthCode, Group, QQ, Time);
	}

	/// <summary>
	/// 移除群员(Auth 10)
	/// </summary>
	/// <param name="Group"></param>
	/// <param name="QQ"></param>
	/// <param name="Forever"></param>
	/// <returns></returns>
	bool SetGroupKick(const uint Group, const uint QQ, const bool Forever)
	{
		return setGroupKick(AuthCode, Group, QQ, Forever);
	}

	/// <summary>
	/// 置群管理员(Auth 11)
	/// </summary>
	/// <param name="Group"></param>
	/// <param name="QQ"></param>
	/// <param name="Set"></param>
	/// <returns></returns>
	bool SetGroupAdmin(const uint Group, const uint QQ, const bool Set)
	{
		return setGroupAdmin(AuthCode, Group, QQ, Set);
	}

	/// <summary>
	/// 置群成员头衔(Auth 12)
	/// </summary>
	/// <param name="Group"></param>
	/// <param name="QQ"></param>
	/// <param name="Title"></param>
	/// <returns></returns>
	bool SetGroupMemberTitle(const uint Group, const uint QQ, const char* Title)
	{
		return setGroupMemberTitle(AuthCode, Group, QQ, Title);
	}

	/// <summary>
	/// 置群成员名片(Auth 13)
	/// </summary>
	/// <param name="Group"></param>
	/// <param name="QQ"></param>
	/// <param name="Card"></param>
	/// <returns></returns>
	bool SetGroupMemberCard(const uint Group, const uint QQ, const char* Card)
	{
		return setGroupMemberCard(AuthCode, Group, QQ, Card);
	}

	/// <summary>
	/// 取群成员信息(Auth 14)
	/// </summary>
	/// <param name="Group"></param>
	/// <param name="QQ"></param>
	/// <returns></returns>
	void GetGroupMemberInfo(const uint Group, const uint QQ)
	{
		return getGroupMemberInfo(AuthCode, Group, QQ);
	}

	/// <summary>
	/// 取陌生人信息(Auth 15)
	/// </summary>
	/// <param name="QQ"></param>
	/// <returns></returns>
	void GetStrangerInfo(const uint QQ)
	{
		return getStrangerInfo(AuthCode, QQ);
	}

	/// <summary>
	/// 取群信息(Auth 16)
	/// </summary>
	/// <param name="Group"></param>
	/// <returns></returns>
	void GetGroupInfo(const uint Group)
	{
		return getGroupInfo(AuthCode, Group);
	}

	/// <summary>
	/// 取好友列表(Auth 17)
	/// </summary>
	/// <returns>记得销毁</returns>
	std::vector<FriendInfo>* GetFriendList()
	{
		LPBYTE bin = getFriendList(AuthCode);
		UnPack UnPack(bin);
		uint length = UnPack.GetInt();
		std::vector<FriendInfo>* FriendList = new std::vector<FriendInfo>;
		FriendList->resize(length);
		for (size_t i = 0; i < length; i++)
		{
			(*FriendList)[i].QQ = UnPack.GetInt();
#if _WIN64
			(*FriendList)[i].Nick = (char*)UnPack.GetLong();
#else
			(*FriendList)[i].Nick = (char*)UnPack.GetInt();
#endif
			(*FriendList)[i].status = UnPack.GetInt();
#if _WIN64
			(*FriendList)[i].Remark = (char*)UnPack.GetLong();
#else
			(*FriendList)[i].Remark = (char*)UnPack.GetInt();
#endif
		}
		delete[] bin;
		return FriendList;
	}

	/// <summary>
	/// 取群列表(Auth 18)
	/// </summary>
	/// <returns>记得销毁</returns>
	std::vector<GroupInfo>* GetGroupList()
	{
		LPBYTE bin = getGroupList(AuthCode);
		UnPack UnPack(bin);
		uint length = UnPack.GetInt();
		std::vector<GroupInfo>* GroupList = new std::vector<GroupInfo>;
		GroupList->resize(length);
		for (size_t i = 0; i < length; i++)
		{
			(*GroupList)[i].GroupCode = UnPack.GetInt();
#if _WIN64
			(*GroupList)[i].GroupName = (char*)UnPack.GetLong();
#else
			(*GroupList)[i].GroupName = (char*)UnPack.GetInt();
#endif
			(*GroupList)[i].MasterQQ = UnPack.GetInt();
			(*GroupList)[i].MemberCount = UnPack.GetShort();
			(*GroupList)[i].SelfIdentity = UnPack.GetByte();
		}
		delete[] bin;
		return GroupList;
	}

	/// <summary>
	/// 取群成员列表(Auth 19)
	/// </summary>
	/// <param name="group_code"></param>
	/// <returns>记得销毁</returns>
	std::vector<GroupMemberInfo>* GetGroupMemberList(const uint group_code)
	{
		LPBYTE bin = getGroupMemberList(AuthCode, group_code);
		UnPack UnPack(bin);
		uint length = UnPack.GetInt();
		std::vector<GroupMemberInfo>* GroupMemberList = new std::vector<GroupMemberInfo>;
		GroupMemberList->resize(length);
		for (size_t i = 0; i < length; i++)
		{

		}
		delete[] bin;
		return GroupMemberList;
	}

	/// <summary>
	/// 取群管理员列表(Auth 20)
	/// </summary>
	/// <param name="group_code"></param>
	/// <returns>记得销毁</returns>
	std::vector<uint>* GetGroupAdminList(const uint group_code)
	{
		LPBYTE bin = getGroupAdminList(AuthCode, group_code);
		UnPack UnPack(bin);
		uint length = UnPack.GetInt();
		std::vector<uint>* GroupAdminList = new std::vector<uint>;
		GroupAdminList->resize(length);
		for (size_t i = 0; i < length; i++)
		{
			(*GroupAdminList)[i] = UnPack.GetInt();
		}
		delete[] bin;
		return GroupAdminList;
	}


	void AddLog(const Log::LogType LogType, const Log::MsgType MsgType, const wchar_t* Type, const wchar_t* Msg)
	{
		addLog(AuthCode, LogType, MsgType, Type, Msg);
	}

};