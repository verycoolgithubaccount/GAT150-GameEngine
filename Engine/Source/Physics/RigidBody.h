#pragma once
#include "Math/Transform.h"
#include <box2d/box2d.h>

class RigidBody
{
public:
	enum class Shape // "enum class" makes it scoped, which is better so you have to use the enum name and theres less confusion
	{
		BOX,
		CAPSULE,
		CIRCLE,
		CHAIN
	};

	struct def_t
	{
		// body
		float gravityScale = 1;
		float damping = 0.2f;
		float angularDamping = 0.2f;
		bool  constrainAngle = false;
		bool  isDynamic = true;

		// shape
		float friction = 0.3f;
		float restitution = 0.5f;
		float density = 1.0f;
		bool isSensor = false; // if it doesn't have collisions

		Shape shape = Shape::BOX;

		class Actor* actor{ nullptr };
	};

public:
	RigidBody(const Transform& transform, const Vector2& size, const def_t& def, const class Physics& physics);
	~RigidBody();

	void SetTransform(const Vector2& position, float rotation);
	Vector2 GetPosition();

	float GetAngle();

	void ApplyForce(const Vector2& force);
	void SetVelocity(const Vector2& velocity);
	Vector2 GetVelocity();

	void ApplyTorque(float torque);
	void SetAngularVelocity(float velocity);

private:
	b2BodyId m_bodyId{ b2_nullBodyId };
};