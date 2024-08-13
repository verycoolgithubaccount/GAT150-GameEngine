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

	virtual void Update(float dt);
	virtual void Draw(Renderer& renderer);

	void AddComponent(std::unique_ptr<Component> component);

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