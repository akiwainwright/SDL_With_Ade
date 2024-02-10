
#pragma once
#include <vector>
#include "CustomMaths.h"
#include "Events.h"

class Actor
{
public:
	enum ActorState
	{
		EActive,
		EPaused,
		EDead
	};

	enum Tag
	{
		UNTAGGED
	};
	Actor(class Game* _game, string _name, Tag _tag = UNTAGGED);
	virtual ~Actor();
	virtual bool HandleMessage(const Telegram& _msg) = 0;

	
	virtual void Update(float _deltaTime){}

	ActorState GetState() const { return m_ActorState; }
	void SetState(ActorState _state) { m_ActorState = _state; }

	class Game* GetGame() { return m_Game; }

	void SetTag(Tag _tag) { m_Tag = _tag; }
	Tag GetTag()const { return m_Tag; }


protected:
	// Actor's state
	ActorState m_ActorState;
	Tag m_Tag;
	//// Transform
	//Vector2 m_Position;
	//Vector2 m_Scale;
	//float m_Rotation;

	//std::vector<class Component*> m_Components;

	string m_Name;
	class Game* m_Game;
};
