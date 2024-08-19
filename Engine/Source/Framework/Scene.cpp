#include "Scene.h"
#include "Engine.h"
#include "Core/Factory.h"
#include "Components/CollisionComponent.h"
#include <algorithm>

void Scene::Initialize()
{
	for (auto& actor : actors)
	{
		actor->Initialize();
	}
}

void Scene::Update(float dt, Renderer& renderer, Audio& audio)
{
	for (Particle& star : m_stars)
	{
		star.Update(dt, renderer);

		star.position.x = Math::Wrap(star.position.x, (float)renderer.GetWidth());
		star.position.y = Math::Wrap(star.position.y, (float)renderer.GetHeight());
	}
	
	for (auto& actor : actors)
	{
		if (actor->isActive()) actor->Update(dt);
	}

	for (auto& actor1 : actors)
	{
		CollisionComponent* collision1 = actor1->GetComponent<CollisionComponent>();
		if (!collision1) continue;

		for (auto& actor2 : actors)
		{
			if (actor1 == actor2) continue;

			CollisionComponent* collision2 = actor2->GetComponent<CollisionComponent>();
			if (!collision2) continue;

			if (collision1->CheckCollision(collision2))
			{
				// If the function exists, call that function
				if (actor1->OnCollisionEnter) actor1->OnCollisionEnter(actor2.get());
				if (actor2->OnCollisionEnter) actor2->OnCollisionEnter(actor1.get());
			}
		}
	}

	m_musicTimer -= dt;
	if (m_musicTimer <= 0) {
	//	audio.PlaySound("music.wav");
		m_musicTimer = 275;
	}

	// destroy
	// Starting at begin until end, remove_if iterates through and adds actor to an array if it's destroyed, then erase deletes it
	std::erase_if(actors, [](auto& actor) { return actor->m_destroyed; }); // Same as above^
}

bool Scene::CheckHitByRay(Vector2 originPosition, Vector2 position, std::string rayTag)
{
	for (auto& actor : actors)
	{
		if (actor->m_destroyed || actor->GetTransform().position == originPosition) continue;

		//if ((actor->GetTransform().translation - position).Length() <= actor->GetRadius() * 0.6)
		//{
		//	actor->HitByRay(rayTag);
		//	return true;
		//}
	}
	return false;
}

void Scene::Draw(Renderer& renderer)
{
	for (Particle& star : m_stars)
	{
		bool canDraw = true;
		for (auto& actor : actors)
		{
			if (actor->GetTransform().position.Distance(star.position) < (8 * actor->GetTransform().scale)) {
				canDraw = false;
			}
		}
		if (canDraw) star.Draw(renderer);
	}

	for (auto& actor : actors)
	{
		if (actor->isActive()) actor->Draw(renderer);
	}
}

void Scene::AddActor(std::unique_ptr<Actor> actor)
{
	actor->m_scene = this;
	actors.push_back(std::move(actor)); //std::move is to delete the original unique_ptr and use it in the list instead
}

void Scene::RemoveAll()
{
	actors.clear();
}

void Scene::AddStars(Renderer& renderer)
{
	for (int i = 0; i < 400; i++)
	{
		float modifier = randomf();
		
		m_stars.push_back(Particle{
			Vector2{ randomf((float)renderer.GetWidth()), randomf((float)renderer.GetHeight()) },
			Vector2{ modifier * 10, 0.0f},
			-42.0f,
			Color{ (float)(0.5f * modifier * randomf(0.8f, 1.0f)), (float)(0.5f * modifier * randomf(0.8f, 1.0f)), (float)(0.5f * modifier * randomf(0.8f, 1.0f))},
			modifier * 0.3f
			});
	}
}

const Vector2 Scene::GetNearestEnemyPosition(Vector2 position)
{
	float distance = HUGE_VAL;
	for (auto& actor : actors)
	{
		if (actor->GetTag() == "Enemy" && distance > position.Distance(actor->GetTransform().position)) distance = position.Distance(actor->GetTransform().position);
	}

	if (distance == HUGE_VAL) return Vector2{ (float)HUGE_VAL, (float)HUGE_VAL };

	for (auto& actor : actors)
	{
		if (actor->GetTag() == "Enemy" && distance == position.Distance(actor->GetTransform().position)) return actor->GetTransform().position;
	}
	return Vector2{ (float)HUGE_VAL, (float)HUGE_VAL };
}

/*
const Vector2 Scene::GetNearestEnemyVelocity(Vector2 position)
{
	float distance = HUGE_VAL;
	for (auto& actor : m_actors)
	{
		if (actor->GetTag() == "Enemy" && distance > position.Distance(actor->GetTransform().position)) distance = position.Distance(actor->GetTransform().position);
	}

	if (distance == HUGE_VAL) return Vector2{ (float)HUGE_VAL, (float)HUGE_VAL };

	for (auto& actor : m_actors)
	{
		if (actor->GetTag() == "Enemy" && distance == position.Distance(actor->GetTransform().position)) return actor->GetVelocity();
	}
	return Vector2{ (float)HUGE_VAL, (float)HUGE_VAL };
}
*/

const Vector2 Scene::GetNearestAlliedPosition(Vector2 position)
{
	float distance = HUGE_VAL;
	for (auto& actor : actors)
	{
		if ((actor->GetTag() == "Player" || actor->GetTag() == "Ally") && distance > position.Distance(actor->GetTransform().position)) distance = position.Distance(actor->GetTransform().position);
	}

	if (distance == HUGE_VAL) return Vector2{ (float)HUGE_VAL, (float)HUGE_VAL };

	for (auto& actor : actors)
	{
		if ((actor->GetTag() == "Player" || actor->GetTag() == "Ally") && distance == position.Distance(actor->GetTransform().position)) return actor->GetTransform().position;
	}
	return Vector2{ (float)HUGE_VAL, (float)HUGE_VAL };
}


/*
const Vector2 Scene::GetNearestAlliedVelocity(Vector2 position)
{
	float distance = HUGE_VAL;
	for (auto& actor : m_actors)
	{
		if ((actor->GetTag() == "Player" || actor->GetTag() == "Ally") && distance > position.Distance(actor->GetTransform().position)) distance = position.Distance(actor->GetTransform().position);
	}

	if (distance == HUGE_VAL) return Vector2{ (float)HUGE_VAL, (float)HUGE_VAL };

	for (auto& actor : m_actors)
	{
		if ((actor->GetTag() == "Player" || actor->GetTag() == "Ally") && distance == position.Distance(actor->GetTransform().position)) return actor->GetVelocity();
	}
	return Vector2{ (float)HUGE_VAL, (float)HUGE_VAL };
}
*/


void Scene::Read(const json_t& value)
{
	if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray())
	{
		for (auto& actorValue : GET_DATA(value, actors).GetArray())
		{
			auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
			actor->Read(actorValue);

			AddActor(std::move(actor));
		}
	}
}

void Scene::Write(json_t& value)
{
	//
}