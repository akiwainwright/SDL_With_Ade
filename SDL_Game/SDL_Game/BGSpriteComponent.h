
#pragma once
#include "SpriteComponent.h"
#include <vector>
#include "CustomMaths.h"
class BGSpriteComponent : public SpriteComponent
{
public:
	// Set draw order to default to lower (so it's in the background)
	BGSpriteComponent(class GameObject* owner, int drawOrder = 10);
	// Update/draw overridden from parent
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	// Set the textures used for the background
	void SetBGTextures(const std::vector<SDL_Texture*>& textures);
	// Get/set screen size and scroll speed
	void SetScreenSize(const Vector2& size) { m_ScreenSize = size; }
	void SetScrollSpeed(float speed) { m_ScrollSpeed = speed; }
	float GetScrollSpeed() const { return m_ScrollSpeed; }
private:
	// Struct to encapsulate each bg image and its offset
	struct BGTexture
	{
		SDL_Texture* m_Texture;
		Vector2 m_Offset;
	};
	std::vector<BGTexture> m_BGTextures;
	Vector2 m_ScreenSize;
	float m_ScrollSpeed;
};
