#include "EnginePhysicsComponent.h"
#include "Framework/Actor.h"

FACTORY_REGISTER(EnginePhysicsComponent)

void EnginePhysicsComponent::Initialize()
{
}

void EnginePhysicsComponent::Update(float dt)
{
	m_velocity += m_acceleration * dt;
	m_owner->SetPosition(m_owner->GetTransform().position + (m_velocity * dt));
	m_velocity *= 1.0f / (1.0f + m_damping * dt);

	m_acceleration = Vector2{ 0, 0 };
}

void EnginePhysicsComponent::ApplyForce(const Vector2& force)
{
	assert(m_mass != 0);
	m_acceleration += force / m_mass;
}

void EnginePhysicsComponent::ApplyTorque(float angle)
{
	m_owner->Rotate(angle);
}

void EnginePhysicsComponent::SetPosition(const Vector2& position)
{
	m_owner->SetPosition(position);
}

void EnginePhysicsComponent::Read(const json_t& value)
{
	Component::Read(value);
	PhysicsComponent::Read(value);
}

void EnginePhysicsComponent::Write(json_t& value)
{
	//
}