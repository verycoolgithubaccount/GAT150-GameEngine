#pragma once
#include "Components/Component.h"

class BulletComponent : public Component
{
private:
	float m_speed{ 0 };
public:
	CLASS_DECLARATION(BulletComponent);
	CLASS_PROTOTYPE(BulletComponent)

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);
};