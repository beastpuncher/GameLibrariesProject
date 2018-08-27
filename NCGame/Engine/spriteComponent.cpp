#include "spriteComponent.h"
#include "entity.h"
#include "renderer.h"
#include "texture.h"

void SpriteComponent::Create(const std::string & textureName, const Vector2D& origin)
{
	if (textureName != "") 
	{
		m_texture = new Texture();
		m_texture->Create(textureName);
	}
	m_origin = origin;
}

void SpriteComponent::Destroy()
{
	//
}

void SpriteComponent::Update()
{
	//
}

void SpriteComponent::Draw()
{
	if (m_texture) 
	{
		Transform transfrom = m_owner->GetTransform();
		m_texture->Draw(transfrom.position, m_origin, transfrom.scale, transfrom.rotation);
	}
}
