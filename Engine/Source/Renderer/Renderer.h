#pragma once
#include "../Math/Vector2.h"
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

class Renderer 
{
private:
	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };

	int m_width{ 0 };
	int m_height{ 0 };
public:
	Renderer() = default; // Default constructor, can also do Renderer() {}
	bool Initialize();
	void Shutdown();

	bool CreateWindow(std::string title, int width, int height);
	void BeginFrame();
	void EndFrame();

	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a); // unsigned char would work (0-255) instead of uint8_t (unsigned int 8 bit type, 0-255)

	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawLine(Vector2 vector1, Vector2 vector2);

	void DrawPoint(int x, int y);
	void DrawPoint(float x, float y);
	void DrawPoint(Vector2 vector);

	void DrawRect(int x, int y, int w, int h);
	void DrawRect(float x, float y, float w, float h);

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	friend class Text;
};