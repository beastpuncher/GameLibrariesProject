#pragma once
#include "engine.h"
#include "color.h"
#include <string>
#include "SDL_ttf.h"
#include "vector2D.h"
#include "color.h"

class ENGINE_API Text 
{
public:
	Text(const std::string& text, const std::string& fontName, int fontSize, const Color & color);
	~Text();

	void Draw(const Vector2D& position, float angle);

	void SetText(const std::string& text);
	void SetText(const std::string& text, const Color& color);
	void SetColor(Color& color);

protected:
	void Create();

protected:
	SDL_Texture * m_texture;
	TTF_Font* m_font = nullptr;
	std::string m_text;
	Color m_color;


};