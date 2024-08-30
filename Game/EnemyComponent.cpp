#include "EnemyComponent.h"
#include "Engine.h"

FACTORY_REGISTER(EnemyComponent);

void EnemyComponent::Initialize()
{
	m_owner->OnCollisionEnter = std::bind(&EnemyComponent::OnCollisionEnter, this, std::placeholders::_1);
	m_owner->OnCollisionExit = std::bind(&EnemyComponent::OnCollisionExit, this, std::placeholders::_1);
	m_owner->GetComponent<PhysicsComponent>()->SetVelocity(m_owner->GetInitialVelocity());
	Actor* target = m_owner->GetScene()->GetNearestActorWithComponent({ "PlayerComponent" }, m_owner->GetTransform().position);
	Vector2 directionToTarget = target->GetTransform().position - m_owner->GetTransform().position;
	m_owner->SetRotation(directionToTarget.Angle());
}

void EnemyComponent::Update(float dt)
{
	
	if (m_health <= 0 && m_movementState != MovementState::DEAD) {
		m_deathTimer = 3;
		m_movementState = MovementState::DEAD;
	}

	if (m_movementState == MovementState::DEAD)
	{
		const Transform& transform = m_owner->GetTransform();
		if (randomf() > 0.983f) {
			Vector2 direction = Vector2{ randomf(-1, 1), randomf(-1, 1) }.Normalized();
			for (int i = 0; i < 50; i++)
			{
				Particle::Data data
				{
					transform.position + ((direction * 4 * transform.scale) + randomf(0, 3)),
					m_owner->GetComponent<PhysicsComponent>()->GetVelocity() + (direction * random(0, 200)) + randomf(0, 10),
					randomf(0, 1),
					Color{ 1, randomf(), randomf(0.0f, 0.3f) },
					randomf(2.8f * transform.scale, 3.8f * transform.scale)
				};
				m_owner->GetScene()->GetEngine()->GetParticleSystem().AddParticle(data);
			}
		}

		m_deathTimer -= dt;
		if (m_deathTimer <= 0) {
			OnDeath();
		}
	}
	else {
		Actor* target = m_owner->GetScene()->GetNearestActorWithComponent({"PlayerComponent"}, m_owner->GetTransform().position);

		if (target != nullptr)
		{
			Vector2 directionToTarget = target->GetTransform().position - m_owner->GetTransform().position;
			Vector2 targetVelocity = target->GetComponent<PhysicsComponent>()->GetVelocity();
			Vector2 ownerVelocity = m_owner->GetComponent<PhysicsComponent>()->GetVelocity();

			float rotationDifference = Math::RadToDeg(directionToTarget.Angle()) - m_owner->GetTransform().rotation;

			switch (m_movementState) {
			case MovementState::SENTRY:
				if (!(m_lastTargetVelocity == target->GetComponent<PhysicsComponent>()->GetVelocity())) m_movementState = MovementState::FOLLOWING;
				else Rotate(directionToTarget, rotationDifference, dt);
				break;
			case MovementState::TRAVELLING: {
				bool willOvershoot = false;
				float stepsUntilRotationGoal = (Math::Abs((Vector2{ 0, 0 } - directionToTarget).Angle() / (Math::DegToRad(m_degreesPerSecond)))) * dt;
				float stepsUntilPositionGoal = ((target->GetTransform().position.Distance(m_owner->GetTransform().position)) / (Math::Abs((targetVelocity - ownerVelocity).Length())));

				if (m_speed * stepsUntilPositionGoal <= Math::Abs((targetVelocity - ownerVelocity).Length())) willOvershoot = true;

				if (target->GetTransform().position.Distance(m_owner->GetTransform().position) < 100) {
					
					//m_movementState = MovementState::FOLLOWING;
				}
				else {
					if (Math::Abs(directionToTarget.Angle() - m_owner->GetTransform().rotation) > 0.1f)
					{

						Rotate(directionToTarget, rotationDifference, dt);
					}
					if (Math::Abs(Math::RadToDeg(directionToTarget.Angle()) - m_owner->GetTransform().rotation) < 10) FireMainThruster(dt);
				}
				break;
			}
			case MovementState::FOLLOWING: {
				Vector2 playerVelocity = targetVelocity;
				Vector2 velocityDiff = targetVelocity - ownerVelocity;

				if (Math::Abs(velocityDiff.x) < m_speed + 0.5 && Math::Abs(velocityDiff.y) < m_speed + 0.5)
				{
					m_lastTargetVelocity = playerVelocity;
					m_movementState = MovementState::SENTRY;
				}
				else if (Math::Abs(velocityDiff.Angle() - m_owner->GetTransform().rotation) > 0.1f)
				{
					Rotate(velocityDiff, velocityDiff.Angle() - m_owner->GetTransform().rotation, dt);
				}
				else {
					FireMainThruster(dt);
				}
				break;
			}
			default:
				break;
			}

			m_fireTimer -= dt;
			if (Math::Abs(rotationDifference) < 10 && m_fireTimer <= 0)
			{
				m_fireTimer = 0.5;
				// actor
				auto rocket = Factory::Instance().Create<Actor>("enemy_rocket");
				rocket->SetPosition(m_owner->GetTransform().position + Vector2{ 60, 0 }.Rotate(Math::DegToRad(m_owner->GetTransform().rotation)));
				rocket->SetRotation(m_owner->GetTransform().rotation);
				rocket->SetLifeSpan(5);
				rocket->SetInitialVelocity(m_owner->GetComponent<PhysicsComponent>()->GetVelocity());

				m_owner->GetScene()->AddActor(std::move(rocket), true);
			}
		}
	}
	m_lastRotationAngle = m_owner->GetTransform().rotation;
}


void EnemyComponent::OnCollisionEnter(Actor* actor)
{
	std::cout << "hi" << std::endl;
	m_lastVelocity = m_owner->GetComponent<PhysicsComponent>()->GetVelocity();
	if (actor->GetTag() == "player_rocket")
	{
		m_health -= 1;
		std::cout << m_health << std::endl;

		if (m_health <= 0) OnDeath();
	}
}

void EnemyComponent::OnCollisionExit(Actor* actor)
{
	std::cout << "hi" << std::endl;
	if (actor->GetTag() == "player" || actor->GetTag() == "ally")
	{
		Vector2 changeInVelocity = m_lastVelocity - m_owner->GetComponent<PhysicsComponent>()->GetVelocity();

		m_health -= (int)(changeInVelocity.Length() / 60);
		std::cout << m_health << std::endl;

		if (m_health <= 0) OnDeath();
	}
}

void EnemyComponent::FireStarboardThruster(float dt)
{
	m_owner->GetComponent<PhysicsComponent>()->ApplyTorque(-0.3 * 90 * dt);
}

void EnemyComponent::FirePortThruster(float dt)
{
	m_owner->GetComponent<PhysicsComponent>()->ApplyTorque(0.3 * 90 * dt);
}

void EnemyComponent::FireMainThruster(float dt)
{
	m_owner->GetComponent<PhysicsComponent>()->ApplyForce(m_owner->GetTransform().GetForwardVector() * m_speed);
	float thrust = 0.5f;

	if (randomf() < 0.5)
	{
		const Transform& transform = m_owner->GetTransform();
		Particle::Data data
		{
			(transform.position - (Vector2{8.4f, 0 + randomf(-3, 3)} *transform.scale).Rotate(Math::DegToRad(transform.rotation))),
			m_owner->GetComponent<PhysicsComponent>()->GetVelocity() * 3 + (Vector2{-thrust * m_speed * 5, randomf(-10, 10)}).Rotate(Math::DegToRad(transform.rotation)),
			randomf(1, 3),
			Color{randomf(), randomf(0.8f, 1), 1},
			randomf(7.0f, 10.0f)
		};
		m_owner->GetScene()->GetEngine()->GetParticleSystem().AddParticle(data);
	}
}

void EnemyComponent::Rotate(Vector2 directionToTarget, float rotationGoal, float dt)
{
	float stepsUntilRotationGoal = 0;
	bool willOvershoot = false;

	m_degreesPerSecond = (m_owner->GetTransform().rotation - m_lastRotationAngle) / dt;

	if (m_degreesPerSecond != 0)
	{
		stepsUntilRotationGoal = Math::Abs((rotationGoal / (Math::DegToRad(m_degreesPerSecond) * dt)));
		if (m_rotationSpeed * stepsUntilRotationGoal <= Math::Abs(m_degreesPerSecond)) willOvershoot = true;
	}
	if (Math::Abs(rotationGoal) > 0.1 && !willOvershoot)
	{
		if (directionToTarget.Angle() < Math::DegToRad(m_owner->GetTransform().rotation))
		{
			FireStarboardThruster(dt);
		}
		else
		{
			FirePortThruster(dt);
		}
	}
	else if (willOvershoot)
	{
		if (m_degreesPerSecond > 0) {
			FireStarboardThruster(dt);
		}
		else
		{
			FirePortThruster(dt);
		}
	}
}


void EnemyComponent::OnDeath()
{
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

void EnemyComponent::Read(const json_t& value)
{
	Component::Read(value);
	READ_DATA_NAME(value, "speed", m_speed);
}

void EnemyComponent::Write(json_t& value)
{
	//
}
