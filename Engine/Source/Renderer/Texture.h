#pragma once
#include "../Resources/Resource.h"
#include <iostream>

struct Vector2;

class Texture : public Resource
{
private:
	struct SDL_Texture* m_texture{ nullptr };

	bool Load(const std::string& filename, class Renderer& renderer);

public:
	Texture() = default;
	~Texture();

	Vector2 GetSize();

	friend class Renderer;

	// Inherited via Resource
	bool Create(std::string name, ...) override;

};