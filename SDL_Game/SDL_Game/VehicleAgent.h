#pragma once
#include "VehicleState.h"
#include "GameObject.h"


class VehicleAgent :public GameObject
{
public:

	VehicleAgent(class Game* _game, string _name, ActorState _state, Tag _tag = UNTAGGED, Actor* _parent = nullptr);
	~VehicleAgent();
	void UpdateGameObject(float _deltatime)override;
	bool HandleMessage(const Telegram& _msg);

	//this is for the class that inherits from this class
	StateMachine<VehicleAgent>* GetStateMachine()const { return m_StateMachine; }

private:
	//this is for the class that inherits from this class
	StateMachine<VehicleAgent>* m_StateMachine;
};




