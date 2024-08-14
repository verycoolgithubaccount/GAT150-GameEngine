#pragma once
#include "PhysicsComponent.h"

class EnginePhysicsComponent : public PhysicsComponent
{
public:
	CLASS_DECLARATION(EnginePhysicsComponent);

	// Inherited via PhysicsComponent
	void Initialize() override;
	void Update(float dt) override;
	void ApplyForce(const Vector2& force) override;
	void SetPosition(const Vector2& position) override;
	void SetVelocity(const Vector2& velocity) override { m_velocity = velocity; }
};