#include "AudioComponent.h"
#include "Resources/ResourceManager.h"
#include "Audio/AudioClip.h"
#include "Audio/AudioSource.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Engine.h"

FACTORY_REGISTER(AudioComponent)
AudioComponent::AudioComponent(const AudioComponent& other)
{
	m_playOnStart = other.m_playOnStart;
	m_loop = other.m_loop;
	m_volume = other.m_volume;
	m_pitch = other.m_pitch;
	m_soundName = other.m_soundName;
	if (other.m_audioSource)
	{
		m_audioSource = std::make_unique<AudioSource>(*other.m_audioSource.get());
	}
}
void AudioComponent::Initialize()
{
	if (!m_audioSource && !m_soundName.empty())
	{
		auto audioClip = ResourceManager::Instance().Get<AudioClip>(m_soundName, m_owner->GetScene()->GetEngine()->GetAudio());
		m_audioSource = std::make_unique<AudioSource>(audioClip);
	}
}
void AudioComponent::Update(float dt)
{
	if (m_owner->IsDestroyed()) Stop();
	if (m_playOnStart)
	{
		m_playOnStart = false;
		Play();
	}
}
void AudioComponent::Play()
{
	if (m_audioSource) m_audioSource->Play(m_owner->GetScene()->GetEngine()->GetAudio(), m_loop, m_volume, m_pitch);
}
void AudioComponent::Play(bool loop, float volume, float pitch)
{
	if (m_audioSource) m_audioSource->Play(m_owner->GetScene()->GetEngine()->GetAudio(), loop, volume, pitch);
}
bool AudioComponent::IsPlaying()
{
	return (m_audioSource && m_audioSource->IsPlaying());
}
void AudioComponent::Stop()
{
	if (m_audioSource) m_audioSource->Stop();
}
void AudioComponent::Pause(bool pause)
{
	if (m_audioSource) m_audioSource->Pause(pause);
}
void AudioComponent::SetVolume(float volume)
{
	m_volume = volume;
	if (m_audioSource->IsPlaying()) m_audioSource->SetVolume(volume);
}
void AudioComponent::SetPitch(float pitch)
{
	m_pitch = pitch;
	if (m_audioSource->IsPlaying()) m_audioSource->SetVolume(pitch);
}
void AudioComponent::Read(const json_t& value)
{
	Component::Read(value);
	READ_DATA_NAME(value, "playOnStart", m_playOnStart);
	READ_DATA_NAME(value, "loop", m_loop);
	READ_DATA_NAME(value, "volume", m_volume);
	READ_DATA_NAME(value, "pitch", m_pitch);
	READ_DATA_NAME(value, "soundName", m_soundName);
}
void AudioComponent::Write(json_t& value)
{
	//
}