#include "game.h"
#include "engine.h"
#include "inputManager.h"
#include "audioSystems.h"
#include "renderer.h"
#include "TextManager.h"
#include "textureManager.h"
#include "vector2D.h"
#include "timer.h"
#include "matrix22.h"
#include "component.h"
#include "transformComponent.h"
#include "spriteComponent.h"
#include "shipControllerComponent.h"
#include "entity.h"
#include "SDL.h"
#include "scene.h"
#include "kinematicComponent.h"
#include <fmod.hpp>

bool Game::Initialize()
{
	bool success = m_engine->Initialize();

	
	Renderer::Instance()->Initialize(m_engine);
	TextureManager::Instance()->Initialize(m_engine);
	TextManager::Instance()->Initialize(m_engine);

	m_scene = new Scene();

	for (size_t i = 0; i < 20; i++) {

		Entity* entity = new Entity();
		TransformComponent* transformComponent = new TransformComponent(entity);
		float x = (float)(rand() % 800);
		float y = (float)(rand() & 600);

		transformComponent->Create(Vector2D(x,y));
		entity->AddComponent(transformComponent);

		m_scene->AddEntity(entity);

	SpriteComponent* spriteComponent = new SpriteComponent(entity);
	spriteComponent->Create("..\\Content\\ship.png");
	entity->AddComponent(spriteComponent);

	KinematicComponent* kinematic = new KinematicComponent(entity);
	kinematic->Create();
	entity->AddComponent(kinematic);

	ShipControllerComponent* shipController = new ShipControllerComponent(entity);
	shipController->Create(50.0f);
	if(i == 1) entity->AddComponent(shipController);
	}
	m_running = success;
	return success;
}

void Game::Shutdown()
{
	InputManager::Instance()->Shutdown();
	AudioSystems::Instance()->Shutdown();
	TextureManager::Instance()->Shutdown();
	Renderer::Instance()->Shutdown();

	SDL_DestroyRenderer(Renderer::Instance()->GetRenderer());
	m_engine->Shutdown();
}

void Game::Update()
{
	
	

	m_scene->Update();

	Renderer::Instance()->Beginframe();
	Renderer::Instance()->SetColor(Color::red);

	m_scene->Draw();

	Renderer::Instance()->EndFrame();
	m_running = !m_engine->IsQuit();
	m_engine->Update();
}
