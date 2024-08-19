#pragma once
#include "Components/Component.h"

class PlayerComponent : public Component
{
private:
	float m_speed{ 0 };
public:
	CLASS_DECLARATION(PlayerComponent);

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);
};