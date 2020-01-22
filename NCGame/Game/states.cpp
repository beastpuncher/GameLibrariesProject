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
#include <iostream>
#include "timer.h"


void TitleState::Enter()
{

	Entity* entity = m_owner->GetScene()->AddEntity<Entity>("title");
	entity->GetTransform().position = Vector2D(400.0f, 300.0f);
	SpriteComponent* spriteComponent = entity->AddComponent<SpriteComponent>();
	spriteComponent->Create("galaga.png", Vector2D(0.5f, 0.5f));
	spriteComponent->SetDepth(100);

	InputManager::Instance()->AddAction("start", SDL_SCANCODE_RETURN, InputManager::eDevice::KEYBOARD);

	m_credits = 0;
}

void TitleState::Update()
{
	if (InputManager::Instance()->GetActionButton("start") == InputManager::eButtonState::PRESSED)
	{
		m_owner->SetState("enter_stage");
	}
}

void TitleState::Exit()
{
	Entity* entity = m_owner->GetScene()->GetEntityWithID("title");
	if (entity)
	{
		entity->SetState(Entity::DESTROY);
	}
}
void EnterStageState::Enter()
{
	Timer::Instance()->Reset();
	Formation* formation = dynamic_cast<Formation*>(m_owner->GetScene()->GetEntityWithID("formation"));
	if (formation == nullptr)
	{
		formation = m_owner->GetScene()->AddEntity<Formation>("formation");
		formation->Create();
	}

}

void EnterStageState::Update()
{
	Formation* formation = dynamic_cast<Formation*>(m_owner->GetScene()->GetEntityWithID("formation"));
	formation->Update();
	if (formation->DoesPlayerExist())
	{
		m_owner->SetState("game");
	}
}

void EnterStageState::Exit()
{
}

void GameState::Enter()
{
	Ship* ship = new Ship(m_owner->GetScene(), "player");
	ship->Create(Vector2D(400, 510));

	ship->SetPlayerLives(3);

	m_owner->GetScene()->AddEntity(ship);
}

void GameState::Update()
{
	Formation* formation = dynamic_cast<Formation*>(m_owner->GetScene()->GetEntityWithID("formation"));
	formation->Update();

	std::vector<Entity*> enemyExist = m_owner->GetScene()->GetEntitiesWithTag("enemy");
	if (enemyExist.size() == 0)
	{
		std::cout << "No Enemies" << std::endl;
		Formation* formation = dynamic_cast<Formation*>(m_owner->GetScene()->GetEntityWithID("formation"));
		m_owner->GetScene()->RemoveEntity(formation);
		formation = m_owner->GetScene()->AddEntity<Formation>("formation");
		formation->Create();

	}

	Ship* player = dynamic_cast<Ship*>(m_owner->GetScene()->GetEntityWithID("player"));
	if (!player )
	{
		m_respawnTimer = m_respawnTimer - Timer::Instance()->DeltaTime();
		if (m_respawnTimer < 0.0f) {
			Ship* ship = new Ship(m_owner->GetScene(), "player");
			ship->Create(Vector2D(400, 510));
			m_owner->GetScene()->AddEntity(ship);
			m_respawnTimer = m_respawnRate;
		}
	}
	/*else if (player->GetPlayerLives() == 0)
	{
		Entity* life = new Entity(m_owner->GetScene(), "LifeCounter");
		life->GetTransform().position = Vector2D(200.0f, 300.0f);
		TextComponent* textComponents = life->AddComponent<TextComponent>();
		textComponents->Create("GAME OVER ", "emulogic.ttf", 50, Color::white);
		textComponents->SetDepth(100);
		m_owner->GetScene()->AddEntity(life);
	}*/
}

void GameState::Exit()
{
}


