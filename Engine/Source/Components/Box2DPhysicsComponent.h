#pragma once
#include "PhysicsComponent.h"
#include "Physics/RigidBody.h"

#include <memory>

class Box2DPhysicsComponent : public PhysicsComponent
{
public:
	Box2DPhysicsComponent() = default;
	Box2DPhysicsComponent(const Box2DPhysicsComponent& other);

	CLASS_DECLARATION(Box2DPhysicsComponent)
	CLASS_PROTOTYPE(Box2DPhysicsComponent)

	void Initialize() override;
	void Update(float dt) override;

	void ApplyForce(const Vector2& force) override;
	void ApplyTorque(float torque) override;

	void SetPosition(const Vector2& position) override;
	void SetVelocity(const Vector2& velocity) override;

public:
	RigidBody::def_t rigidBodyDef;
	Vector2 size{ 0, 0 };
	Vector2 scale{ 1, 1 };

private:
	std::unique_ptr<RigidBody> m_rigidBody;
};