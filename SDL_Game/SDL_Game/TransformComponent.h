#pragma once
#include "Component.h"
#include "CustomMaths.h"

class TransformComponent : public Component
{
public:
	TransformComponent(GameObject* _owner);
	~TransformComponent();

	void Update(float _deltaTime)override;

	Vector2& GetPosition() { return m_Position; }
	void SetPosition(const Vector2& pos) { m_Position = pos; }
	Vector2& GetScale() { return m_Scale; }
	void SetScale(const Vector2& scale) { m_Scale = scale; }
	float GetRotation() { return m_Rotation; }
	void SetRotation(float rotation) { m_Rotation = rotation; }


	//const Vector2& GetPosition() const { return m_Position; }
	//void SetPosition(const Vector2& pos) { m_Position = pos; }
	//Vector2 GetScale() const { return m_Scale; }
	//void SetScale(float scale) { m_Scale = scale; }
	//float GetRotation() const { return m_Rotation; }
	//void SetRotation(float rotation) { m_Rotation = rotation; }

private:

	Vector2 m_Position;
	Vector2 m_Scale;
	float m_Rotation;
};


