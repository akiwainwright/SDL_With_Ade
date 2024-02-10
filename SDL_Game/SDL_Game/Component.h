#pragma once
#include <stdint.h>
class GameObject;





class Component
{
public:
	// (the lower the update order, the earlier the component updates)
	Component(class GameObject* _owner, int _updateOrder = 100);
	virtual ~Component();
	virtual void Update(float _deltaTime);

	int GetUpdateOrder() const { return m_UpdateOrder; }
protected:
	// Owning actor
	class GameObject* m_Owner;
	// Update order of component
	int m_UpdateOrder;
};
