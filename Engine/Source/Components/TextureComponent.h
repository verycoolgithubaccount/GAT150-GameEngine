#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"

class TextureComponent : public RenderComponent
{
private:
	res_t<Texture> m_texture;
	std::string m_textureName;
public:
	void Initialize() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

	res_t<Texture> GetTexture() { return m_texture; }
	void SetTexture(res_t<Texture> texture) { m_texture = texture; }

	std::string GetTextureName() { return m_textureName; }
	void SetTextureName(std::string textureName) { m_textureName = textureName; }
};