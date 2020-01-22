#pragma once
#include "entity.h"
#include "engine.h"

class ENGINE_API ShipExplosion : public Entity
{
public:
	ShipExplosion(Scene* scene, const ID& id) : Entity(scene, id) {}
	~ShipExplosion() {}

	void Create(const Vector2D & position);
	void Update();

};