
#pragma once
#include "SpriteComponent.h"
#include <vector>
class AnimatorComponent : public SpriteComponent
{
public:
	AnimatorComponent(class GameObject* _owner, int _drawOrder = 100);
	// Update animation every frame (overridden from component)
	void Update(float _deltaTime) override;
	// Set the textures used for animation
	void SetAnimTextures(const std::vector<SDL_Texture*>& _textures);
	float GetAnimFPS() const { return m_AnimFPS; }
	void SetAnimFPS(float _fps) { m_AnimFPS = _fps; }
private:
	// All textures in the animation
	std::vector<SDL_Texture*> m_AnimTextures;
	// Current frame displayed
	float m_CurrentFrame;
	// Animation frame rate
	float m_AnimFPS;
};
