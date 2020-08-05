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
		// 0 ���Ժ��� 1 ��������״̬ 2 ����Ⱥ 3����������
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
			ignore, //Ignore ����
			block, //Block ����
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
				group_fileupload, //Group file upload Ⱥ�ļ��ϴ�
				group_adminchange, //Group administrator changes Ⱥ����Ա�䶯
				group_memberchange, //The change in the number of group members Ⱥ��Ա�����䶯
				group_mute, //Group ban Ⱥ����
				friend_added, //Friend added ���������
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
			uint Type; // 0 Set up administrator �����ù���Ա 1 Cancelled administrator ��ȡ������Ա
		};
		struct group_memberchange
		{
			uint FromGroup;
			uint FromQQ;
			uint OperateQQ;
			uint Type; // 0 Increase ���� 1 Decrease(Don't include kicked) ����(����������) 2 Kicked ����
		};
		struct group_mute
		{
			uint FromGroup;
			uint FromQQ;
			uint OperateQQ;
			uint Type; // 0 Ban ������ 1 Free ����� 
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
				agree, //Agree ͬ��
				disagree, //Disagree ��ͬ��
				ignore, //Ignore ����
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
			uint Type; // 0 Others apply to join the group ����������Ⱥ 1 Myself was invited to join the group �Լ�������Ⱥ
		};
	}
}