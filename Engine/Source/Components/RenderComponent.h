#pragma once
#include "Component.h"

class RenderComponent : public Component
{
public:
	virtual void Draw(class Renderer& renderer) = 0;
};