#include "enemyControllerComponent.h"
#include "inputManager.h"
#include "entity.h"
#include "transformComponent.h"
#include "kinematicComponent.h"
#include "renderer.h"
#include "audioSystems.h"
#include "scene.h"
#include "missile.h"
#include "_math.h"
#include "timer.h"

void EnemyControllerComponent::Create(float speed)
{
	m_speed = speed;
	m_timer = Math::GetRandomRange(m_fireRateMin, m_fireRateMax);

	

}

void EnemyControllerComponent::Destroy()
{
}

void EnemyControllerComponent::Update()
{
	float dt = Timer::Instance()->DeltaTime();
	m_timer = m_timer - dt;
	if (m_timer < 0.0f)
	{
		Missile* missile = new Missile(m_owner->GetScene());
		missile->Create("enemyMissile", m_owner->GetTransform().position, Vector2D::up, 1000.0f);
		m_owner->GetScene()->AddEntity(missile);
		m_timer = Math::GetRandomRange(m_fireRateMin,m_fireRateMax);
	}

	Vector2D force = Vector2D::up;
	force.y = 1.0;

	Entity* player = m_owner->GetScene()->GetEntityWithID("player");
	if (player)
	{
		float dx = player->GetTransform().position.x - m_owner->GetTransform().position.x;
		if (dx < -32.0f) force.x = -1.0f;
		if (dx >  32.0f) force.x =  1.0f;
	}


	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}

	Vector2D size = Renderer::Instance()->GetSize();

	m_owner->GetTransform().position = m_owner->GetTransform().position + (force * m_speed * Timer::Instance()->DeltaTime());

	
}
