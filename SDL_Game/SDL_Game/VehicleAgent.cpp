#include "VehicleAgent.h"
#include "Game.h"


VehicleAgent::VehicleAgent(Game* _game, string _name, ActorState _state, Tag _tag , Actor* _parent ):GameObject( _game,  _name,  _state,  _tag ,  _parent )
{
	//example
	m_StateMachine = new StateMachine<VehicleAgent>(this);
	m_StateMachine->ChangeState(PursuitState::GetInstance());
	m_StateMachine->CurrentState()->Enter(this);
}

VehicleAgent::~VehicleAgent()
{
	delete m_StateMachine;
}

void VehicleAgent::UpdateGameObject(float _deltatime)
{
	m_StateMachine->UpdateState();
}

bool VehicleAgent::HandleMessage(const Telegram& _msg)
{
	return m_StateMachine->HandleMessage(_msg);
}