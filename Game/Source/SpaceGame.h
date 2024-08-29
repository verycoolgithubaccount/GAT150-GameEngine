#pragma once
#include "Framework/Game.h"
#include "Event/EventManager.h"
#include <memory>

class SpaceGame : public Game, Observer
{
public:
	enum class State : char
	{
		TITLE,
		START_GAME,
		START_LEVEL,
		GAME,
		PLAYER_DEAD,
		GAME_OVER
	};
private:
	State m_state{ State::GAME };
	float m_spawnTimer = 5;
	std::unique_ptr<Scene> m_scene;
public:
	SpaceGame(Engine* engine) : Game{engine} {}

	bool Initialize() override;
	void Shutdown() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

	// events
	void OnPlayerDead(const Event& event);
	void OnScoreIncrease(const Event& event);
};