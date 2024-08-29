#pragma once
#include "../Math/Vector2.h"
#include "Color.h"
#include "Renderer.h"
#include "../Math/Transform.h"
#include <vector>

class Model
{
private:
	std::vector<Vector2> m_points;
	Color m_color;
public:
	Model() = default;
	Model(const std::vector<Vector2>& points, const Color& color) :
		m_points{ points },
		m_color{ color }
	{}

	void Draw(Renderer& renderer, const Vector2& position, float angle, float scale, const Vector2& modifier = { 0, 0 });
	void Draw(Renderer& renderer, const Transform& transform, const Vector2& modifier = { 0, 0 });

	float GetRadius(float scale);
};