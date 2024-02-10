
#include "SpriteComponent.h"
#include "GameObject.h"
#include "Game.h"

SpriteComponent::SpriteComponent(GameObject* owner, int drawOrder)
	:Component(owner)
	,m_Texture(nullptr)
	,m_DrawOrder(drawOrder)
	,m_TexWidth(0)
	,m_TexHeight(0)
{
	m_Owner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	m_Owner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (m_Texture)
	{
		SDL_Rect r;
		// Scale the width/height by owner's scale
		r.w = static_cast<int>(m_TexWidth * m_Owner->GetTransform()->GetScale().x);
		r.h = static_cast<int>(m_TexHeight * m_Owner->GetTransform()->GetScale().y);
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(m_Owner->GetTransform()->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(m_Owner->GetTransform()->GetPosition().y - r.h / 2);

		// Draw (have to convert angle from radians to degrees, and clockwise to counter)
		SDL_RenderCopyEx(renderer,
			m_Texture,
			nullptr,
			&r,
			-radToDeg(m_Owner->GetTransform()->GetRotation()),
			nullptr,
			SDL_FLIP_NONE);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	m_Texture = texture;
	// Set width/height
	SDL_QueryTexture(texture, nullptr, nullptr, &m_TexWidth, &m_TexHeight);
}
