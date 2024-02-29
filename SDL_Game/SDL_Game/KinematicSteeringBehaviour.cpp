#include "KinematicSteeringBehaviour.h"
#include "Ship.h"

Steering::Steering(Ship* _obj)
{
	m_Ship = _obj;
	m_TargetPos = Vec2_Zero();
	m_Velocity = Vec2_Zero();
	m_Mass = 1.0f;
	m_MaxForce = 2.0f;
	m_MaxSpeed = 150.0f;
	m_MaxTurnRate = PI;
	m_ForwardDir = m_Ship->GetTransform()->GetForward();
}

void Steering::Update(float _deltaTime)
{
	Vector2 steeringForce = Vec2_Zero();
	Vector2 desiredVel = (m_TargetPos - m_Ship->GetTransform()->GetPosition()).Normalise() * m_MaxSpeed;
	steeringForce = desiredVel - m_Velocity;
	//acceleration = force / mass
	Vector2 acceleration = steeringForce / m_Mass;
	m_Velocity += acceleration * _deltaTime;
	m_Velocity.Truncate(m_MaxSpeed);

	if (m_Velocity.LenghtSqrd() >FLT_EPSILON)
	{
		m_ForwardDir = m_Velocity.Normalise();
		//m_Right = rotateVector2()
		m_Ship->GetTransform()->SetRotation(atan2(-m_ForwardDir.y, m_ForwardDir.x));
	}
	m_Ship->GetTransform()->SetPosition(m_Ship->GetTransform()->GetPosition() + (m_Velocity * _deltaTime));
}

void Steering::SetTargetPos(Vector2 _pos)
{
	m_TargetPos = _pos;
}
