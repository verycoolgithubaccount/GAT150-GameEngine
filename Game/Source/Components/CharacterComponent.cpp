#include "CharacterComponent.h"
#include "Engine.h"

FACTORY_REGISTER(CharacterComponent)

void CharacterComponent::Initialize()
{
	m_owner->OnCollisionEnter = std::bind(&CharacterComponent::OnCollisionEnter, this, std::placeholders::_1);
	m_owner->OnCollisionExit = std::bind(&CharacterComponent::OnCollisionExit, this, std::placeholders::_1);

	physics = m_owner->GetComponent<PhysicsComponent>();
	animation = m_owner->GetComponent<TextureAnimationComponent>();
}

void CharacterComponent::Update(float dt)
{
	bool onGround = (m_groundCount > 0);

	Vector2 direction{ 0, 0 };
	auto& input = m_owner->GetScene()->GetEngine()->GetInput();
	if (input.GetKeyDown(SDL_SCANCODE_A) || input.GetKeyDown(SDL_SCANCODE_LEFT)) direction.x = -1;
	if (input.GetKeyDown(SDL_SCANCODE_D) || input.GetKeyDown(SDL_SCANCODE_RIGHT)) direction.x = 1;

	float modifier = (onGround) ? 1 : 0.6f;
	physics->ApplyForce(direction * m_speed * modifier);

	if ((input.GetKeyDown(SDL_SCANCODE_SPACE) || input.GetKeyDown(SDL_SCANCODE_UP)) && onGround)
	{
		physics->SetVelocity(physics->GetVelocity() + Vector2{ 0, (int) (-m_speed * 0.75f) });
	}

	if (physics->GetVelocity().x < -0.1f) animation->SetHFlip(true);
	else if (physics->GetVelocity().x > 0.1f) animation->SetHFlip(false);

	if (Math::Abs(physics->GetVelocity().x) > 0.1f) animation->SetAnimation("walk");
	else animation->SetAnimation("idle");
}

void CharacterComponent::OnCollisionEnter(Actor* actor)
{
	if (actor->GetTag() == "coin") m_owner->GetComponent<AudioComponent>()->Stop();
	//EVENT_NOTIFY(PlayerDead);
	if (actor->GetTag() == "ground") m_groundCount++;
}

void CharacterComponent::OnCollisionExit(Actor* actor)
{
	if (actor->GetTag() == "ground") m_groundCount--;
}

void CharacterComponent::Read(const json_t& value)
{
	READ_DATA_NAME(value, "speed", m_speed);
}

void CharacterComponent::Write(json_t& value)
{
	//
}