#include "PlayerComponent.h"
#include "Engine.h"

FACTORY_REGISTER(PlayerComponent)

void PlayerComponent::Initialize()
{
	m_owner->OnCollisionEnter = std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1);
}

void PlayerComponent::Update(float dt)
{
	float rotate = 0;
	float thrust = 0;
	auto& input = m_owner->GetScene()->GetEngine()->GetInput();
	if (input.GetKeyDown(SDL_SCANCODE_A) || input.GetKeyDown(SDL_SCANCODE_LEFT)) rotate = -0.3;
	if (input.GetKeyDown(SDL_SCANCODE_D) || input.GetKeyDown(SDL_SCANCODE_RIGHT)) rotate = 0.3;
	if (input.GetKeyDown(SDL_SCANCODE_W) || input.GetKeyDown(SDL_SCANCODE_UP)) thrust = 0.5;
	//if (input.GetKeyDown(SDL_SCANCODE_S) || input.GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -0.5;

	Vector2 direction = m_owner->GetTransform().GetForwardVector();

	m_owner->GetComponent<PhysicsComponent>()->ApplyTorque(rotate * 90 * dt);
	m_owner->GetComponent<PhysicsComponent>()->ApplyForce(direction * thrust * m_speed);

	if (input.GetKeyDown(SDL_SCANCODE_SPACE)) 
	{
		auto rocket = Factory::Instance().Create<Actor>("rocket");
		rocket->SetPosition(m_owner->GetTransform().position + Vector2{ 60, 0 }.Rotate(Math::DegToRad(m_owner->GetTransform().rotation)));
		rocket->SetRotation(m_owner->GetTransform().rotation);

		m_owner->GetScene()->AddActor(std::move(rocket), true);
	}
}

void PlayerComponent::OnCollisionEnter(Actor* actor)
{
	//std::cout << "player hit" << std::endl;
	EVENT_NOTIFY(PlayerDead);
}

void PlayerComponent::Read(const json_t& value)
{
	READ_DATA_NAME(value, "speed", m_speed);
}

void PlayerComponent::Write(json_t& value)
{
	//
}