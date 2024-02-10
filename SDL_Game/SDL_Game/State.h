#pragma once
#include "BasicIncludes.h"
#include "Actor.h"
#include "Events.h"

template<class Actor>

class State
{
public:
	//this execute if the agent receives a message from the message Dispatcher
	virtual void Enter(Actor* _agent) = 0;
	virtual void Execute(Actor* _agent) = 0;
	virtual void Exit(Actor* _agent) = 0;
	virtual bool OnMessage(Actor* _agent, const Telegram&) = 0;
	virtual ~State() {}

};


template<class Actor>
class StateMachine
{
private:
	State<Actor>* m_GlobalState;
	State<Actor>* m_CurrentState;
	State<Actor>* m_PreviousState;
	Actor* m_Agent;

public:
	State<Actor>* GlobalState() const { return m_GlobalState; }
	State<Actor>* CurrentState() const { return m_CurrentState; }
	State<Actor>* PreviousState() const { return m_PreviousState; }
	//bool IsInState(const State<Actor>& _state) const { return _state == m_CurrentState || _state == m_GlobalState; }
	bool IsInState(const State<Actor>& _state) const { return typeid(*m_CurrentState) == typeid(_state); }

public:
	StateMachine(Actor* _agent) :m_Agent(_agent), m_GlobalState(nullptr), m_CurrentState(nullptr), m_PreviousState(nullptr) {}

	void ChangeState(State<Actor>* _newState) {
		if (_newState == m_CurrentState)
		{
			return;
		}
		ChangeStateRoutine(_newState);
	}
	void RevertState()
	{
		if (!m_PreviousState)
		{
			ChangeState(m_PreviousState);
		}
	}

	bool HandleMessage(const Telegram& _msg) const {
		//first see if the current state is valid and that it can handle the message
		if (m_CurrentState && m_CurrentState->OnMessage(m_Agent, _msg))
		{
			return true;
		}

		// if not, and if a global state has been implemented, send the message to the global state
		if (m_GlobalState && m_GlobalState->OnMessage(m_Agent, _msg))//global state
		{
			return true;
		}

		return false;
	}
	void UpdateState()
	{
		if (!m_GlobalState)
		{
			return;
		}
		m_GlobalState->Execute(m_Agent);

		if (!m_CurrentState)
		{
			return;
		}
		m_CurrentState->Execute(m_Agent);

	}
private:


	void ChangeStateRoutine(State<Actor>* _newState) {
		assert(_newState);
		m_CurrentState->Exit(m_Agent);

		m_PreviousState = m_CurrentState;
		m_CurrentState = _newState;
		m_CurrentState->Enter(m_Agent);
	}
};
