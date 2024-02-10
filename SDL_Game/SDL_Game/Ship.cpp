
#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "TransformComponent.h"
#include "Game.h"

Ship::Ship(Game* _game, string _name, ActorState _state, Tag _tag, Actor* _parent )
	:GameObject(_game, _name, _state, _tag, _parent)
	,m_RightSpeed(0.0f)
	,m_DownSpeed(0.0f)
{
	
	AnimatorComponent* asc = new AnimatorComponent(this);
	std::vector<SDL_Texture*> anims = {
		_game->GetTexture("Assets/Textures/Ship01.png"),
		_game->GetTexture("Assets/Textures/Ship02.png"),
		_game->GetTexture("Assets/Textures/Ship03.png"),
		_game->GetTexture("Assets/Textures/Ship04.png"),
	};
	asc->SetAnimTextures(anims);
}

void Ship::UpdateGameObject(float _deltaTime)
{
	GameObject::UpdateGameObject(_deltaTime);
	// Update position based on speeds and delta time
	Vector2 pos = GetTransform()->GetPosition();
	pos.x += m_RightSpeed * _deltaTime;
	pos.y += m_DownSpeed * _deltaTime;
	// Restrict position to left half of screen
	if (pos.x < 25.0f)
	{
		pos.x = 25.0f;
	}
	else if (pos.x > 500.0f)
	{
		pos.x = 500.0f;
	}
	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 743.0f;
	}
	GetTransform()->SetPosition(pos);
}

void Ship::GameObjectInput(const uint8_t* _state)
{
	m_RightSpeed = 0.0f;
	m_DownSpeed = 0.0f;
	// right/left
	if (_state[SDL_SCANCODE_D])
	{
		m_RightSpeed += 250.0f;
	}
	if (_state[SDL_SCANCODE_A])
	{
		m_RightSpeed -= 250.0f;
	}
	// up/down
	if (_state[SDL_SCANCODE_S])
	{
		m_DownSpeed += 300.0f;
	}
	if (_state[SDL_SCANCODE_W])
	{
		m_DownSpeed -= 300.0f;
	}
}
