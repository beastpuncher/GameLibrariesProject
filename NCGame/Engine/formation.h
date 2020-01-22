#pragma once
#include "entity.h"
#include "enemy.h"

class Formation : public Entity
{
	Formation(Scene* scene, const ID& id) : Entity(scene, id) {}

};