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
#include "entity.h"
#include "SDL.h"
#include "scene.h"
#include "ship.h"
#include "enemy.h"
#include "fileSystem.h"
#include "spriteComponent.h"
#include "renderComponent.h"
#include "animationComponent.h"
#include "textComponent.h"
#include "eventManager.h"
#include "stateMachine.h"
#include "timer.h"
#include "states.h"
#include <fmod.hpp>
#include <vector>
#include <iostream>

bool Game::Initialize()
{
	bool success = m_engine->Initialize();
	FileSystem::Instance()->SetPathname("..\\Content\\Galaga\\");

	
	EventManager::Instance()->SetGameEventReceiver(this);

	m_scene = new Scene();
	m_stateMachine = new StateMachine(m_scene);

	m_stateMachine->AddState("title", new TitleState(m_stateMachine));
	m_stateMachine->AddState("enter_stage", new EnterStageState(m_stateMachine));
	m_stateMachine->AddState("game", new GameState(m_stateMachine));

	m_stateMachine->SetState("title");

	Entity* entity = new Entity(m_scene, "score");
	entity->GetTransform().position = Vector2D(20.0f, 20.0f);
	TextComponent* textComponent = entity->AddComponent<TextComponent>();
	textComponent->Create(" 0000", "emulogic.ttf", 18, Color::white);
	textComponent->SetDepth(100);
	m_scene->AddEntity(entity);

	Entity* life = new Entity(m_scene, "LifeCounter");
	life->GetTransform().position = Vector2D(100.0f, 500.0f);
	TextComponent* textComponents = life->AddComponent<TextComponent>();
	textComponents->Create("Lives: " + m_lives, "emulogic.ttf", 18, Color::white);
	textComponents->SetDepth(100);
	m_scene->AddEntity(life);


	m_running = success;
	return success;
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(Renderer::Instance()->GetRenderer());
	m_engine->Shutdown();
}

void Game::Update()
{
	m_running = !m_engine->IsQuit();
	m_engine->Update();
	m_stateMachine->Update();

	if (m_lives < 0)
	{
		m_running = false;
	}

	Entity* score = m_scene->GetEntityWithID("score");
	if (score)
	{
		TextComponent* textComp = score->GetComponent<TextComponent>();
		std::string _score = std::to_string(m_score);
		while (_score.length() < 5) _score = "0" + _score;
		textComp->SetText(_score);
	}

	Entity* life = m_scene->GetEntityWithID("LifeCounter");
	if (life)
	{
		TextComponent* textComp = life->GetComponent<TextComponent>();
		std::string _life = std::to_string(m_lives);
		textComp->SetText(_life);
		
	}

	Renderer::Instance()->Beginframe();

	m_scene->Update();
	m_scene->Draw();
	Renderer::Instance()->SetColor(Color::black);

	Renderer::Instance()->EndFrame();
}

void Game::OnEvent(const Event & event)
{
	if (event.eventID == "add_score")
	{
		m_score += event.varient.asInt;
	}
	if (event.eventID == "loose life")
	{
		Ship* ship = dynamic_cast<Ship*>(m_scene->GetEntityWithID("player"));
			m_lives = m_lives - 1;
		//	std::cout << ship->GetPlayerLives() << std::endl;
			//ship->SetPlayerLives(ship->GetPlayerLives() - 1);
	}
}
