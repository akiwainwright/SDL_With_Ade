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
	void SetRotation(const Vector2& _pos);

	Vector2 GetForward() const { return Vector2(cos(m_Rotation),-sin(m_Rotation)); }
	Vector2 GetRight() const { return Vector2(cosf(m_Rotation + degToRad(90)), -sinf(m_Rotation + degToRad(90))); }

	//functions
	//LookAt - Rotates the transform so the forward vector points at /target/'s current position
	//RotateAround - Rotates the transform about axis passing through point in world coordinates by angle degrees or radians
	//Translate(Vector2 translation) - Moves the transform in the direction and distance of translation


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


