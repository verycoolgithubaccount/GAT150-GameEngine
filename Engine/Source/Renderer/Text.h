#pragma once
#include "Color.h"
#include "Math/Vector2.h"
#include "Resources/Resource.h"
#include <SDL_ttf.h>
#include <iostream>

class Font;
class Renderer;
class Texture;

class Text
{
private:
	res_t<Font> m_font{ nullptr };
	res_t<Texture> m_texture{ nullptr };
public:
	Text() = default;
	Text(res_t<Font> font) : m_font{ font } {}
	~Text() = default;

	bool Create(Renderer& renderer, const std::string& text, const Color& color);
	void Draw(Renderer& renderer, float x, float y, float angle = 0, const Vector2& modifier = { 0, 0 });

	void SetFont(res_t<Font> font) { m_font = font; }
	res_t<Texture> GetTexture() { return m_texture; }
};