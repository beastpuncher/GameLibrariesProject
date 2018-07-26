#pragma once
#include "engine.h"
#include "singleton.h"
#include "color.h"
#include "vector2D.h"
#include <SDL_image.h>
#include <map>

class Texture;

class ENGINE_API Renderer : public Singleton<Renderer>
{
public:
	Renderer() {};

	bool Initialize(Engine* engine);
	SDL_Renderer* GetRenderer() { return m_renderer; }
	void Shutdown();
	void Beginframe();
	void EndFrame();
	void SetColor(const Color & color);
	void DrawTexture(SDL_Texture * texture, const Vector2D position, float angle);
	void DrawTexture(SDL_Texture* texture, const Vector2D position, Vector2D scale, float angle);
	void DrawTexture(Texture* texture, const Vector2D position, Vector2D scale, float angle);

	friend Singleton<Renderer>;

private:
	Engine * m_engine = nullptr;
	SDL_Renderer* m_renderer = nullptr;

};
