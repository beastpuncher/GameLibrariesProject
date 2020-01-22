#include "enemy.h"
#include "ship.h"
#include "transformComponent.h"
#include "spriteComponent.h"
#include "kinematicComponent.h"
#include "aabbComponent.h"
#include "enemyControllerComponent.h"
#include "audioSystems.h"
#include "eventManager.h"
#include "animationComponent.h"
#include "waypointControllerComponent.h"
#include "transfromControllerComponent.h"
#include "stateMachine.h"
#include "explosion.h"
#include "timer.h"
#include "scene.h"
#include "entity.h"
#include "formation.h"
#include "missile.h"
#include "timer.h"
#include <vector>
#include <iostream>

std::vector<Vector2D> Enemy::m_enterPath = { Vector2D(200.0f, 400.0f), Vector2D(300.0f, 300.0f), Vector2D(200.0f, 200.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 400.0f) };

void Enemy::Create(const Info& info)
{
	SetTag("enemy");
	m_info = info;

	float select = Math::GetRandomRange(0.0f, 1.0f);
	if (select <= 0.9f) 
	{
		m_scoreValue = 100;
	}
	else 
	{
		m_scoreValue = 200;
	}

	if (m_info.side == LEFT)
	{
		m_transform.position = Vector2D(-64.0f, 400.0f);
	}
	else if (m_info.side == RIGHT)
	{
		m_transform.position = Vector2D(864.0f, 400.0f);
	}
	else if (m_info.side == TOP)
	{
		m_transform.position = Vector2D(400.0f, -100.0f);
	}
	else if (m_info.side == TOPLEFT)
	{
		m_transform.position = Vector2D(900.0f, -100.0f);
	}
	else
	{
		m_transform.position = Vector2D(400.0f, 700.0f);
	}

	
	m_transform.scale = Vector2D(2.0f, 2.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.5f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("enemy01A.png", Vector2D(0.5f, 0.5f));

	AnimationComponent* animationComponent;
	animationComponent = AddComponent<AnimationComponent>();
	std::vector<std::string> animations;
	if (m_info.type == BEE)
	{
		animations = { "enemy02A.png","enemy02B.png" };
	}
	else if(m_info.type == BOSS)
	{
		animations = { "enemy01A.png","enemy01B.png" };
	}
	else
	{
		animations = { "enemy03A.png","enemy03B.png" };
	}
	animationComponent->Create(animations, 1.0f / 10.0f);

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create(Vector2D(0.7f,0.9f));

	m_stateMachine = new StateMachine(GetScene(), this);
	m_stateMachine->AddState("enter_path", new EnterPathState(m_stateMachine));
	m_stateMachine->AddState("enter_formation", new EnterFormationState(m_stateMachine));
	m_stateMachine->AddState("idle", new IdleState(m_stateMachine));
	m_stateMachine->AddState("attack", new AttackState(m_stateMachine));
	m_stateMachine->AddState("boss", new BossState(m_stateMachine));
	m_stateMachine->SetState("enter_path");

	
}

void Enemy::Update()
{
	Entity::Update();

	m_stateMachine->Update();
}

void Enemy::OnEvent(const Event & event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "playerMissile")
		{
			Event score;
			score.eventID = "add_score";
			score.varient.asInt = m_scoreValue;
			score.varient.type = Varient::INTEGER;
			EventManager::Instance()->SendGameMessage(score);

			Explosion* explosion = m_scene->AddEntity<Explosion>();
			explosion->Create(m_transform.position);
			
			
			SetState(Entity::DESTROY);
		}
		if (event.sender->GetTag() == "player")
		{
			SetState(Entity::DESTROY);
		}
	}

}

void EnterPathState::Enter()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->AddComponent<WaypointControllerComponent>();
	//std::cout << m_owner->GetEntity<Enemy>()->m_info.side << std::endl;
	waypointController->Create(m_owner->GetEntity<Enemy>()->m_info.formation->GetEnterPath(m_owner->GetEntity<Enemy>()->m_info.side), m_owner->GetEntity<Enemy>()->m_info.speed, 5.0f, true);
}

void EnterPathState::Update()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->GetComponent<WaypointControllerComponent>();
	if (waypointController && waypointController->IsComplete())
	{
		m_owner->GetEntity()->RemoveComponent(waypointController);
		m_owner->SetState("enter_formation");

	}
}

void EnterPathState::Exit()
{

}


void EnterFormationState::Enter()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->AddComponent<WaypointControllerComponent>();
	waypointController->Create(std::vector<Vector2D> { m_owner->GetEntity<Enemy>()->m_info.target }, m_owner->GetEntity<Enemy>()->m_info.speed, 5.0f);
	
}


void EnterFormationState::Update() 
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->GetComponent<WaypointControllerComponent>();
	if (waypointController && waypointController->IsComplete())
	{
		m_owner->GetEntity()->RemoveComponent(waypointController);
		m_owner->SetState("idle");

	}
}
void EnterFormationState::Exit() 
{
}

void IdleState::Enter()
{
	TransformControllerComponent* controller = m_owner->GetEntity()->AddComponent<TransformControllerComponent>();
	controller->Create(m_owner->GetEntity<Enemy>()->m_info.target,180.0f, m_owner->GetEntity<Enemy>()->m_info.speed,5.0f);

	m_timer = Math::GetRandomRange(m_timeMin, m_timeMax);
}

void IdleState::Update()
{ 
	Ship* ship = dynamic_cast<Ship*>(m_owner->GetScene()->GetEntityWithID("player"));
	
	float dt = Timer::Instance()->DeltaTime();
	if (ship)
	{
		m_timer = m_timer - dt;
		if (m_timer <= 0.0f)
		{
			TransformControllerComponent* controller = m_owner->GetEntity()->GetComponent<TransformControllerComponent>();
			m_owner->GetEntity()->RemoveComponent(controller);
			if (m_owner->GetEntity<Enemy>()->m_info.type == Enemy::eType::BOSS) {
				m_owner->SetState("boss");
			}
			else
			{
				m_owner->SetState("attack");
			}
		}
	}
	else
	{
		m_waitTimer = m_waitTimer - dt;
		if (m_waitTimer <= 0.0f)
		{
			Formation* formation = dynamic_cast<Formation*>(m_owner->GetScene()->GetEntityWithID("formation"));
			formation->setPlayerExistance(true);
		}
	}
	

}
void IdleState::Exit()
{
}

void AttackState::Enter()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->AddComponent<WaypointControllerComponent>();
	waypointController->Create(m_owner->GetEntity<Enemy>()->m_info.formation->GetRandomAttack() ,m_owner->GetEntity<Enemy>()->m_info.speed, 5.0f);
}

void AttackState::Update()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->GetComponent<WaypointControllerComponent>();
	if (waypointController && waypointController->IsComplete())
	{
		m_owner->GetEntity()->RemoveComponent(waypointController);
		m_owner->SetState("idle");

	}
}

void AttackState::Exit()
{
	m_owner->GetEntity()->GetTransform().position.y = -64.0f;
}

void BossState::Enter()
{
}

void BossState::Update()
{
	
	m_timer = m_timer - Timer::Instance()->DeltaTime();
	if (m_timer < 0.0f)
	{
		Missile* missile = new Missile(m_owner->GetScene());
		missile->Create("enemyMissile", m_owner->GetEntity<Enemy>()->GetTransform().position, Vector2D::up, 1000.0f);
		m_owner->GetScene()->AddEntity(missile);
		m_timer = Math::GetRandomRange(m_fireRateMin, m_fireRateMax);
	}
}

void BossState::Exit()
{
}
