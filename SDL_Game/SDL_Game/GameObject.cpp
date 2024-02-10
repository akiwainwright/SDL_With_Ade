#include "GameObject.h"

GameObject::GameObject(Game* _game, string _name, ActorState _state, Tag _tag, Actor* _parent) : Actor(_game, _name,_tag), m_Parent(_parent)
{
	m_Transform = new TransformComponent(this);
}


void GameObject::Update(float deltaTime)
{
	if (m_ActorState == EActive)
	{
		UpdateComponents(deltaTime);
		UpdateGameObject(deltaTime);
	}
}

void GameObject::UpdateComponents(float deltaTime)
{
	for (auto comp : m_Components)
	{
		comp->Update(deltaTime);
	}
}

void GameObject::UpdateGameObject(float deltaTime)
{
}

void GameObject::ProcessInput(const uint8_t* _keyState)
{
	GameObjectInput(_keyState);
}

void GameObject::AddComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->GetUpdateOrder();
	auto iter = m_Components.begin();
	for (;
		iter != m_Components.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	m_Components.insert(iter, component);
}

void GameObject::RemoveComponent(Component* component)
{
	auto iter = std::find(m_Components.begin(), m_Components.end(), component);
	if (iter != m_Components.end())
	{
		m_Components.erase(iter);
	}
}

Actor* GameObject::GetParent()
{
	return m_Parent;
}

bool GameObject::HasComponent(Component* _comp)
{
	auto iter = find(m_Components.begin(), m_Components.end(), _comp);
	if (iter != m_Components.end())
	{
		return true;
	}
	return false;
}


GameObject::~GameObject()
{
	// Need to delete components
// Because ~Component calls RemoveComponent, need a different style loop
	while (!m_Components.empty())
	{
		delete m_Components.back();
	}
}
