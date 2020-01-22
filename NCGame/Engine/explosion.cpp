#include "explosion.h"
#include "spriteComponent.h"
#include "animationComponent.h"
#include "audioSystems.h"

void Explosion::Create(const Vector2D & position)
{
	
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);
	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("", Vector2D(0.5, 0.5f));

	AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
	std::vector<std::string> textureNames = { "enemy-explosion01.png","enemy-explosion02.png","enemy-explosion03.png","enemy-explosion04.png","enemy-explosion05.png" };
	animationComponent->Create(textureNames, 1.0f / 10.0f, AnimationComponent::ePlayback::ONE_TIME_DESTROY);


	AudioSystems::Instance()->AddSound("hit1", "enemy-hit01.wav");
	AudioSystems::Instance()->AddSound("hit2", "enemy-hit02.wav");
	float select = 0;
	select = Math::GetRandomRange(0.0f, 1.0f);
	if (select <= 0.5f)
	{
		AudioSystems::Instance()->PlaySound("hit1", false);
	}
	else
	{
		AudioSystems::Instance()->PlaySound("hit2", false);
	}
}

void Explosion::Update()
{
	Entity::Update();
}
