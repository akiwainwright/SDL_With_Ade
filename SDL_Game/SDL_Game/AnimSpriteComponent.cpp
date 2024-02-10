
#include "AnimSpriteComponent.h"
#include "Math.h"

AnimatorComponent::AnimatorComponent(GameObject* _owner, int _drawOrder)
	:SpriteComponent(_owner, _drawOrder)
	, m_CurrentFrame(0.0f)
	, m_AnimFPS(24.0f)
{
}

void AnimatorComponent::Update(float _deltaTime)
{
	SpriteComponent::Update(_deltaTime);

	if (m_AnimTextures.size() > 0)
	{
		// Update the current frame based on frame rate
		// and delta time
		m_CurrentFrame += m_AnimFPS * _deltaTime;
		
		// Wrap current frame if needed
		while (m_CurrentFrame >= m_AnimTextures.size())
		{
			m_CurrentFrame -= m_AnimTextures.size();
		}

		// Set the current texture
		SetTexture(m_AnimTextures[static_cast<int>(m_CurrentFrame)]);
	}
}

void AnimatorComponent::SetAnimTextures(const std::vector<SDL_Texture*>& _textures)
{
	m_AnimTextures = _textures;
	if (m_AnimTextures.size() > 0)
	{
		// Set the active texture to first frame
		m_CurrentFrame = 0.0f;
		SetTexture(m_AnimTextures[0]);
	}
}
