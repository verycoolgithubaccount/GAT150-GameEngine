#pragma once
#include "Components/Component.h"

class TextureAnimationComponent;
class PhysicsComponent;

class CharacterComponent : public Component
{
private:
	int m_groundCount{ 0 };
	float m_speed{ 0 };
public:
	CLASS_DECLARATION(CharacterComponent);
	CLASS_PROTOTYPE(CharacterComponent)

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);
	void OnCollisionExit(Actor* actor);

	PhysicsComponent* physics{ nullptr };
	TextureAnimationComponent* animation{ nullptr };
};