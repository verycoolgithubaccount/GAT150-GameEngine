  #include "Actor.h"
#include "../Engine.h"
#include "Core/Factory.h"
#include "Components/RenderComponent.h"

#include <iostream>

FACTORY_REGISTER(Actor)

void Actor::Initialize()
{
	for (auto& component : m_components)
	{
		component->Initialize();
	}
}

void Actor::Update(float dt)
{
	m_collisionCooldown -= dt;
	// Check for lifespan
	if (m_lifespan != 0)
	{
		m_lifespan -= dt;
		if (m_lifespan <= 0)
		{
			m_destroyed = true;
		}
	}

	for (auto& component : m_components)
	{
		component->Update(dt);
	}
}

void Actor::Draw(Renderer& renderer, const Vector2& modifier)
{
	if (m_destroyed) return;

	for (auto& component : m_components)
	{
		RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component.get());
		if (renderComponent) (m_useCameraOffset) ? renderComponent->Draw(renderer, modifier) : renderComponent->Draw(renderer);
	}
}

void Actor::AddComponent(std::unique_ptr<Component> component)
{
	component->m_owner = this;
	m_components.push_back(std::move(component));
}

bool Actor::HasComponent(std::string componentName)
{
	for (auto& component : m_components)
	{
		if (IsEqualIgnoreCase(component->GetComponentType(), componentName)) return true;
	}
	return false;
}

void Actor::Read(const json_t& value)
{
	Object::Read(value);

	Json::Read(value, "tag", m_tag);
	Json::Read(value, "lifespan", m_lifespan);

	READ_DATA_NAME(value, "initialVelocity", m_initialVelocity);
	READ_DATA_NAME(value, "useCameraOffset", m_useCameraOffset);
	// read transform
	if (HAS_DATA(value, transform)) m_transform.Read(GET_DATA(value, transform));

	// read components
	if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray())
	{
		for (auto& componentValue : GET_DATA(value, components).GetArray())
		{
			std::string type;
			READ_DATA(componentValue, type);

			auto component = Factory::Instance().Create<Component>(type);

			if (!component)// unique_ptrs overload bool return type, false if they are empty
			{
				std::cerr << "Could not create component: " << type << std::endl;
				continue; 
			}

			component->Read(componentValue);

			AddComponent(std::move(component));
		}
	}
}

void Actor::Write(json_t& value)
{
	//
}

Actor::Actor(const Actor& other)
{
	m_name = other.m_name;
	m_tag = other.m_tag;
	m_lifespan = other.m_lifespan;
	m_transform = other.m_transform;
	m_collisionCooldown = other.m_collisionCooldown;
	m_initialVelocity = other.m_initialVelocity;
	m_useCameraOffset = other.m_useCameraOffset;

	for (auto& component : other.m_components)
	{
		auto cloneComponent = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
		AddComponent(std::move(cloneComponent));
	}
}