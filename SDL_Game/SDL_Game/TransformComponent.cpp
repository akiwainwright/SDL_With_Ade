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

void TransformComponent::SetRotation(const Vector2& _pos)
{
	Vector2 dir =  _pos - m_Position;
	dir.Normalised();
	//float dotResult = Vector2::DotProduct(GetForward(), _pos);
	//float angle = acos(dotResult);
	float angle = atan2(-dir.y,dir.x);
	SetRotation(angle);
}
