#pragma once
#include "Vector2.h"

struct Rect
{
	int x, y, w, h = 0;

	Rect() = default;
	Rect(int x, int y, int w, int h) : x{ x }, y{ y }, w{ w }, h{ h } {}
	Rect(const Vector2& dim, const Vector2& scale) : x{ (int) dim.x }, y{ (int) dim.y }, w{ (int) scale.x }, h{ (int) scale.y } {}
};