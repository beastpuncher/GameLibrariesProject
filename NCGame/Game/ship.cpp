#include "ship.h"
#include "transformComponent.h"
#include "spriteComponent.h"
#include "kinematicComponent.h"
#include "shipControllerComponent.h"
#include "animationComponent.h"
#include "audioSystems.h"
#include "aabbComponent.h"
#include "shipExplosion.h"
#include "eventManager.h"
#include "scene.h"
#include "renderer.h"
#include "_math.h"

void Ship::Create(const Vector2D & position)
{
	SetTag("player");


	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("ship.png", Vector2D(0.5f,0.5f));

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.5f);

	ShipControllerComponent* shipController = AddComponent<ShipControllerComponent>();
	shipController->Create(300.0f);

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create();

}

void Ship::OnEvent(const Event & event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "enemy" || event.sender->GetTag() == "enemyMissile")
		{
			ShipExplosion* explosion = m_scene->AddEntity<ShipExplosion>();
			explosion->Create(m_transform.position);

			Event life;
			life.eventID = "loose life";
			EventManager::Instance()->SendGameMessage(life);

			SetState(Entity::DESTROY);
		}
	}
}
