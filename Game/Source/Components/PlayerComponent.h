#pragma once
#include "Components/Component.h"
#include "Math/Vector2.h"

class PlayerComponent : public Component
{
private:
	float m_speed{ 0 };
	float m_health{ 10 };
	float m_fireTimer{ 0 };
	float m_collisionCooldown{ 0 };
	bool m_controlsDisabled = false;
	Vector2 m_lastVelocity{ 0, 0 };
public:
	CLASS_DECLARATION(PlayerComponent);
	CLASS_PROTOTYPE(PlayerComponent)

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);
	void OnCollisionExit(Actor* actor);
	void OnDeath();
};