#include "shipControllerComponent.h"
#include "inputManager.h"
#include "entity.h"
#include "transformComponent.h"
#include "kinematicComponent.h"
#include "timer.h"

void ShipControllerComponent::Create(float speed)
{
	m_speed = speed;
	InputManager::Instance()->AddAction("Left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Up", SDL_SCANCODE_UP, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Down", SDL_SCANCODE_DOWN, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("Pause", SDL_SCANCODE_P, InputManager::eDevice::KEYBOARD);
}

void ShipControllerComponent::Destroy()
{
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
	if (InputManager::Instance()->GetActionButton("Up") == InputManager::eButtonState::HELD ||
		InputManager::Instance()->GetActionButton("Up") == InputManager::eButtonState::PRESSED)
	{
		force.y = -1.0;
	}
	if (InputManager::Instance()->GetActionButton("Down") == InputManager::eButtonState::HELD ||
		InputManager::Instance()->GetActionButton("Down") == InputManager::eButtonState::PRESSED)
	{
		force.y = 1.0;
	}
	if (InputManager::Instance()->GetActionButton("Pause") == InputManager::eButtonState::PRESSED)
	{
		(Timer::Instance()->IsPaused()) ? Timer::Instance()->UnPause() : Timer::Instance()->Pause();
	}

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::FORCE);
	}

	TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
	transform->position = transform->position + (force * m_speed * Timer::Instance()->DeltaTime());

}
