#pragma once
#include "Vector2.h"

struct Transform
{
	Vector2 translation{0, 0};
	float rotation{ 0.0f };
	float scale{ 0.0f };

	Transform() = default;
	Transform(Vector2 position = { 0, 0 }, float rotation = 0, float scale = 1) :
		translation{ position },
		rotation{ rotation },
		scale{ scale }
	{}
};