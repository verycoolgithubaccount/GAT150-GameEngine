#include "TextComponent.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include <memory>

FACTORY_REGISTER(TextComponent)

void TextComponent::Initialize()
{
	if (!m_fontName.empty())
	{
		auto font = ResourceManager::Instance().Get<Font>(m_fontName, m_fontSize);
		m_textObject = std::make_unique<Text>(font);
	}
}

void TextComponent::Update(float dt)
{
}

void TextComponent::Draw(Renderer& renderer, const Vector2& modifier)
{
	// update text if text has changed
	if (m_textChanged)
	{
		m_textObject->Create(renderer, m_text, m_color);
		m_textChanged = false;
	}

	renderer.DrawTexture(m_textObject->GetTexture(), m_owner->GetTransform(), false, modifier);
}

void TextComponent::SetText(const std::string& text)
{
	// only set the text if it's actually changed
	if (m_text != text) {
		m_text = text;
		m_textChanged = true;
	}
}

void TextComponent::Read(const json_t& value)
{
	Component::Read(value);
	READ_DATA_NAME_REQUIRED(value, "text", m_text);
	READ_DATA_NAME_REQUIRED(value, "fontName", m_fontName);
	READ_DATA_NAME_REQUIRED(value, "fontSize", m_fontSize);
	READ_DATA_NAME_REQUIRED(value, "color", m_color);
}

void TextComponent::Write(json_t& value)
{
	//
}


TextComponent::TextComponent(const TextComponent& other)
{
	m_text = other.m_text;
	m_fontName = other.m_fontName;
	m_fontSize = other.m_fontSize;
	m_color = other.m_color;

	m_textChanged = true;
	m_textObject = std::make_unique<Text>(*other.m_textObject.get());
}