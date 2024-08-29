#pragma once
#include "Component.h"

class RenderComponent : public Component
{
public:
	virtual void Draw(class Renderer& renderer, const Vector2& modifier = { 0, 0 }) = 0;
};