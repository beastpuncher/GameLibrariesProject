#include "states.h"
#include "scene.h"
#include "entity.h"
#include "spriteComponent.h"
#include "stateMachine.h"
#include "inputManager.h"
#include "waypoint.h"
#include "enemy.h"
#include "ship.h"
#include "formation.h"
#include "textComponent.h"
#include "audioSystems.h"
#include <iostream>
#include "timer.h"


void TitleState::Enter()
{
	InputManager::Instance()->AddAction("Morgan", SDL_SCANCODE_M, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Welcome", SDL_SCANCODE_W, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Crawl", SDL_SCANCODE_C, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("LowLands", SDL_SCANCODE_L, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Helparu", SDL_SCANCODE_H, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Noon", SDL_SCANCODE_N, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Valus", SDL_SCANCODE_V, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Kys", SDL_SCANCODE_K, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Cares", SDL_SCANCODE_T, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Dmg", SDL_SCANCODE_D, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Ussr", SDL_SCANCODE_S, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Bath", SDL_SCANCODE_B, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Vath", SDL_SCANCODE_R, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Dank", SDL_SCANCODE_E, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Fate", SDL_SCANCODE_F, InputManager::eDevice::KEYBOARD);

	AudioSystems::Instance()->AddSound("morgan", "Morgan Freeman - I can smell you.mp3");
	AudioSystems::Instance()->AddSound("welcome", "YourWelcome.mp3");
	AudioSystems::Instance()->AddSound("crawl", "CrawlingInMyCrawl.mp3");
	AudioSystems::Instance()->AddSound("low", "LowLands.mp3");
	AudioSystems::Instance()->AddSound("helparu", "Helparu.mp3");
	AudioSystems::Instance()->AddSound("noon", "ItHighNoon.mp3");
	AudioSystems::Instance()->AddSound("valus", "ValusTa'aurc.mp3");
	AudioSystems::Instance()->AddSound("kys", "killys.mp3");
	AudioSystems::Instance()->AddSound("cares", "whoTheHellCares.mp3");
	AudioSystems::Instance()->AddSound("dmg", "dmg.mp3");
	AudioSystems::Instance()->AddSound("ussr", "Ussr.mp3");
	AudioSystems::Instance()->AddSound("bath", "bath.mp3");
	AudioSystems::Instance()->AddSound("vath", "valusBathtub.mp3");
	AudioSystems::Instance()->AddSound("dank", "dankEngine.mp3");
	AudioSystems::Instance()->AddSound("fate", "fate.mp3");
	//AudioSystems::Instance()->AddSound("welcome", "YourWelcome.mp3");
	
}

void TitleState::Update()
{
	if (InputManager::Instance()->GetActionButton("Morgan") == InputManager::eButtonState::PRESSED && InputManager::Instance()->GetActionButton("Fire") != InputManager::eButtonState::HELD)
	{
		AudioSystems::Instance()->PlaySound("morgan", false);
	}
	if (InputManager::Instance()->GetActionButton("Welcome") == InputManager::eButtonState::PRESSED && InputManager::Instance()->GetActionButton("Fire") != InputManager::eButtonState::HELD)
	{
		AudioSystems::Instance()->PlaySound("welcome", false);
	}
	if (InputManager::Instance()->GetActionButton("Crawl") == InputManager::eButtonState::PRESSED && InputManager::Instance()->GetActionButton("Fire") != InputManager::eButtonState::HELD)
	{
		AudioSystems::Instance()->PlaySound("crawl", false);
	}
	if (InputManager::Instance()->GetActionButton("LowLands") == InputManager::eButtonState::PRESSED && InputManager::Instance()->GetActionButton("Fire") != InputManager::eButtonState::HELD)
	{
		AudioSystems::Instance()->PlaySound("low", false);
	}
	if (InputManager::Instance()->GetActionButton("Helparu") == InputManager::eButtonState::PRESSED && InputManager::Instance()->GetActionButton("Fire") != InputManager::eButtonState::HELD)
	{
		AudioSystems::Instance()->PlaySound("helparu", false);
	}
	if (InputManager::Instance()->GetActionButton("Noon") == InputManager::eButtonState::PRESSED && InputManager::Instance()->GetActionButton("Fire") != InputManager::eButtonState::HELD)
	{
		AudioSystems::Instance()->PlaySound("noon", false);
	}
	if (InputManager::Instance()->GetActionButton("Valus") == InputManager::eButtonState::PRESSED && InputManager::Instance()->GetActionButton("Fire") != InputManager::eButtonState::HELD)
	{
		AudioSystems::Instance()->PlaySound("valus", false);
	}
	if (InputManager::Instance()->GetActionButton("Kys") == InputManager::eButtonState::PRESSED && InputManager::Instance()->GetActionButton("Fire") != InputManager::eButtonState::HELD)
	{
		AudioSystems::Instance()->PlaySound("kys", false);
	}
	if (InputManager::Instance()->GetActionButton("Cares") == InputManager::eButtonState::PRESSED && InputManager::Instance()->GetActionButton("Fire") != InputManager::eButtonState::HELD)
	{
		AudioSystems::Instance()->PlaySound("cares", false);
	}
	if (InputManager::Instance()->GetActionButton("Dmg") == InputManager::eButtonState::PRESSED && InputManager::Instance()->GetActionButton("Fire") != InputManager::eButtonState::HELD)
	{
		AudioSystems::Instance()->PlaySound("dmg", false);
	}
	if (InputManager::Instance()->GetActionButton("Ussr") == InputManager::eButtonState::PRESSED && InputManager::Instance()->GetActionButton("Fire") != InputManager::eButtonState::HELD)
	{
		AudioSystems::Instance()->PlaySound("ussr", false);
	}
	if (InputManager::Instance()->GetActionButton("Bath") == InputManager::eButtonState::PRESSED && InputManager::Instance()->GetActionButton("Fire") != InputManager::eButtonState::HELD)
	{
		AudioSystems::Instance()->PlaySound("bath", false);
	}
	if (InputManager::Instance()->GetActionButton("Vath") == InputManager::eButtonState::PRESSED && InputManager::Instance()->GetActionButton("Fire") != InputManager::eButtonState::HELD)
	{
		AudioSystems::Instance()->PlaySound("vath", false);
	}
	if (InputManager::Instance()->GetActionButton("Dank") == InputManager::eButtonState::PRESSED && InputManager::Instance()->GetActionButton("Fire") != InputManager::eButtonState::HELD)
	{
		AudioSystems::Instance()->PlaySound("dank", false);
	}
	if (InputManager::Instance()->GetActionButton("Fate") == InputManager::eButtonState::PRESSED && InputManager::Instance()->GetActionButton("Fire") != InputManager::eButtonState::HELD)
	{
		AudioSystems::Instance()->PlaySound("fate", false);
	}
}

void TitleState::Exit()
{
	
}
void EnterStageState::Enter()
{
	

}

void EnterStageState::Update()
{
	
}

void EnterStageState::Exit()
{
}

void GameState::Enter()
{
	
}

void GameState::Update()
{
	
}

void GameState::Exit()
{
}


