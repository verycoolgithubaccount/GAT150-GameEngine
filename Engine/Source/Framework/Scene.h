#pragma once
#include "Object.h"
#include "Renderer/Particle.h"
#include "Actor.h"
#include "Math/Vector2.h"
#include "Components/PhysicsComponent.h"
#include <list>
#include <vector>
#include <memory>
#include <cmath>

class Renderer;
class Audio;
class Game;
class Engine;

class Scene : public Object
{
protected:
	std::list<std::unique_ptr<Actor>> actors;
	std::vector<Particle> m_stars;

	Game* m_game{ nullptr };
	float m_musicTimer = 0;

	Engine* m_engine{ nullptr };

	Actor* m_camera{ nullptr };
public:
	CLASS_DECLARATION(Scene);
	CLASS_PROTOTYPE(Scene)

	Scene(Engine* engine, Game* game = nullptr) : m_engine{ engine }, m_game{ game } {}
	
	void Update(float dt, Renderer& renderer, Audio& audio);
	void Draw(Renderer& renderer);

	void AddActor(std::unique_ptr<Actor> actor, bool initialize);
	void RemoveAll();

	void AddStars(Renderer& renderer);

	bool HasStars() { return !m_stars.empty(); }

	template<typename T> T* GetActor();
	template<typename T> T* GetActor(const std::string& name);

	Actor* GetNearestActorWithComponent(const std::vector<std::string>& componentNames, const Vector2& position);
	const Vector2& GetCameraPosition() { return m_camera->GetTransform().position; }
	const Vector2& GetCameraVelocity() { return m_camera->GetComponent<PhysicsComponent>()->GetVelocity(); }

	bool CheckHitByRay(Vector2 originPosition, Vector2 position, std::string rayTag);

	Game* GetGame() { return m_game; }
	Engine* GetEngine() { return m_engine; }

	// Inherited via Object
	void Initialize() override;

	Scene(const Scene& other) { /* Can't copy scene */ }
};

template<typename T> // Template functions HAVE to be in the header
T* Scene::GetActor()
{
	for (auto& actor : actors)
	{
		T* result = dynamic_cast<T*>(actor.get()); // Cast to type T if possible
		if (result) return result;

		// Basically, what this does is when this function is called you need to specify the type you're looking for in <>,
		// and it searches through m_actors until it finds something of that type and returns it
	}

	return nullptr;
}

template<typename T>
inline T* Scene::GetActor(const std::string& name)
{
	for (auto& actor : actors)
	{
		T* result = dynamic_cast<T*>(actor.get()); // Cast to type T if possible
		if (result && IsEqualIgnoreCase(result->GetName(), name)) return result;

		// Basically, what this does is when this function is called you need to specify the type you're looking for in <>,
		// and it searches through m_actors until it finds something of that type and returns it
	}

	return nullptr;
}
