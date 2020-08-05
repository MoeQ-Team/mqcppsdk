#include "MoeQ.h"

void MoeQ::SetAuthCode(uint64_t _AuthCode)
{
	AuthCode = _AuthCode;
}

std::vector<MoeQ::FriendInfo>* MoeQ::GetFriendList()
{
	UnPack UnPack(getFriendList(AuthCode));
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
	return FriendList;
}

std::vector<MoeQ::GroupInfo>* MoeQ::GetGroupList()
{
	UnPack UnPack(getGroupList(AuthCode));
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
	return GroupList;
}
