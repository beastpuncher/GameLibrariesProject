#pragma once
#include "entity.h"
#include "vector2D.h"



class Ship : public Entity
{
public:
	Ship(Scene* scene,const ID& id) : Entity(scene, id) {}
	~Ship() {}

	void Create(const Vector2D& position);

	void OnEvent(const Event& event);

	int GetPlayerLives() { return m_playerLives; }
	void SetPlayerLives(int life) { m_playerLives = life; }

protected:
	int m_playerLives = 3;

};
