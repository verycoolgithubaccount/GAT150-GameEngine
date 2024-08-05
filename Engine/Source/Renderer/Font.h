#pragma once
#include "../Resources/Resource.h"
#include <SDL_ttf.h>
#include <iostream>

class Font : public Resource
{
private:
	_TTF_Font* m_ttfFont{ nullptr };
	bool Load(const std::string& name, int fontSize);
public:
	Font() = default;
	~Font();
	
	friend class Text;

	// Inherited via Resource
	bool Create(std::string name, ...) override;
};