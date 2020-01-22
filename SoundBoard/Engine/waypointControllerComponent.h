#pragma once
#include "controllerComponent.h"
#include "vector2D.h"
#include <vector>
#include "engine.h"

class Waypoint;

class ENGINE_API WaypointControllerComponent : public IControllerComponent
{
public:
	WaypointControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(const std::vector<Vector2D>&points,float speed, float turnRate, bool setPositionAtStart = false);
	void Destroy();
	void Update();

	void setNextWaypoint();

	bool IsComplete() { return m_IsComplete; }

protected:
	bool m_IsComplete = false;
	float m_speed = 0.0f;
	float m_turnRate = 0.0f;

	bool IsBoss = false;

	

	Waypoint * m_Waypoint = nullptr;
	size_t m_waypointIndex;
	std::vector<Waypoint*> m_waypoints;
	

};