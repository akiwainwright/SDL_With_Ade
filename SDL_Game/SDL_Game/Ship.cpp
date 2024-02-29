
#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "TransformComponent.h"
#include "Game.h"

Ship::Ship(Game* _game, string _name, ActorState _state, Tag _tag, Actor* _parent )
	:GameObject(_game, _name, _state, _tag, _parent)
	,m_RightSpeed(250.0f)
	,m_DownSpeed(250.0f)
{
	
	AnimatorComponent* asc = new AnimatorComponent(this);
	std::vector<SDL_Texture*> anims = {
		_game->GetTexture("Assets/Textures/Ship01.png"),
		_game->GetTexture("Assets/Textures/Ship02.png"),
		_game->GetTexture("Assets/Textures/Ship03.png"),
		_game->GetTexture("Assets/Textures/Ship04.png"),
	};
	asc->SetAnimTextures(anims);
	
	m_Steering = new Steering(this);
}

void Ship::UpdateGameObject(float _deltaTime)
{
	GameObject::UpdateGameObject(_deltaTime);
	// Update position based on speeds and delta time
	//Vector2 pos = GetTransform()->GetPosition();
	//pos.x += m_RightSpeed * _deltaTime;
	//pos.y += m_DownSpeed * _deltaTime;
	// Restrict position to left half of screen
	//if (m_TargetPos.x < 25.0f)
	//{
	//	m_TargetPos.x = 25.0f;
	//}
	//else if (m_TargetPos.x > 500.0f)
	//{
	//	m_TargetPos.x = 500.0f;
	//}
	//if (m_TargetPos.y < 25.0f)
	//{
	//	m_TargetPos.y = 25.0f;
	//}
	//else if (m_TargetPos.y > 743.0f)
	//{
	//	m_TargetPos.y = 743.0f;
	//}


	Vector2 pos = GetTransform()->GetPosition();
	float rot = GetTransform()->GetRotation();
	

	//GetTransform()->SetRotation(m_TargetPos);
	//if (pos.x < m_TargetPos.x)
	//{
	//	pos.x += m_RightSpeed * _deltaTime;
	//}
	//if (pos.x > m_TargetPos.x)
	//{
	//	pos.x -= m_RightSpeed * _deltaTime;
	//}
	//if (pos.y < m_TargetPos.y)
	//{
	//	pos.y += m_DownSpeed * _deltaTime;
	//}
	//if (pos.y > m_TargetPos.y)
	//{
	//	pos.y -= m_DownSpeed * _deltaTime;
	//}

	//m_Kinematic->Update(_deltaTime, m_SteeringOutput);
	//GetTransform()->SetPosition(pos);
	m_Steering->Update(_deltaTime);
}

void Ship::GameObjectInput(const uint8_t* _state)
{
	//m_RightSpeed = 0.0f;
	//m_DownSpeed = 0.0f;
	//// right/left
	//if (_state[SDL_SCANCODE_D])
	//{
	//	m_RightSpeed += 250.0f;
	//}
	//if (_state[SDL_SCANCODE_A])
	//{
	//	m_RightSpeed -= 250.0f;
	//}
	//// up/down
	//if (_state[SDL_SCANCODE_S])
	//{
	//	m_DownSpeed += 300.0f;
	//}
	//if (_state[SDL_SCANCODE_W])
	//{
	//	m_DownSpeed -= 300.0f;
	//}

	


}

void Ship::SetTarget(Vector2 _pos)
{
	m_TargetPos = _pos;
	m_Steering->SetTargetPos(m_TargetPos);
	Static pos;
	pos.m_Position = _pos;
}
