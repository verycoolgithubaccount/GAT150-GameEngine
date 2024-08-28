#pragma once
#include "Audio/AudioClip.h"

class AudioSource
{
public:
	AudioSource() = default;
	AudioSource(res_t<AudioClip> audioClip) : m_audioClip{ audioClip } { }
	~AudioSource() = default;
	bool Play(class Audio& audio, bool loop = false, float volume = 1, float pitch = 1);
	void Stop();
	void Pause(bool pause = true);
	void SetAudioClip(res_t<AudioClip> audioClip) { m_audioClip = audioClip; }
	bool IsPlaying();
	bool SetVolume(float volume);
	bool SetPitch(float pitch);
private:
	res_t<AudioClip> m_audioClip;
	FMOD::Channel* m_channel{ nullptr };
};