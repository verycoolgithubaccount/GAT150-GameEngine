#pragma once
#include "Component.h"

class CollisionComponent : public Component
{
public:
	virtual bool CheckCollision(const CollisionComponent* collision) = 0;
};