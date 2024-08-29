#include "CameraComponent.h"

FACTORY_REGISTER(CameraComponent);

void CameraComponent::Initialize()
{
	//
}

void CameraComponent::Update(float dt)
{
	//
}

void CameraComponent::Read(const json_t& value)
{
	Component::Read(value);
}

void CameraComponent::Write(json_t& value)
{
	//
}