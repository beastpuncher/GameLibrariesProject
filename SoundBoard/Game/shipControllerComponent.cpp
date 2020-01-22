#include "shipControllerComponent.h"
#include "inputManager.h"
#include "entity.h"
#include "transformComponent.h"
#include "kinematicComponent.h"
#include "renderer.h"
#include "audioSystems.h"
#include "scene.h"
#include "missile.h"
#include "timer.h"

void ShipControllerComponent::Create(float speed)
{
	m_speed = speed;
	InputManager::Instance()->AddAction("Left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Pause", SDL_SCANCODE_P, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Fire", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);

	AudioSystems::Instance()->AddSound("fire", "laser.wav");
	AudioSystems::Instance()->AddSound("shipHit", "ship-explosion.wav");


}

void ShipControllerComponent::Destroy()
{
	AudioSystems::Instance()->RemoveSound("fire");
	AudioSystems::Instance()->RemoveSound("shipHit");
}

void ShipControllerComponent::Update()
{
	Vector2D force = Vector2D::zero;
	if (InputManager::Instance()->GetActionButton("Left") == InputManager::eButtonState::HELD ||
		InputManager::Instance()->GetActionButton("Left") == InputManager::eButtonState::PRESSED)
	{
		force.x = -1.0;
	}
	if (InputManager::Instance()->GetActionButton("Right") == InputManager::eButtonState::HELD ||
		InputManager::Instance()->GetActionButton("Right") == InputManager::eButtonState::PRESSED)
	{
		force.x = 1.0;
	}
	if (InputManager::Instance()->GetActionButton("Pause") == InputManager::eButtonState::PRESSED)
	{
		(Timer::Instance()->IsPaused()) ? Timer::Instance()->UnPause() : Timer::Instance()->Pause();
	}

	if (InputManager::Instance()->GetActionButton("Fire") == InputManager::eButtonState::PRESSED)
	{
		std::vector<Entity*> missiles = m_owner->GetScene()->GetEntitiesWithTag("playerMissile");

			Missile* missile = new Missile(m_owner->GetScene());
			missile->Create("playerMissile",m_owner->GetTransform().position, Vector2D::down, 1000.0f);
			m_owner->GetScene()->AddEntity(missile);
			AudioSystems::Instance()->PlaySound("fire", false);
	}


	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}

	Vector2D size = Renderer::Instance()->GetSize();
	
	m_owner->GetTransform().position = m_owner->GetTransform().position + (force * m_speed * Timer::Instance()->DeltaTime());
	if (m_owner->GetTransform().position.x > size.x)
	{
		m_owner->GetTransform().position.x = 0.0f;
	}
	if (m_owner->GetTransform().position.x < 0.0f)
	{
		m_owner->GetTransform().position.x = size.x;
	}

}
