#include "Component.h"
#include "GameObject.h"

//
//Component::Component(GameObject* _owner)
//{
//	m_Owner = _owner;
//	if (!m_Owner->HasComponent(this))
//	{
//		m_Owner->AddComponent(this);
//	}
//	
//	
//}
//
//Component::~Component()
//{
//	m_Owner->RemoveComponent(this);
//}


Component::Component(GameObject* _owner, int _updateOrder)
	:m_Owner(_owner)
	, m_UpdateOrder(_updateOrder)
{
	// Add to actor's vector of components
	m_Owner->AddComponent(this);
}

Component::~Component()
{
	m_Owner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}
