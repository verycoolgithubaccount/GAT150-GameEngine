#pragma once
#include "Vector2.h"
#include "Core/Serializable.h"
#include <iostream>

struct Transform : public Serializable
{
	Vector2 position;
	float rotation = 0;
	float scale = 1;

	Transform() = default;
	Transform(Vector2 position = {0, 0}, float rotation = 0, float scale = 1) :
		position{ position },
		rotation{ rotation },
		scale{ scale }
	{}

	void Read(const json_t& value) override;
	void Write(json_t& value) override;

	Vector2 GetForwardVector() const { return Vector2{ 1, 0 }.Rotate(Math::DegToRad(rotation)); } // Forward facing direction

	friend std::ostream& operator << (std::ostream& output, const Transform& t)
	{
		output << "Position: " << t.position << ", Rotation: " << t.rotation << ", Scale: " << t.scale;
		return output;
	}
};