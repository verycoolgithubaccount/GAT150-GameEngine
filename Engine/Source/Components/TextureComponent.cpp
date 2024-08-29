#include "TextureComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Engine.h"
#include "Resources/ResourceManager.h"

FACTORY_REGISTER(TextureComponent)

void TextureComponent::Initialize()
{
	if (!m_textureName.empty())
	{
		m_texture = ResourceManager::Instance().Get<Texture>(m_textureName, m_owner->GetScene()->GetEngine()->GetRenderer());
	}

	if (m_texture && m_source.w == 0 && m_source.h == 0)
	{
		m_source.x = 0;
		m_source.y = 0;
		m_source.w = static_cast<int>(m_texture->GetSize().x);
		m_source.h = static_cast<int>(m_texture->GetSize().y);
	}
}

void TextureComponent::Update(float dt)
{
	//
}

void TextureComponent::Draw(Renderer& renderer, const Vector2& modifier)
{
	renderer.DrawTexture(m_texture, m_owner->GetTransform(), m_source, m_hflip, modifier);
}

void TextureComponent::Read(const json_t& value)
{
	Component::Read(value);
	READ_DATA_NAME_REQUIRED(value, "textureName", m_textureName);
	READ_DATA_NAME(value, "source", m_source);
}

void TextureComponent::Write(json_t& value)
{
	//
}