#include "PhysicsComponent.h"

void PhysicsComponent::Read(const json_t& value)
{
	READ_DATA_NAME(value, "velocity", m_velocity);
	READ_DATA_NAME(value, "acceleration", m_acceleration);
	READ_DATA_NAME(value, "mass", m_mass);
	READ_DATA_NAME(value, "damping", m_damping);
}

void PhysicsComponent::Write(json_t& value)
{
}
