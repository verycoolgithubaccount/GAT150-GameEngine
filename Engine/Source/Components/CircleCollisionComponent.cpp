#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

FACTORY_REGISTER(CircleCollisionComponent)

void CircleCollisionComponent::Initialize()
{
    //
}

void CircleCollisionComponent::Update(float dt)
{
    //
}

bool CircleCollisionComponent::CheckCollision(const CollisionComponent* collision)
{
    float r1 = m_radius;
    float r2 = (dynamic_cast<const CircleCollisionComponent*>(collision))->GetRadius();

    float distance = m_owner->GetTransform().position.Distance(collision->m_owner->GetTransform().position);

    return (distance <= r1 + r2);
}

void CircleCollisionComponent::Read(const json_t& value)
{
	Component::Read(value);
    READ_DATA_NAME(value, "radius", m_radius);
}

void CircleCollisionComponent::Write(json_t& value)
{
}