#pragma once
#include "Object.h"
#include "../Math/Transform.h"
#include "../Renderer/Particle.h"
#include "Components/Component.h"

#include <vector>
#include <string>
#include <memory>
#include <functional>

class Renderer;
class Scene;

class Actor : public Object
{
protected:
	std::string m_tag;
	bool m_destroyed = false;
	float m_lifespan = 0;
	float m_collisionCooldown = 0;
	bool m_useCameraOffset = true;

	Vector2 m_initialVelocity{ 0, 0 };
	Transform m_transform{ {0,0}, 0.0f, 0.0f };

	Scene* m_scene{ nullptr };

	std::vector<std::unique_ptr<Component>> m_components;
public:
	Actor() = default;
	Actor(const Transform& transform) : m_transform{ transform } {}

	CLASS_DECLARATION(Actor);
	CLASS_PROTOTYPE(Actor)

	void Initialize() override;

	const Transform& GetTransform() { return m_transform; }

	void SetTransform(const Transform& transform) { m_transform = transform; }
	void SetPosition(const Vector2& position) { m_transform.position = position; }
	void SetRotation(float rotation) { m_transform.rotation = rotation; }

	void SetInitialVelocity(const Vector2 initialVelocity) { m_initialVelocity = initialVelocity; }
	const Vector2& GetInitialVelocity() { return m_initialVelocity; }

	virtual void Update(float dt);
	virtual void Draw(Renderer& renderer, const Vector2& modifier = Vector2{ 0, 0 });

	//void return type, passing in Actor*
	std::function<void(Actor*)> OnCollisionEnter;
	std::function<void(Actor*)> OnCollisionExit;

	void AddComponent(std::unique_ptr<Component> component);

	bool HasComponent(std::string componentName);

	template<typename T>
	T* GetComponent();

	template<typename T>
	T* GetComponent(const std::string& name);

	template<typename T>
	std::vector<T*> GetComponents();

	void SetLifeSpan(float lifespan) { m_lifespan = lifespan; }

	void SetTag(const std::string& tag) { m_tag = tag; }
	const std::string& GetTag() { return m_tag; }

	//virtual void OnDeath() = 0;

	//virtual void HitByRay(std::string rayTag) = 0;

	const bool IsDestroyed() const { return m_destroyed; }
	void MakeDestroyed() { m_destroyed = true; }

	Scene* GetScene() { return m_scene; }
	void SetScene(Scene* scene) { m_scene = scene; }

	friend class Scene;

	void Rotate(float rotationAmount) { m_transform.rotation += rotationAmount; }

	Actor(const Actor& other);
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
inline T* Actor::GetComponent(const std::string& name)
{
	for (auto& component : m_components)
	{
		T* result = dynamic_cast<T*>(component.get()); // Cast to type T if possible
		if (result && IsEqualIgnoreCase(name, result->GetName())) return result;

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
