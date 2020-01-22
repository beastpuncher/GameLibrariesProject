#include "waypoint.h"
#include "aabbComponent.h"

void Waypoint::Create(const Vector2D & position, const Vector2D & size, Entity * owner)
{
	m_owner = owner;

	m_transform.position = position;
	m_transform.scale = size;

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create();
}

void Waypoint::Update()
{
	Entity::Update();
}
