#pragma once
#include "vector2D.h"
#include "vector3D.h"
#include "matrix33.h"
#include "renderComponent.h"
#include "controllerComponent.h"
#include "kinematicComponent.h"
#include "engine.h"

class Texture;

class ENGINE_API TransformControllerComponent : public IControllerComponent
{
public:
	TransformControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(const Vector2D& position, float rotation, float speed, float roatateRate);
	void Destroy();
	void Update();


protected:
	Vector2D m_position;
	float m_rotation;
	float m_speed = 0.0f;
	float m_roatateRate = 0.0f;


};