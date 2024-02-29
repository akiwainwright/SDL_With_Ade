#pragma once
#include "GameObject.h"
#include "KinematicSteeringBehaviour.h"

class Ship : public GameObject
{
public:
	Ship(class Game* _game, string _name, ActorState _state, Tag _tag = UNTAGGED, Actor* _parent = nullptr);
	
	void UpdateGameObject(float _deltaTime) override;
	void GameObjectInput(const uint8_t* _state) override;
	float GetRightSpeed() const { return m_RightSpeed; }
	float GetDownSpeed() const { return m_DownSpeed; }
	void SetTarget(Vector2 _pos);
private:
	Vector2 m_TargetPos;
	float m_RightSpeed;
	float m_DownSpeed;
	//SteeringOutput* m_SteeringOutput;
	//Kinematic* m_Kinematic;
	//KinematicSeek* m_Seek;
	Steering* m_Steering;
};