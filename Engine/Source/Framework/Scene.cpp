#include "Scene.h"
#include "Engine.h"
#include "Core/Factory.h"
#include "Components/CollisionComponent.h"
#include "Components/CameraComponent.h"
#include <algorithm>

void Scene::Initialize()
{
	for (auto& actor : actors)
	{
		actor->Initialize();
		if (actor->GetComponent<CameraComponent>()) m_camera = actor.get();
	}
}

void Scene::Update(float dt, Renderer& renderer, Audio& audio)
{
	if (m_stars.empty()) AddStars(renderer);

	for (Particle& star : m_stars)
	{
		star.Update(dt, renderer);

		star.position.x = Math::Wrap(star.position.x, (float)renderer.GetWidth());
		star.position.y = Math::Wrap(star.position.y, (float)renderer.GetHeight());
	}
	
	for (auto& actor : actors)
	{
		if (actor->IsActive()) actor->Update(dt);
	}

	if (m_camera != nullptr && !m_camera->IsDestroyed() && m_camera->IsActive()) renderer.SetCameraOffset(Vector2{ renderer.GetWidth()/2, renderer.GetHeight()/2 } - m_camera->GetTransform().position);


	// destroy
	// Starting at begin until end, remove_if iterates through and adds actor to an array if it's destroyed, then erase deletes it
	std::erase_if(actors, [](auto& actor) { return actor->m_destroyed; }); // Same as above^
}

Actor* Scene::GetNearestActorWithComponent(const std::vector<std::string>& componentNames, const Vector2& checkingPosition)
{
	std::vector<Actor*> fittingActors;
	for (auto& actor : actors)
	{
		for (auto& componentName : componentNames)
		{
			if (actor->HasComponent(componentName))
			{
				fittingActors.push_back(actor.get());
				break;
			}
		}
	}

	if (fittingActors.empty()) return nullptr;

	int currentClosest = 0;
	for (int i = 1; i < fittingActors.size(); i++)
	{
		if (checkingPosition.Distance(fittingActors[currentClosest]->GetTransform().position) > checkingPosition.Distance(fittingActors[i]->GetTransform().position)) currentClosest = i;
	}

	return fittingActors[currentClosest];
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
		if (m_camera && m_camera->GetComponent<PhysicsComponent>())
		{
			star.velocity = (m_camera->GetComponent<PhysicsComponent>()->GetVelocity() / -10.0f) * (star.size / 0.5f);
		}

		star.Draw(renderer);
	}

	for (auto& actor : actors)
	{
		// Check that the actor is in bounds before drawing
		if (actor->IsActive() &&
			(actor->GetTransform().position + renderer.GetCameraOffset()).x < (renderer.GetWidth() * 1.3) &&
			(actor->GetTransform().position + renderer.GetCameraOffset()).x > 0 - (renderer.GetWidth() * 0.3) &&
			(actor->GetTransform().position + renderer.GetCameraOffset()).y < (renderer.GetHeight() * 1.3) &&
			(actor->GetTransform().position + renderer.GetCameraOffset()).y > 0 - (renderer.GetHeight() * 0.3))
		{
			actor->Draw(renderer, renderer.GetCameraOffset());
		}
	}
}

void Scene::AddActor(std::unique_ptr<Actor> actor, bool initialize)
{
	actor->SetScene(this);
	if (initialize) actor->Initialize();

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

void Scene::Read(const json_t& value)
{
	if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray())
	{
		for (auto& actorValue : GET_DATA(value, actors).GetArray())
		{
			auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
			actor->Read(actorValue);

			bool prototype = false;
			if (READ_DATA(actorValue, prototype))
			{
				std::string name = actor->m_name;
				Factory::Instance().RegisterPrototype(name, std::move(actor));
			}
			else {
				AddActor(std::move(actor), false);
			}
		}
	}
}

void Scene::Write(json_t& value)
{
	//
}