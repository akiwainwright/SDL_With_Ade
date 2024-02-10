#include "TransformComponent.h"
#include "GameObject.h"

TransformComponent::TransformComponent(GameObject* _owner) :Component(_owner), m_Position(Vector2(0, 0)), m_Scale(Vector2(1, 1)), m_Rotation(0.0f)
{

}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::Update(float _deltaTime)
{
	
}