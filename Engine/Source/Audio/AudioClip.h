#pragma once
#include "Resources/Resource.h"
#include "Audio.h"
#include <fmod.hpp>

class AudioClip : public Resource
{
private:
	FMOD::Sound* m_sound{ nullptr };
public:
	AudioClip() = default;
	~AudioClip();
	bool Create(std::string name, ...) override;
	bool Load(const std::string& filename, class Audio& audio);
	
	friend Audio;
	friend class AudioSource;
};