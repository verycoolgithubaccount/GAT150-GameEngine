#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"

class TextureComponent : public RenderComponent
{
protected:
	res_t<Texture> m_texture;
	std::string m_textureName;
	Rect m_source;
	bool m_hflip{ false };
public:
	CLASS_DECLARATION(TextureComponent);
	CLASS_PROTOTYPE(TextureComponent)

	void Initialize() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

	res_t<Texture> GetTexture() { return m_texture; }
	void SetTexture(res_t<Texture> texture) { m_texture = texture; }

	std::string GetTextureName() { return m_textureName; }
	void SetTextureName(std::string textureName) { m_textureName = textureName; }

	void SetHFlip(bool hflip) { m_hflip = hflip; }

	Vector2 GetScale() { return Vector2{ m_source.w, m_source.h }; }
};