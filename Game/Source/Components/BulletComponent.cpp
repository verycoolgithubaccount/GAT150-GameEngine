#include "BulletComponent.h"
#include "Engine.h"

FACTORY_REGISTER(BulletComponent);

void BulletComponent::Initialize()
{
	m_owner->OnCollisionEnter = std::bind(&BulletComponent::OnCollisionEnter, this, std::placeholders::_1);
	m_owner->GetComponent<PhysicsComponent>()->SetVelocity(m_owner->GetInitialVelocity() + Vector2{m_speed, 0.0f}.Rotate(Math::DegToRad(m_owner->GetTransform().rotation)));
}

void BulletComponent::Update(float dt)
{
	Vector2 cameraOffset = m_owner->GetScene()->GetEngine()->GetRenderer().GetCameraOffset();
	float screenWidth = m_owner->GetScene()->GetEngine()->GetRenderer().GetWidth();
	float screenHeight = m_owner->GetScene()->GetEngine()->GetRenderer().GetHeight();

	if ((m_owner->GetTransform().position + cameraOffset).x > (screenWidth * 1.1) ||
		(m_owner->GetTransform().position + cameraOffset).x < 0 - (screenWidth * 0.1) ||
		(m_owner->GetTransform().position + cameraOffset).y >(screenHeight * 1.1) ||
		(m_owner->GetTransform().position + cameraOffset).y < 0 - (screenHeight * 0.1))
	{
		m_owner->MakeDestroyed();
	}
}

void BulletComponent::OnCollisionEnter(Actor* actor)
{
	if (actor->GetTag() != "background") m_owner->MakeDestroyed();
}

void BulletComponent::Read(const json_t& value)
{
	READ_DATA_NAME(value, "speed", m_speed);
}

void BulletComponent::Write(json_t& value)
{
	//
}