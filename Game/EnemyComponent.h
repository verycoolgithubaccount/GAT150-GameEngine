#pragma once
#include "Components/Component.h"

class EnemyComponent : public Component
{
public:
	enum class MovementState : char
	{
		SENTRY = 0,
		FOLLOWING,
		TRAVELLING,
		DEAD
	};
private:
	MovementState m_movementState{ MovementState::TRAVELLING };
	Vector2 m_lastTargetVelocity{ 0, 0 };
	float m_lastRotationAngle{ 0 };
	float m_speed{ 0 };
	float m_rotationSpeed = 0.03f;
	float m_degreesPerSecond = 0;
	float m_fireTimer = 0;
	float m_deathTimer = 0;
	int m_health = 3;
	bool lastDamagedByPlayer = false;
public:
	CLASS_DECLARATION(EnemyComponent);
	CLASS_PROTOTYPE(EnemyComponent);

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);

	void FireStarboardThruster(float dt);
	void FirePortThruster(float dt);
	void FireMainThruster(float dt);

	void Rotate(Vector2 directionToTarget, float rotationGoal, float dt);

	void OnDeath();
};