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
	Vector2 m_velocity{ 0, 0 };
	float m_damping{ 0 }; // drag, velocity reduction

	Scene* m_scene{ nullptr };

	std::vector<std::unique_ptr<Component>> m_components;
public:
	Actor() = default;
	Actor(const Transform& transform) : m_transform{ transform } {}

	CLASS_DECLARATION(Actor);

	void Initialize() override;

	const Transform& GetTransform() { return m_transform; }
	const Vector2& GetVelocity() { return m_velocity; }

	void SetTransform(const Transform& transform) { m_transform = transform; }

	virtual void Update(float dt);
	virtual void Draw(Renderer& renderer);

	void AddComponent(std::unique_ptr<Component> component);

	void SetDamping(float damping) { m_damping = damping; }
	void SetLifeSpan(float lifespan) { m_lifespan = lifespan; }

	void SetTag(const std::string& tag) { m_tag = tag; }
	const std::string& GetTag() { return m_tag; }

	//virtual void OnCollision(Actor* collider) = 0;
	//virtual void OnDeath() = 0;
	//float GetRadius(){ return (m_model) ? m_model->GetRadius(m_transform.scale) : 0; }

	//virtual void HitByRay(std::string rayTag) = 0;

	friend class Scene;
};