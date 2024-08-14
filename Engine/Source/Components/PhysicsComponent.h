#pragma once
#include "Component.h"

class PhysicsComponent : public Component
{
protected:
	Vector2 m_velocity{ 0, 0 };
	Vector2 m_acceleration{ 0, 0 };
	float m_mass = 1;
	float m_damping = 0;
public:
	CLASS_DECLARATION(PhysicsComponent);

	virtual void ApplyForce(const Vector2& force) = 0;
	virtual void SetPosition(const Vector2& position) = 0;
	virtual void SetVelocity(const Vector2& velocity) = 0;
	
	void SetMass(float mass) { m_mass = mass; }
	void SetDamping(float damping) { m_damping = damping; }
	void SetAcceleration(const Vector2& acceleration) { m_acceleration = acceleration; }

	const Vector2& GetVelocity() const { return m_velocity; }
	const Vector2& GetAcceleration() const { return m_acceleration; }
	const float GetMass() const { return m_mass; }
	const float GetDamping() const { return m_damping; }
};