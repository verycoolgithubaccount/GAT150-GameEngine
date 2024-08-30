#include "PlayerComponent.h"
#include "Engine.h"

FACTORY_REGISTER(PlayerComponent);

void PlayerComponent::Initialize()
{
	m_owner->OnCollisionEnter = std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1);
	m_owner->OnCollisionExit = std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1);
}

void PlayerComponent::Update(float dt)
{
	auto engineAudio = m_owner->GetComponent<AudioComponent>("main_thruster");
	Vector2 direction = m_owner->GetTransform().GetForwardVector();
	float rotate = 0;
	float thrust = 0;
	auto& input = m_owner->GetScene()->GetEngine()->GetInput();
	if (!m_controlsDisabled && (input.GetKeyDown(SDL_SCANCODE_A) || input.GetKeyDown(SDL_SCANCODE_LEFT))) rotate = -0.3f;
	if (!m_controlsDisabled && (input.GetKeyDown(SDL_SCANCODE_D) || input.GetKeyDown(SDL_SCANCODE_RIGHT))) rotate = 0.3f;
	
	if (!m_controlsDisabled && (input.GetKeyDown(SDL_SCANCODE_W) || input.GetKeyDown(SDL_SCANCODE_UP)))
	{
		if (engineAudio && !engineAudio->IsPlaying()) engineAudio->Play();

		thrust = 0.5f;

		if (randomf() < 0.5)
		{
			const Transform& transform = m_owner->GetTransform();
			Particle::Data data
			{
				(transform.position - (Vector2{8.4f, 0 + randomf(-3, 3)} * transform.scale).Rotate(Math::DegToRad(transform.rotation))),
				m_owner->GetComponent<PhysicsComponent>()->GetVelocity() * 2.5 + (Vector2{-thrust * m_speed * 5, randomf(-10, 10)}).Rotate(Math::DegToRad(transform.rotation)),
				randomf(1, 3),
				Color{randomf(), randomf(0.8f, 1), 1},
				randomf(7.0f, 10.0f)
			};
			m_owner->GetScene()->GetEngine()->GetParticleSystem().AddParticle(data);
		}
	}
	else {
		if (engineAudio && engineAudio->IsPlaying()) engineAudio->Stop();
	}

	m_owner->GetComponent<PhysicsComponent>()->ApplyTorque(rotate * 90 * dt);
	m_owner->GetComponent<PhysicsComponent>()->ApplyForce(direction * thrust * m_speed);

	m_fireTimer -= dt;
	if (!m_controlsDisabled && input.GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <= 0)
	{
		m_fireTimer = 0.2f;

		auto rocket = Factory::Instance().Create<Actor>("player_rocket");
		rocket->SetPosition(m_owner->GetTransform().position + Vector2{ 60, 0 }.Rotate(Math::DegToRad(m_owner->GetTransform().rotation)));
		rocket->SetRotation(m_owner->GetTransform().rotation);
		rocket->SetLifeSpan(5);
		rocket->SetInitialVelocity(m_owner->GetComponent<PhysicsComponent>()->GetVelocity());

		m_owner->GetScene()->AddActor(std::move(rocket), true);
	}
}

void PlayerComponent::OnCollisionEnter(Actor* actor)
{
	m_lastVelocity = m_owner->GetComponent<PhysicsComponent>()->GetVelocity();
	if (actor->GetTag() == "enemy_rocket")
	{
		m_owner->GetScene()->GetEngine()->GetAudio().PlaySound("Sounds/boom.wav");

		m_health -= 1;
		EVENT_NOTIFY_DATA_NAME(DisplayUpdate, m_health, health);

		if (m_health <= 0 && !m_controlsDisabled) OnDeath();
	}
}

void PlayerComponent::OnCollisionExit(Actor* actor)
{
	if (actor->GetTag() == "enemy" || actor->GetTag() == "asteroid")
	{
		Vector2 changeInVelocity = m_lastVelocity - m_owner->GetComponent<PhysicsComponent>()->GetVelocity();

		if (changeInVelocity.Length() > 60) {
			m_owner->GetScene()->GetEngine()->GetAudio().PlaySound("Sounds/ship_collision.wav");
		}

		m_health -= (int)(changeInVelocity.Length() / 60);
		EVENT_NOTIFY_DATA_NAME(DisplayUpdate, m_health, health);

		if (m_health <= 0 && !m_controlsDisabled) OnDeath();
	}
}

void PlayerComponent::OnDeath()
{
	EVENT_NOTIFY(PlayerDead);
	for (int i = 0; i < 400; i++) // Explosion
	{
		Particle::Data data
		{
			m_owner->GetTransform().position,
			m_owner->GetComponent<PhysicsComponent>()->GetVelocity() + (randomOnUnitCircle() * randomf(0, 300)),
			randomf(0, 1),
			Color{ 1, randomf(), randomf(0.0f, 0.3f) },
			randomf(10.0f * m_owner->GetTransform().scale, 50.0f * m_owner->GetTransform().scale)
		};
		m_owner->GetScene()->GetEngine()->GetParticleSystem().AddParticle(data);
	}
	for (int i = 0; i < 100; i++) // Ring
	{
		Particle::Data data
		{
			m_owner->GetTransform().position,
			m_owner->GetComponent<PhysicsComponent>()->GetVelocity() + (randomOnUnitCircle() * 450),
			randomf(0, 1),
			Color{ 1, 1, 1 },
			randomf(2.8f * m_owner->GetTransform().scale, 3.8f * m_owner->GetTransform().scale)
		};
		m_owner->GetScene()->GetEngine()->GetParticleSystem().AddParticle(data);
	}
	m_owner->MakeDestroyed();
}

void PlayerComponent::Read(const json_t& value)
{
	Component::Read(value);
	READ_DATA_NAME(value, "speed", m_speed);
}

void PlayerComponent::Write(json_t& value)
{
	//
}