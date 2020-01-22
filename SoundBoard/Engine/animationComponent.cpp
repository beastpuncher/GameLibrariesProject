#include "animationComponent.h"
#include "spriteComponent.h"
#include "entity.h"
#include "texture.h"
#include "timer.h"
#include "engine.h"

void AnimationComponent::Create(std::vector<std::string>& textureNames, float rate, ePlayback playback)
{
	m_rate = rate;
	m_placyback = playback;
	for (std::string textureName : textureNames)
	{
		Texture* texture = new Texture();
		texture->Create(textureName);
		m_textures.push_back(texture);	
	}
}

void AnimationComponent::Destroy()
{
	for (Texture* texture : m_textures)
	{
		texture->Destroy();
		delete texture;
	}
	m_textures.clear();
}

void AnimationComponent::Update()
{
	float dt = Timer::Instance()->DeltaTime();
	m_timer = m_timer + dt;
	if (m_timer >= m_rate)
	{
		m_timer = m_timer - m_rate;
		m_frame = m_frame + m_direction;
		if (m_frame >= m_textures.size() || m_frame < 0)
		{
			switch (m_placyback)
			{
			case AnimationComponent::LOOP:
				m_frame = 0;
				break;
			case AnimationComponent::ONE_TIME:
				m_frame = (int)m_textures.size() - 1;
				break;
			case AnimationComponent::ONE_TIME_DESTROY:
				m_frame = m_textures.size() - 1;
				m_owner->SetState(Entity::DESTROY);
				break;
			case AnimationComponent::PING_PONG:
				m_frame = Math::Clamp(m_frame, 0, m_textures.size() - 1);
				m_direction = -m_direction;
				// ???
				break;
			}

		
		}
	}

	SpriteComponent* spriteComponent = m_owner->GetComponent<SpriteComponent>();
	if (spriteComponent)
	{
		spriteComponent->SetTexture(GetTexture());
	}
}

Texture * AnimationComponent::GetTexture()
{
	return m_textures[m_frame];
}
