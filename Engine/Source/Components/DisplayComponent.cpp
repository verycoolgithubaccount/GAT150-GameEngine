#include "DisplayComponent.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Core/EString.h"
#include "TextureAnimationComponent.h"
#include "Component.h"

#include <variant>

FACTORY_REGISTER(DisplayComponent);

void DisplayComponent::Initialize()
{
	ADD_OBSERVER(DisplayUpdate, DisplayComponent::OnDisplayUpdate);
}

void DisplayComponent::Update(float dt)
{
	//
}

void DisplayComponent::OnDisplayUpdate(const Event& event)
{
	if (IsEqualIgnoreCase(event.name, m_owner->GetName()))
	{
		int num = 4;
		//auto num = std::get<int>(event.data);

		m_owner->GetComponent<TextureAnimationComponent>()->HideSegments("on", 8, num);
	}
}

void DisplayComponent::Read(const json_t& value)
{
	Component::Read(value);
	READ_DATA_NAME(value, "numColumns", m_numColumns);
	READ_DATA_NAME(value, "numRows", m_numRows);
	READ_DATA_NAME(value, "tileSize", m_tileSize);
	READ_DATA_NAME(value, "spacing", m_spacing);
	READ_DATA_NAME(value, "tileNames", m_tileNames);
	READ_DATA_NAME(value, "tiles", m_tiles);
}

void DisplayComponent::Write(json_t& value)
{
	//
}