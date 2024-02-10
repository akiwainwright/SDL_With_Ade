
#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include "CustomMaths.h"

Actor::Actor(Game* _game, string _name, Tag _tag )
	:m_ActorState(EActive)
	, m_Game(_game)
{
	m_Name = _name;
	m_Tag = _tag;
	m_Game->AddActor(this);
}

Actor::~Actor()
{
	m_Game->RemoveActor(this);

}
