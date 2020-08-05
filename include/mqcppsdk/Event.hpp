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

	void Message::DestoryMsg(Message::Msg* Msg)
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
					if(((Message::test*)ReplyMsg->Message)->text != nullptr) delete[] ((Message::test*)ReplyMsg->Message)->text;
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
	}
};

namespace Target
{
	namespace TargetType {
		enum _TargetType
		{
			_private = 0,
			group =1,
			discuss = 2,
		};
	};

	struct _private
	{
		byte FromType;

	}
}