#include "shipExplosion.h"
#include "spriteComponent.h"
#include "animationComponent.h"
#include "audioSystems.h"

void ShipExplosion::Create(const Vector2D & position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);
	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("", Vector2D(0.5, 0.5f));

	AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
	std::vector<std::string> textureNames = { "ship-explosion01.png","ship-explosion02.png","ship-explosion03.png","ship-explosion04.png"};
	animationComponent->Create(textureNames, 1.0f / 10.0f, AnimationComponent::ePlayback::ONE_TIME_DESTROY);
}

void ShipExplosion::Update()
{
	Entity::Update();
}
