#pragma once
#include "VehicleAgent.h"

class Static
{
public:
	Vector2 m_Position;
	//The orientation value represents an angle from a reference axis
	float m_Orientation;
};


class SteeringOutput
{
public:
	SteeringOutput(GameObject* _obj) {
		m_Linear = _obj->GetTransform()->GetPosition();
		m_Angular = _obj->GetTransform()->GetRotation();
	}
	Vector2 m_Linear;
	float m_Angular;// how fast the character’s orientation is changing. // the number of radians per second that the orientation is changing.
};

class Kinematic
{
public:
	Kinematic(GameObject* _obj) {
		m_Position = _obj->GetTransform()->GetPosition();
		m_Orientation = _obj->GetTransform()->GetRotation();
	}
	Vector2 m_Position;
	float m_Orientation;//the direction in which a character is facing.
	Vector2 m_Velocity;
	float m_Rotation;// angular velocity is rotation, since rotation suggests motion. angular velocity represents how fast the character’s orientation is changing

	void Update(float _deltatime, SteeringOutput* _steering)
	{
		/// If the frame rate is high, then the update time passed to this function is likely to be very small. 
		///The square of this time is likely to be even smaller, and so the contribution of acceleration to position and orientation will be tiny

		//Updates the position and orientation
		float halfTimeSq = 0.5f * _deltatime * _deltatime;
		m_Position += m_Velocity * _deltatime + _steering->m_Linear * halfTimeSq;
		m_Orientation += m_Rotation * _deltatime + _steering->m_Angular * halfTimeSq;

		///the alternative
		//m_Position += m_Velocity * _deltatime;
		//m_Orientation += m_Rotation * _deltatime;

		//and the velocity and rotation
		m_Velocity += _steering->m_Linear * _deltatime;
		m_Rotation += _steering->m_Angular * _deltatime;
	}





};



class KinematicSteeringOutput
{
public:
	KinematicSteeringOutput(GameObject* _obj) {

	}
	Vector2 m_Velocity;
	float m_Rotation;
};


class KinematicSeek
{
public:
	Static m_Character;
	Static m_Target;

	float m_MaxSpeed;



	void GetSteering(KinematicSteeringOutput* _output) {
		_output->m_Velocity = m_Target.m_Position - m_Character.m_Position;

		_output->m_Velocity.Normalised();
		_output->m_Velocity *= m_MaxSpeed;
		m_Character.m_Orientation = NewOrientation(m_Character.m_Orientation, _output->m_Velocity);
		_output->m_Rotation = 0;
	}

	float NewOrientation(float _current, Vector2 _velocity) {
		if (_velocity.Length() > 0)
		{
			return atan2(-_velocity.y, _velocity.x);//this could need to change based on the y direction of the screen
		}
		return _current;
	}

	

};


class Steering
{
public:
	Steering(class Ship* _obj);
	~Steering();

public:
	Vector2 m_Velocity;
	Vector2 m_ForwardDir;
	Vector2 m_Right;
	float m_Mass;
	float m_MaxForce;
	float m_MaxSpeed;
	float m_MaxTurnRate;

	void Update(float _deltaTime);
	void SetTargetPos(Vector2 _pos);

	Vector2 m_TargetPos;
	class Ship* m_Ship;
};


