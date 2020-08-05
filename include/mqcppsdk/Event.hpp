#pragma once
namespace Message
{
	namespace MsgType {
		enum _MsgType
		{
			text = 1,
			classcal_face = 2,
			expression = 6,
			picture = 8,
			xml = 12,
			red_packet = 56,
			reply = 93,
			json = 115,
		};
	};

	struct Msg
	{
		MsgType::_MsgType MsgType;
		Msg* NextPoint = nullptr;
		void* Message;
	};

	struct test
	{
		char* text = nullptr;
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
		char* discribe = nullptr;
	};
	struct reply
	{
		uint MsgId;
		uint QQ;
		uint Time;
		Message::Msg* Msg = nullptr;
	};
	/*
	void DestoryMsg(Message::Msg* Msg)
	{
		Message::Msg* ThisMsg = Msg;
		while (ThisMsg != nullptr)
		{
			switch (ThisMsg->MsgType)
			{
			case Message::MsgType::text:
				delete[]((Message::test*)ThisMsg->Message)->text;
				break;
			case Message::MsgType::classcal_face:
				break;
			case Message::MsgType::expression:
				delete[]((Message::expression*)ThisMsg->Message)->MD5;
				break;
			case Message::MsgType::picture:
				delete[]((Message::picture*)ThisMsg->Message)->MD5;
				delete[]((Message::picture*)ThisMsg->Message)->URL;
				break;
			case Message::MsgType::xml:
				delete[]((Message::xml*)ThisMsg->Message)->text;
				if (((Message::xml*)ThisMsg->Message)->discribe != nullptr) delete[]((Message::xml*)ThisMsg->Message)->discribe;
				break;
			case Message::MsgType::reply:
			{
				Message::Msg* ReplyMsg = ((Message::reply*)ThisMsg->Message)->Msg;
				while (ReplyMsg != nullptr)
				{
					if (((Message::test*)ReplyMsg->Message)->text != nullptr) delete[]((Message::test*)ReplyMsg->Message)->text;
					delete ThisMsg->Message;
					Message::Msg* tmp = ThisMsg->NextPoint;
					delete ThisMsg;
					ThisMsg = tmp;
				}
			}
			break;
			default:
				break;
			}
			delete ThisMsg->Message;
			Message::Msg* tmp = ThisMsg->NextPoint;
			delete ThisMsg;
			ThisMsg = tmp;
		};
	}*/
};

namespace Target
{
	namespace TargetType {
		enum _TargetType
		{
			_private = 0,
			group = 1,
			discuss = 2,
		};
	};

	struct Target
	{
		TargetType::_TargetType TargetType;
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
	namespace ReturnType
	{
		enum _ReturnType
		{
			ignore, //Ignore 忽略
			block, //Block 阻塞
		};
	}

	namespace LifeCycleEvent
	{
		namespace LifeCycleEventType
		{
			enum _LifeCycleEventType {
				StartUp,
				ShutDown,
				PluginEnabled,
				PluginDisabled
			};
		}
	}

	namespace NoticeEvent 
	{
		namespace NoticeEventType
		{
			enum _NoticeEventType {
				group_fileupload, //Group file upload 群文件上传
				group_adminchange, //Group administrator changes 群管理员变动
				group_memberchange, //The change in the number of group members 群成员数量变动
				group_mute, //Group ban 群禁言
				friend_added, //Friend added 好友已添加
			};
		}

		struct NoticeEvent
		{
			Event::NoticeEvent::NoticeEventType::_NoticeEventType NoticeEventType;
			void* Information;
		};

		struct FileInfo
		{
			char* Name;
			char* ID;
			uint64_t size;
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
		namespace RequestEventType
		{
			enum _RequestEventType {
				add_friend,
				add_group
			};
		}

		namespace ReturnType
		{
			enum _ReturnType
			{
				agree, //Agree 同意
				disagree, //Disagree 不同意
				ignore, //Ignore 忽略
			};
		}

		struct RequestEvent
		{
			Event::RequestEvent::RequestEventType::_RequestEventType RequestEventType;
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