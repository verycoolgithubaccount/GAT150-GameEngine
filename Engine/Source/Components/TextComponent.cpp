#include "TextComponent.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include <memory>

FACTORY_REGISTER(TextComponent)

void TextComponent::Initialize()
{
	std::cout << m_fontSize;
	if (!m_fontName.empty())
	{
		auto font = ResourceManager::Instance().Get<Font>(m_fontName, m_fontSize);
		m_textObject = std::make_unique<Text>(font);
	}
}

void TextComponent::Update(float dt)
{
}

void TextComponent::Draw(Renderer& renderer)
{
	// update text if text has changed
	if (m_textChanged)
	{
		m_textObject->Create(renderer, m_text, m_color);
		m_textChanged = false;
	}

	renderer.DrawTexture(m_textObject->GetTexture(), m_owner->GetTransform());
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
	READ_DATA_NAME(value, "text", m_text, true);
	READ_DATA_NAME(value, "fontName", m_fontName, true);
	READ_DATA_NAME(value, "fontSize", m_fontSize, true);
	READ_DATA_NAME(value, "color", m_color, true);
}

void TextComponent::Write(json_t& value)
{
	//
}