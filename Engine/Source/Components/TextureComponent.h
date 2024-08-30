#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Math/Vector2.h"

class TextureComponent : public RenderComponent
{
protected:
	res_t<Texture> m_texture;
	std::string m_textureName;
	Vector2 m_textureOffset;
	Rect m_source;
	bool m_hflip{ false };
public:
	CLASS_DECLARATION(TextureComponent);
	CLASS_PROTOTYPE(TextureComponent)

	void Initialize() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer, const Vector2& modifier = { 0, 0 }) override;

	res_t<Texture> GetTexture() { return m_texture; }
	void SetTexture(res_t<Texture> texture) { m_texture = texture; }

	std::string GetTextureName() { return m_textureName; }
	void SetTextureName(std::string textureName) { m_textureName = textureName; }

	void SetHFlip(bool hflip) { m_hflip = hflip; }

	void SetTextureOffset(const Vector2& textureOffset) { m_textureOffset = textureOffset; }

	Vector2 GetScale() { return Vector2{ m_source.w, m_source.h }; }
};