#include "TextureComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Engine.h"
#include "Resources/ResourceManager.h"

void TextureComponent::Initialize()
{
	if (!m_textureName.empty())
	{
		m_texture = ResourceManager::Instance().Get<Texture>(m_textureName, m_owner->GetScene()->GetEngine()->GetRenderer());
	}
}

void TextureComponent::Update(float dt)
{
	//
}

void TextureComponent::Draw(Renderer& renderer)
{
	renderer.DrawTexture(m_texture, m_owner->GetTransform());
}

void TextureComponent::Read(const json_t& value)
{
	Json::Read(value, "textureName", m_textureName, true);
}

void TextureComponent::Write(json_t& value)
{
	//
}