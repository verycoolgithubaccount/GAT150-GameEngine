#pragma once
#include "RenderComponent.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include <string>

class TextComponent : public RenderComponent
{
private:
	std::string m_text;
	std::string m_fontName;
	int m_fontSize = 8;
	Color m_color{ 1, 1, 1 };

	std::unique_ptr<Text> m_textObject;
	bool m_textChanged = true;
public:
	TextComponent() = default;

	CLASS_DECLARATION(TextComponent);
	CLASS_PROTOTYPE(TextComponent);

	void Initialize() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

	void SetText(const std::string& text);
	void SetColor(const Color& color) { m_color = color; }
	//void SetFont(const res_t<Font>& font) { m_textObject->SetFont(font); }

	TextComponent(const TextComponent& other);
};