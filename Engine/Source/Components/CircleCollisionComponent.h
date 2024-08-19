#pragma once
#include "CollisionComponent.h"

class CircleCollisionComponent : public CollisionComponent
{
private:
	float m_radius = 0;
public:
	CLASS_DECLARATION(CircleCollisionComponent)

	void Initialize() override;
	void Update(float dt) override;
	bool CheckCollision(const CollisionComponent* collision) override;

	float GetRadius() const { return m_radius; }
};