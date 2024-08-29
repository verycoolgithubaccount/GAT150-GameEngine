#include "ParticleSystem.h"

void ParticleSystem::Update(float dt, Renderer& renderer)
{
	for (auto& particle : m_particles)
	{
		if (particle.isActive) particle.Update(dt, renderer);
	}
}

void ParticleSystem::Draw(Renderer& renderer, const Vector2& modifier)
{
	for (auto& particle : m_particles)
	{
		if (particle.isActive) particle.Draw(renderer, modifier);
	}
}

void ParticleSystem::AddParticle(const Particle::Data& data)
{
	Particle* particle = GetFreeParticle();
	if (particle)
	{
		particle->Initialize(data);
	}
}

Particle* ParticleSystem::GetFreeParticle()
{
	// find the first inactive particle
	for (auto& particle : m_particles)
	{
		if (!particle.isActive) return &particle;
	}
	return nullptr;
}
 