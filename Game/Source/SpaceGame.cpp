#include "SpaceGame.h"
#include "Engine.h"

#include <memory>

bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<Scene>(m_engine);

	std::string sceneNames[] = { "scenes/space_tilemap.json", "scenes/scene.json" };
	for (auto& sceneName : sceneNames)
	{
		// read json
		rapidjson::Document document;
		Json::Load(sceneName, document);
		m_scene->Read(document);
	}

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
	switch (m_state)
	{
	case State::GAME:
		if (m_spawnTimer < 0)
		{
			m_spawnTimer = 5;
			auto enemy = Factory::Instance().Create<Actor>("enemy");
			enemy->SetPosition(m_scene->GetCameraPosition() + (randomOnUnitCircle() * (m_engine->GetRenderer().GetWidth() / 1.8)));
			enemy->SetInitialVelocity(m_scene->GetCameraVelocity());

			m_scene->AddActor(std::move(enemy), true);
		}
		break;
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
	m_state = State::PLAYER_DEAD;
}

void SpaceGame::OnScoreIncrease(const Event& event)
{
	m_score += std::get<int>(event.data); // std::get is to make sure the value is an int
}
