#pragma once
#include "Framework/Game.h"
#include "Event/EventManager.h"
#include <memory>

class SpaceGame : public Game, Observer
{
private:
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