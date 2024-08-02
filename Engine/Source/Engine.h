#pragma once

// ** core **
#include "Core/ETime.h"
#include "Core/EAssert.h"
#include "Core/EFile.h"

// ** systems **
// renderer
#include "Renderer/Renderer.h"
#include "Renderer/Particle.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Model.h"
#include "Renderer/Texture.h"
//input
#include "Input/Input.h"
//audio
#include "Audio/Audio.h"

// ** math **
#include "Math/Vector2.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"

#include <fmod.hpp>
#include <SDL.h>
#include <memory>

class Engine
{
private:
	bool quit{ false };

	// unique_ptr<Renderer> m_renderer instead of Renderer* m_renderer{nullptr}, it's a regular pointer but it's automatically deleted when out of scope, 
	// better than new/delete
	std::unique_ptr<Renderer> m_renderer;
	std::unique_ptr<Input> m_input;
	std::unique_ptr<Audio> m_audio;
		 
	std::unique_ptr<Time> m_time;

	std::unique_ptr<ParticleSystem> m_particleSystem;

public:

	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }

	ParticleSystem& GetParticleSystem() { return *m_particleSystem; }
	Time& GetTime() { return *m_time; }

	bool GameQuit() { return quit; }
};

