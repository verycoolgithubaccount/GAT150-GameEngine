#pragma once
#include "Component.h"

class AudioComponent : public Component
{
private:
	bool m_playOnStart{ false };
	bool m_loop{ false };
	float m_volume{ 1 };
	float m_pitch{ 1 };
	std::string m_soundName;
	std::unique_ptr<class AudioSource> m_audioSource;
public:
	AudioComponent() = default;

	AudioComponent(const AudioComponent& other);

	CLASS_DECLARATION(AudioComponent);
	CLASS_PROTOTYPE(AudioComponent);
	
	void Initialize() override;

	void Update(float dt) override;
	void Play();
	void Play(bool loop, float volume, float pitch);
	bool IsPlaying();
	void Stop();
	void Pause(bool pause = true);
	void SetVolume(float volume);
	void SetPitch(float pitch);
};