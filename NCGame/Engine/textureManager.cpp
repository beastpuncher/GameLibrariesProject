#include "textureManager.h"
#include "renderer.h"
#include <assert.h>

bool TextureManager::Initialize(Engine* engine)
{
	m_engine = engine;
	return true;
}

void TextureManager::Shutdown()
{
	for (auto texture : m_texture)
	{
		SDL_DestroyTexture(texture.second);
	}
}

SDL_Texture* TextureManager::GetTexture(const std::string& textureName)
{
	SDL_Texture* texture = m_texture[textureName];

	if (texture == nullptr) {
		SDL_Surface* surface = SDL_LoadBMP(textureName.c_str());
		assert(surface);
		texture = SDL_CreateTextureFromSurface(Renderer::Instance()->GetRenderer(), surface);
		SDL_FreeSurface(surface);

		m_texture[textureName]= texture;
	}

	return texture;
}
