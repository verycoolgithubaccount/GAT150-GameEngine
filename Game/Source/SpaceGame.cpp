#include "SpaceGame.h"
#include "Engine.h"

#include <memory>

bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<Scene>(m_engine);

	std::string sceneNames[] = { "scenes/tilemap.json", "scenes/game.json" };
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
	m_scene->Update(dt, m_engine->GetRenderer(), m_engine->GetAudio());
}

void SpaceGame::Draw(Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void SpaceGame::OnPlayerDead(const Event& event)
{
	std::cout << "game player dead" << std::endl;
}

void SpaceGame::OnScoreIncrease(const Event& event)
{
	m_score += std::get<int>(event.data); // std::get is to make sure the value is an int
}
