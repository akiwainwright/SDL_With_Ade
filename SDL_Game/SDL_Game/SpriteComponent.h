
#pragma once
#include "Component.h"
#include <SDL.h>
class SpriteComponent : public Component
{
public:
	// (Lower draw order corresponds with further back)
	SpriteComponent(class GameObject* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return m_DrawOrder; }
	int GetTexHeight() const { return m_TexHeight; }
	int GetTexWidth() const { return m_TexWidth; }
protected:
	SDL_Texture* m_Texture;
	int m_DrawOrder;
	int m_TexWidth;
	int m_TexHeight;
};
