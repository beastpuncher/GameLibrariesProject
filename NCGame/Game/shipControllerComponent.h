#pragma once


#include "vector2D.h"
#include "vector3D.h"
#include "matrix33.h"
#include "renderComponent.h"
#include "controllerComponent.h"
#include "kinematicComponent.h"

class Texture;

class ShipControllerComponent : public IControllerComponent
{
public:
	ShipControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(float speed);
	void Destroy();
	void Update();


protected:
	float m_speed = 0.0f;

};