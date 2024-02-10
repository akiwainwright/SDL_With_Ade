
#pragma once
#include "GameObject.h"
class Ship : public GameObject
{
public:
	Ship(class Game* _game, string _name, ActorState _state, Tag _tag = UNTAGGED, Actor* _parent = nullptr);
	
	void UpdateGameObject(float _deltaTime) override;
	void GameObjectInput(const uint8_t* _state) override;
	float GetRightSpeed() const { return m_RightSpeed; }
	float GetDownSpeed() const { return m_DownSpeed; }
private:
	float m_RightSpeed;
	float m_DownSpeed;
};