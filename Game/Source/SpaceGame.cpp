#include "SpaceGame.h"
#include "Engine.h"

#include <memory>

bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<Scene>(m_engine);

	std::string sceneNames[] = { "scenes/space_tilemap.json", "scenes/scene.json", "scenes/menu.json" };
	for (auto& sceneName : sceneNames)
	{
		// read json
		rapidjson::Document document;
		Json::Load(sceneName, document);
		m_scene->Read(document);
	}

	m_restartTimer = 5;
	m_scene->Initialize();

	ADD_OBSERVER(PlayerDead, SpaceGame::OnPlayerDead);
	ADD_OBSERVER(ScoreIncrease, SpaceGame::OnScoreIncrease);

	return true;
}

void SpaceGame::Shutdown()
{
	m_scene->RemoveAll();
}

void SpaceGame::Update(float dt)
{
	if (m_state == State::GAME)
	{
		if (m_spawnTimer < 0)
		{
			m_spawnTimer = 5;
			if (randomf() > 0.6)
			{
				auto enemy = Factory::Instance().Create<Actor>("enemy");
				enemy->SetPosition(m_scene->GetCameraPosition() + (randomOnUnitCircle() * (m_engine->GetRenderer().GetWidth() / 1.8)));
				enemy->SetInitialVelocity(m_scene->GetCameraVelocity());
				m_scene->AddActor(std::move(enemy), true);
			}
			else 
			{
				auto asteroid = Factory::Instance().Create<Actor>("asteroid");
				Vector2 asteroidPosition = m_scene->GetCameraPosition() + (randomOnUnitCircle() * (m_engine->GetRenderer().GetWidth() / 2));
				asteroid->SetPosition(asteroidPosition);
				asteroid->SetInitialVelocity((m_scene->GetCameraVelocity() + asteroidPosition - m_scene->GetCameraPosition()).Normalized() * random(100, 1000));
				m_scene->AddActor(std::move(asteroid), true);
			}
			

		}
	}
	else
	{
		if (m_restartTimer > 0) m_restartTimer -= dt;
		else
		{
			m_scene->RemoveAll();
			m_scene.release();
			Initialize();
			m_state == State::GAME;
		}
	}

	m_spawnTimer -= dt;

	

	m_scene->Update(dt, m_engine->GetRenderer(), m_engine->GetAudio());
}

void SpaceGame::Draw(Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void SpaceGame::OnPlayerDead(const Event& event)
{
	m_state = State::GAME_OVER;
}

void SpaceGame::OnScoreIncrease(const Event& event)
{
	m_score += std::get<int>(event.data); // std::get is to make sure the value is an int
}
