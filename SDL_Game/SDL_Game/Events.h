#pragma once
#include "BasicIncludes.h"
#include "Game.h"

class Actor;

enum MessageType
{
	MsgExample,
	MSG_ReceiveBall,
	MSG_SupportAttacker,
	MSG_Wait,
	MSG_GoHome,
	MSG_PassToMe,
};

struct Telegram
{
public:
	//the entity that sent this telegram
	class Actor* m_Sender;

	//the entity that received this telegram
	class Actor* m_Receiver;

	//the messages itself. These are enumerators
	MessageType m_Msg;

	//messages can be dispatched immediately or delayed for a specific amount of time.
	//if a delay is necessary, this field is stamped with the time
	//the message should be dispatched
	double m_DispatchTime;

	//any additional info that may acompany the message
	void* m_ExtraInfo;

	Telegram(double _dispatchTime, Actor* _sender, Actor* _receiver, MessageType _msg, void* _extraInfo) {
		m_DispatchTime = _dispatchTime;
		m_Sender = _sender;
		m_Receiver = _receiver;
		m_Msg = _msg;
		m_ExtraInfo = _extraInfo;
	}

	bool operator<(const Telegram& _tele) const noexcept {
		return m_DispatchTime < _tele.m_DispatchTime;
	}

};


class MessageDispatcher
{
public:

	static MessageDispatcher* Instance() { return m_Instance = (m_Instance != nullptr) ? m_Instance : new MessageDispatcher(); }

	void DispatchMessage(double _delay, Actor* _sender, Actor* _receiver, MessageType _msg, void* _extraInfo);

	//send out any delay messages. this method is called each time through the main game loop
	void DispatchDelayedMessages();

	void SetGame(class Game* _gameMode);

	~MessageDispatcher();

private:
	static MessageDispatcher* m_Instance;

	//the set is used as the container for the delayed messages because of the benefit of automatic sorting and avoidance of duplicates. 
	//Messages are sorted by their dispatch time
	set<Telegram> m_PriorityQueue;

	//this method is utilized by DispatchMessage or DispatchDelayedMessages
	//this method calls the message handling member function of the receiving entity(m_Receiver) wiith the telegram
	void Discharge(Actor* _receiver, const Telegram& _msg);

	MessageDispatcher();

	class Game* m_GameMode;

};


