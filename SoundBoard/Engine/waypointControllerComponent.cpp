#include "waypointControllerComponent.h"
#include "waypoint.h"
#include "timer.h"
#include "kinematicComponent.h"
#include "scene.h"
#include "renderer.h"
#include "debugDraw.h"

void WaypointControllerComponent::Create(const std::vector<Vector2D>&points, float speed, float turnRate, bool setPositionAtStart)
{
	m_speed = speed;
	m_turnRate = turnRate;
	
	for (Vector2D point : points)
	{
		Waypoint* waypoint = m_owner->GetScene()->AddEntity<Waypoint>();
		waypoint->Create(point, Vector2D(10.0f, 10.0f),m_owner);
		m_waypoints.push_back(waypoint);
	}
	m_waypointIndex = 0;
	m_Waypoint = m_waypoints[m_waypointIndex];
}

void WaypointControllerComponent::Destroy()
{
	for (Waypoint* waypoint : m_waypoints)
	{
		waypoint->SetState(Entity::DESTROY);
	}
}

void WaypointControllerComponent::Update()
{
	float dt = Timer::Instance()->DeltaTime();

	if (m_owner->Intersects(m_Waypoint))
	{
		setNextWaypoint();
	}

	DEBUG_DRAW_LINE(m_owner->GetTransform().position, m_Waypoint->GetTransform().position , Color::red);

	Vector2D direction = m_Waypoint->GetTransform().position - m_owner->GetTransform().position;
	float rotation = (Vector2D::GetAngle(direction) * Math::RadiansToDegrees - 90.0f);
	m_owner->GetTransform().rotation = Math::LerpDegrees(m_owner->GetTransform().rotation, rotation, dt * 5.0f);

	Vector2D force = Vector2D::Rotate(Vector2D::down, m_owner->GetTransform().rotation * Math::DegreesToRadians + Math::PI);
	
	

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}

	Vector2D size = Renderer::Instance()->GetSize();

	m_owner->GetTransform().position = m_owner->GetTransform().position + (force * m_speed * Timer::Instance()->DeltaTime());
	
}

void WaypointControllerComponent::setNextWaypoint()
{
	m_waypointIndex++;
	if (m_waypointIndex < m_waypoints.size())
	{
		m_Waypoint = m_waypoints[m_waypointIndex];
	}
	else 
	{
		m_IsComplete = true;
		m_waypointIndex = 0;
		m_Waypoint = m_waypoints[m_waypointIndex];

	}
}
