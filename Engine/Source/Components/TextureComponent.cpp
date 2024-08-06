#include "TextureComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Resources/ResourceManager.h"

void TextureComponent::Initialize()
{
	if (!m_textureName.empty())
	{
		//texture = ResourceManager::Instance().Get<Texture>();
	}
}

void TextureComponent::Update(float dt)
{
	//
}

void TextureComponent::Draw(Renderer& renderer)
{
	Transform transform = m_owner->GetTransform().translation;
	renderer.DrawTexture(m_texture.get(), transform.translation.x, transform.translation.y, transform.scale);
}
