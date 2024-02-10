#pragma once
#include "State.h"


class VehicleAgent;

//change the template typename to the class that inherits from vehicle agent 
class PursuitState : public State<VehicleAgent>
{
public:
	static PursuitState* GetInstance();
	void Enter(VehicleAgent* _agent);
	void Execute(VehicleAgent* _agent);
	void Exit(VehicleAgent* _agent);
	bool OnMessage(VehicleAgent* _agent, const Telegram&);

private:
	static PursuitState* m_Instance;
	PursuitState(){}
};



