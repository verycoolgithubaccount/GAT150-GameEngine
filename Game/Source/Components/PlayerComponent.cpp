#include "PlayerComponent.h"
#include "Engine.h"

FACTORY_REGISTER(PlayerComponent)

void PlayerComponent::Initialize()
{
	m_owner->OnCollisionEnter = std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1);
}

void PlayerComponent::Update(float dt)
{
	Vector2 direction{ 0,0 };
	auto& input = m_owner->GetScene()->GetEngine()->GetInput();
	if (input.GetKeyDown(SDL_SCANCODE_A) || input.GetKeyDown(SDL_SCANCODE_LEFT)) direction.x = -1;
	if (input.GetKeyDown(SDL_SCANCODE_D) || input.GetKeyDown(SDL_SCANCODE_RIGHT)) direction.x = 1;
	if (input.GetKeyDown(SDL_SCANCODE_W) || input.GetKeyDown(SDL_SCANCODE_UP)) direction.y = -1;
	if (input.GetKeyDown(SDL_SCANCODE_S) || input.GetKeyDown(SDL_SCANCODE_DOWN)) direction.y = 1;
	m_owner->GetComponent<PhysicsComponent>()->ApplyForce(direction * m_speed);
}

void PlayerComponent::OnCollisionEnter(Actor* actor)
{
	std::cout << "player hit" << std::endl;
}

void PlayerComponent::Read(const json_t& value)
{
	READ_DATA_NAME(value, "speed", m_speed);
}

void PlayerComponent::Write(json_t& value)
{
	//
}