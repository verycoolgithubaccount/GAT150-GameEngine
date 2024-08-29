#pragma once
#include "Component.h"

class CameraComponent : public Component
{
public:
	CLASS_DECLARATION(CameraComponent);
	CLASS_PROTOTYPE(CameraComponent)

	void Initialize() override;
	void Update(float dt) override;
};