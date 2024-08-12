#pragma once
#include "Vector2.h"
#include "Core/Serializable.h"

struct Transform : public Serializable
{
	Vector2 translation;
	float rotation = 0;
	float scale = 1;

	Transform() = default;
	Transform(Vector2 position = {0, 0}, float rotation = 0, float scale = 1) :
		translation{ position },
		rotation{ rotation },
		scale{ scale }
	{}

	void Read(const json_t& value) override;
	void Write(json_t& value) override;
};