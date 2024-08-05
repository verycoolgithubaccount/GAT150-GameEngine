#include "Font.h"

Font::~Font()
{
	if (m_ttfFont != nullptr)
	{
		TTF_CloseFont(m_ttfFont);
	}
}

bool Font::Load(const std::string& name, int fontSize)
{
	m_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
	if (m_ttfFont == nullptr)
	{
		std::cerr << "Could not load font: " << name << std::endl;
		return false;
	}

	return true;
}

bool Font::Create(std::string name, ...)
{
	va_list args; // list of passed in variadic arguments
	va_start(args, name);
	int fontSize = va_arg(args, int); // fontSize = first int in arguments
	va_end(args);

	return Load(name, fontSize);
}
