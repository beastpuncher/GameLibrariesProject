#pragma once
#include "entity.h"
#include "engine.h"

class ENGINE_API Explosion : public Entity
{
public:
	enum eType
	{
		ENEMY,
		PLAYER,

	};

public:
	Explosion(Scene* scene, const ID& id) : Entity(scene,id) {}
	~Explosion() {}

	void Create(const Vector2D & position);
	void Update();

};
