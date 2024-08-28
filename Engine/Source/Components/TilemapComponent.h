#pragma once
#include "Component.h"
#include "Math/Vector2.h"
#include <vector>

class TilemapComponent : public Component
{
private:
	int m_numColumns;
	int m_numRows;
	Vector2 m_tileSize{ 0, 0 };

	std::vector<std::string> m_tileNames;
	std::vector<int> m_tiles;
public:
	TilemapComponent() = default;

	CLASS_DECLARATION(TilemapComponent);
	CLASS_PROTOTYPE(TilemapComponent)

	void Initialize() override;
	void Update(float dt) override;
};