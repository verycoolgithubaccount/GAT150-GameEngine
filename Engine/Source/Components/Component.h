#pragma once
#include "Framework/Object.h"

class Component : public Object
{
protected:
	
public:
	virtual void Update(float dt) = 0;
	class Actor* m_owner{ nullptr };
	//Actor* GetOwner() { return m_owner; }
	//void SetOwner(Actor* owner) { m_owner = owner; }
};