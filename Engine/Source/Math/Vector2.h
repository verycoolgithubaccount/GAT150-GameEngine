#pragma once
#include "MathUtils.h"
#include <cmath>
#include <iostream>

struct Vector2
{
	float x;
	float y;

	Vector2() = default;
	Vector2(float x, float y) { this->x = x; this->y = y; }
	Vector2(int x, int y) { this->x = (float)x; this->y = (float)y; }

	float operator [] (unsigned int index) const { return (&x)[index]; } // 0 is x, 1 will go forward to the next variable in memory, y
	float& operator [] (unsigned int index) { return (&x)[index]; } // same as above but lets you edit the values

	Vector2 operator + (const Vector2& v) const { return Vector2{ x + v.x, y + v.y }; };
	Vector2 operator - (const Vector2& v) const { return Vector2{ x - v.x, y - v.y }; };
	Vector2 operator * (const Vector2& v) const { return Vector2{ x * v.x, y * v.y }; };
	Vector2 operator / (const Vector2& v) const { return Vector2{ x / v.x, y / v.y }; };
	// output,  symbol,   input,                      operation              

	Vector2 operator + (float s) const { return Vector2{ x + s, y + s }; };
	Vector2 operator - (float s) const { return Vector2{ x - s, y - s }; };
	Vector2 operator * (float s) const { return Vector2{ x * s, y * s }; };
	Vector2 operator / (float s) const { return Vector2{ x / s, y / s }; };

	Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
	Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
	Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
	Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }

	Vector2& operator += (float s) { x += s; y += s; return *this; }
	Vector2& operator -= (float s) { x -= s; y -= s; return *this; }
	Vector2& operator *= (float s) { x *= s; y *= s; return *this; }
	Vector2& operator /= (float s) { x /= s; y /= s; return *this; }

	friend std::ostream& operator << (std::ostream& output, const Vector2& v)
	{
		output << "(" << v.x << ", " << v.y << ")";
		return output;
	}

	bool operator==(const Vector2& v) const {
		return (this->x == v.x && this->y == v.y);
	}

	bool isANumber() 
	{
		return (x == x && y == y);
	}

	// The point of having length and distance squared functions are so you don't need to do a square root operation
	// if you're just comparing distances to see which is larger

	float LengthSqr() const { return (x * x) + (y * y); }
	float Length() const { return Math::Sqrt((x * x) + (y * y)); }

	float DistanceSqr(const Vector2& other) const { return (other - *this).LengthSqr(); }
	float Distance(const Vector2& other) const { return (other - *this).Length(); }

	float Angle() const { return Math::Atan2(y, x); }

	Vector2 Rotate(float radians) const;

	Vector2 Normalized() const { return *this / Length(); } // Get unit vector, length of one with same angle
};

inline Vector2 Vector2::Rotate(float radians) const
{
	float x_ = x * cos(radians) - y * sin(radians);
	float y_ = x * sin(radians) + y * cos(radians);

	return { x_, y_ };
}