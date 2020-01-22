#pragma once
#include "entity.h"
#include "vector2D.h"
#include "stateMachine.h"
#include "state.h"

class Enemy : public Entity
{
public:
	enum eType
	{
		BEE,
		BOSS,
		BUG,
	};

	enum eSide
	{
		LEFT,
		RIGHT,
		TOP,
		BOTTOM,
		TOPLEFT,
	};

	struct Info
	{
		eType type;
		eSide side;
		float speed;
		Vector2D target;
		class Formation* formation;
	};

public:
	Enemy(Scene* scene, const ID& id = ID()) : Entity(scene) {}
	~Enemy() {}

	void Create(const Info& info);
	void Update();

	void OnEvent(const Event& event);

	static std::vector<Vector2D> m_enterPath;
	//Vector2D m_targetPosition;
	//float m_speed = 100.0f;

	Info m_info;

protected:
	int m_scoreValue;
	StateMachine* m_stateMachine;

};
class EnterPathState : public IState
{
public:

	EnterPathState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
};

class EnterFormationState : public IState
{
public:
	EnterFormationState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
};

class IdleState : public IState
{
public:
	IdleState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

protected:
	float m_timeMin = 8.0f;
	float m_timeMax = 15.0f;
	float m_timer = 0.0f;

	float m_waitTimer = 10.0f;

};

class AttackState : public IState
{
public:
	AttackState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
};

class BossState : public IState
{
public:
	BossState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

protected:
	float m_timer = 0.0f;
	float m_fireRateMin = 1.0f;
	float m_fireRateMax = 3.0f;
	bool hasBeenHit;
};


