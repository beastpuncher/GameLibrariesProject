#include "engine.h"
#include "textureManager.h"
#include "renderer.h"
#include "vector2D.h"
#include "inputManager.h"
#include "audioSystems.h"
#include "matrix22.h"
#include "timer.h"
#include "TextManager.h"
#include "text.h"
#include "audioSystems.h"
#include "physics.h"
#include "physicsComponent.h"
#include <iostream>

bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	Physics::Instance()->Initialize(this);
	Timer::Instance()->Initialize(this);
	InputManager::Instance()->Initialize(this);
	AudioSystems::Instance()->Initialize(this);
	return true;
}

void Engine::Shutdown()
{
	Physics::Instance()->Shutdown();
	InputManager::Instance()->Shutdown();
	AudioSystems::Instance()->Shutdown();
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Engine::Update()
{
	Timer::Instance()->Update();
	Timer::Instance()->SetTimeScale(10.0f);
	InputManager::Instance()->Update();
	AudioSystems::Instance()->Update();
	Physics::Instance()->Update();

	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
			m_isQuit = true;
			break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_isQuit = true;
			break;
		}
	}

	SDL_PumpEvents();

	
}
