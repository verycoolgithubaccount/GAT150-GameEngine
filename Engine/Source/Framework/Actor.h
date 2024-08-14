#pragma once
#include "Object.h"
#include "../Math/Transform.h"
#include "../Renderer/Particle.h"
#include "Components/Component.h"

#include <vector>
#include <string>
#include <memory>

class Renderer;
class Scene;

class Actor : public Object
{
protected:
	std::string m_tag;
	bool m_destroyed = false;
	float m_lifespan = 0;
	float m_collisionCooldown = 0;

	Transform m_transform{ {0,0}, 0.0f, 0.0f };

	Scene* m_scene{ nullptr };

	std::vector<std::unique_ptr<Component>> m_components;
public:
	Actor() = default;
	Actor(const Transform& transform) : m_transform{ transform } {}

	CLASS_DECLARATION(Actor);

	void Initialize() override;

	const Transform& GetTransform() { return m_transform; }

	void SetTransform(const Transform& transform) { m_transform = transform; }
	void SetPosition(const Vector2& position) { m_transform.position = position; }

	virtual void Update(float dt);
	virtual void Draw(Renderer& renderer);

	void AddComponent(std::unique_ptr<Component> component);

	template<typename T>
	T* GetComponent();

	template<typename T>
	std::vector<T*> GetComponents();

	void SetLifeSpan(float lifespan) { m_lifespan = lifespan; }

	void SetTag(const std::string& tag) { m_tag = tag; }
	const std::string& GetTag() { return m_tag; }

	//virtual void OnDeath() = 0;

	//virtual void HitByRay(std::string rayTag) = 0;

	const bool GetDestroyed() const { return m_destroyed; }
	void MakeDestroyed() { m_destroyed = true; }

	Scene* GetScene() { return m_scene; }

	friend class Scene;
};

template<typename T>
inline T* Actor::GetComponent()
{
	for (auto& component : m_components)
	{
		T* result = dynamic_cast<T*>(component.get()); // Cast to type T if possible
		if (result) return result;

		// Basically, what this does is when this function is called you need to specify the type you're looking for in <>,
		// and it searches through m_actors until it finds something of that type and returns it
	}
	return nullptr;
}

template<typename T>
inline std::vector<T*> Actor::GetComponents()
{
	std::vector<T*> results;
	for (auto& component : m_components)
	{
		T* result = dynamic_cast<T*>(component.get());
		if (result) results.push_back(result);
	}
	return results;
}
