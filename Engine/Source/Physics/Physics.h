#pragma once
#include "Math/Vector2.h"
#include <box2d/box2d.h>
#include <memory>

#define PIXELS_PER_UNIT	48.0f

inline b2Vec2  ConvertVec2(const Vector2& v) { return { v.x, v.y }; }
inline Vector2 ConvertVec2(const b2Vec2& v)  { return { v.x, v.y }; }

class Physics
{
public:
	Physics() = default;

	bool Initialize();
	void Shutdown();

	void Update(float dt);
	void UpdateCollision();

	static Vector2 WorldToScreen(const Vector2& world)	{ return world * PIXELS_PER_UNIT; }
	static Vector2 ScreenToWorld(const Vector2& screen) { return screen * (1.0f / PIXELS_PER_UNIT); }
	
	friend class RigidBody;

private:
	b2WorldId m_worldId;
};
