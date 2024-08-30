#pragma once
#include "Component.h"
#include "Math/Vector2.h"
#include <vector>
#include "Event/EventManager.h"

class DisplayComponent : public Component, Observer
{
private:
	int m_numColumns{ 1 };
	int m_numRows{ 1 };
	Vector2 m_tileSize{ 0, 0 };
	float m_spacing{ 0 };

	std::vector<std::string> m_tileNames;
	std::vector<int> m_tiles;
public:
	DisplayComponent() = default;

	CLASS_DECLARATION(DisplayComponent);
	CLASS_PROTOTYPE(DisplayComponent)

	void Initialize() override;
	void Update(float dt) override;

	void OnDisplayUpdate(const Event& event);
};