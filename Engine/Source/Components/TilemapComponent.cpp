#include "TilemapComponent.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"

FACTORY_REGISTER(TilemapComponent);

void TilemapComponent::Initialize()
{
	for (int i = 0; i < m_tiles.size(); i++)
	{
		int tileIndex = m_tiles[i];
		if (tileIndex == 0) continue;

		std::string tileName = m_tileNames[tileIndex];
		auto tile = Factory::Instance().Create<Actor>(tileName);

		if (tile)
		{
			int x = i & m_numColumns;
			int y = i / m_numColumns;

			tile->SetPosition(m_owner->GetTransform().position + (Vector2{ x, y } * m_tileSize));
			m_owner->GetScene()->AddActor(std::move(tile), true);
		}
	}
}

void TilemapComponent::Update(float dt)
{
	//
}

void TilemapComponent::Read(const json_t& value)
{
	READ_DATA_NAME(value, "numColumns", m_numColumns);
	READ_DATA_NAME(value, "numRows", m_numRows);
	READ_DATA_NAME(value, "tileSize", m_tileSize);
	READ_DATA_NAME(value, "tileNames", m_tileNames);
	READ_DATA_NAME(value, "tiles", m_tiles);
}

void TilemapComponent::Write(json_t& value)
{
	//
}