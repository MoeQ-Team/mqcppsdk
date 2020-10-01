#include "mqcppsdk.h"

void MoeQ::SetAuthCode(uint64_t _AuthCode)
{
	AuthCode = _AuthCode;
}


char* MoeQ::GetCookies(const char* Host)
{
	return getCookies(AuthCode, Host);
}

bool MoeQ::SendLike(const uint QQ, const int Times)
{
	return sendLike(AuthCode, QQ, Times);
}

bool MoeQ::LeaveGroup(const uint Group)
{
	return setGroupLeave(AuthCode, Group);
}

bool MoeQ::LeaveDiscuss(const uint Disscuss)
{
	return setDiscussLeave(AuthCode, Disscuss);
}

bool MoeQ::SendPrivateMsg(const uint QQ, const Message::Msg* Msg)
{
	return sendPrivateMsg(AuthCode, QQ, Msg);
}

bool MoeQ::SendGroupMsg(const uint Group, const Message::Msg* Msg)
{
	return sendGroupMsg(AuthCode, Group, Msg);
}

bool MoeQ::SendDiscussMsg(const uint Disscuss, const Message::Msg* Msg)
{
	return sendDisscussMsg(AuthCode, Disscuss, Msg);
}

bool MoeQ::DrawGroupMsg(const uint Group, const uint MsgID)
{
	return drawGroupMsg(AuthCode, Group, MsgID);
}

bool MoeQ::DrawPrivateMsg(const uint QQ, const uint MsgID)
{
	return drawPrivateMsg(AuthCode, QQ, MsgID);
}

bool MoeQ::SetGroupBan(const uint Group, const uint QQ, const uint Time)
{
	return setGroupBan(AuthCode, Group, QQ, Time);
}

bool MoeQ::SetGroupKick(const uint Group, const uint QQ, const bool Forever)
{
	return setGroupKick(AuthCode, Group, QQ, Forever);
}

bool MoeQ::SetGroupAdmin(const uint Group, const uint QQ, const bool Set)
{
	return setGroupAdmin(AuthCode, Group, QQ, Set);
}

bool MoeQ::SetGroupMemberTitle(const uint Group, const uint QQ, const char* Title)
{
	return setGroupMemberTitle(AuthCode, Group, QQ, Title);
}

bool MoeQ::SetGroupMemberCard(const uint Group, const uint QQ, const char* Card)
{
	return setGroupMemberCard(AuthCode, Group, QQ, Card);
}

void MoeQ::GetGroupMemberInfo(const uint Group, const uint QQ)
{
	return getGroupMemberInfo(AuthCode, Group, QQ);
}

void MoeQ::GetStrangerInfo(const uint QQ)
{
	return getStrangerInfo(AuthCode, QQ);
}

void MoeQ::GetGroupInfo(const uint Group)
{
	return getGroupInfo(AuthCode, Group);
}

std::vector<MoeQ::FriendInfo>* MoeQ::GetFriendList()
{
	LPBYTE bin = getFriendList(AuthCode);
	UnPack UnPack(bin);
	uint length = UnPack.GetInt();
	std::vector<MoeQ::FriendInfo>* FriendList = new std::vector<MoeQ::FriendInfo>;
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

std::vector<MoeQ::GroupInfo>* MoeQ::GetGroupList()
{
	LPBYTE bin = getGroupList(AuthCode);
	UnPack UnPack(bin);
	uint length = UnPack.GetInt();
	std::vector<MoeQ::GroupInfo>* GroupList = new std::vector<MoeQ::GroupInfo>;
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

std::vector<MoeQ::GroupMemberInfo>* MoeQ::GetGroupMemberList(const uint group_code)
{
	LPBYTE bin = getGroupMemberList(AuthCode, group_code);
	UnPack UnPack(bin);
	uint length = UnPack.GetInt();
	std::vector<MoeQ::GroupMemberInfo>* GroupMemberList = new std::vector<MoeQ::GroupMemberInfo>;
	GroupMemberList->resize(length);
	for (size_t i = 0; i < length; i++)
	{

	}
	delete[] bin;
	return GroupMemberList;
}

std::vector<uint>* MoeQ::GetGroupAdminList(const uint group_code)
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


void MoeQ::AddLog(const Log::LogType LogType, const Log::MsgType MsgType, const wchar_t* Type, const wchar_t* Msg)
{
	addLog(AuthCode, LogType, MsgType, Type, Msg);
}
