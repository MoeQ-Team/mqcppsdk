#include "mqcppsdk.h"

void MoeQ::SetAuthCode(uint64_t _AuthCode)
{
	AuthCode = _AuthCode;
}

const std::vector<MoeQ::FriendInfo>* MoeQ::GetFriendList()
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

const std::vector<MoeQ::GroupInfo>* MoeQ::GetGroupList()
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

void MoeQ::AddLog(const Log::LogType LogType, const Log::MsgType MsgType, const wchar_t* Type, const wchar_t* Msg)
{
	addLog(AuthCode, LogType, MsgType, Type, Msg);
}

bool MoeQ::SendLike(const uint QQ, const int Times)
{
	return sendLike(AuthCode, QQ, Times);
}
