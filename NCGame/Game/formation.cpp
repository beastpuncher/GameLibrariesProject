#include "formation.h"
#include "timer.h"
#include "scene.h"

void Formation::Create()
{
	
	m_enterPath[0] = { Vector2D(200.0f, 400.0f), Vector2D(300.0f, 300.0f), Vector2D(200.0f, 200.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 400.0f) };
	m_enterPath[1] = { Vector2D(600.0f, 400.0f) };
	m_enterPath[2] = { Vector2D(400.0f, -64.0f), Vector2D(400.0f, 400.0f), Vector2D(600.0f, 200.0f), Vector2D(700.0f, 300.0f), Vector2D(600.0f, 400.0f) };
	m_enterPath[3] = { Vector2D(400.0f, 200.0f) };
	m_enterPath[4] = { Vector2D(600.0f, 100.0f), Vector2D(200.0f,100.0f) };

	m_attackPaths.push_back({ Vector2D(400.0f, 300.0f), Vector2D(500.0f, 500.0f), Vector2D(600.0f, 600.0f), Vector2D(550.0f, 650.0f) });
	m_attackPaths.push_back({ Vector2D(100.0f, 100.0f), Vector2D(100.0f, 200.0f), Vector2D(300.0f, 400.0f), Vector2D(550.0f, 650.0f) });
	m_attackPaths.push_back({ Vector2D(200.0f, 300.0f), Vector2D(100.0f, 600.0f), Vector2D(400.0f, 400.0f), Vector2D(500.0f, 650.0f) });
	m_attackPaths.push_back({ Vector2D(500.0f, 100.0f), Vector2D(600.0f, 200.0f), Vector2D(50.0f, 500.0f), Vector2D(250.0f, 250.0f) });
	m_attackPaths.push_back({ Vector2D(600.0f, 600.0f), Vector2D(300.0f, 300.0f), Vector2D(350.0f, 50.0f), Vector2D(150.0f, 650.0f) });


	m_formation =
	{ { { Enemy::BEE, Enemy::LEFT, 100.0f, Vector2D(600.0f, 200.0f), this }, 0.0f, false },
	{ { Enemy::BEE, Enemy::LEFT, 100.0f, Vector2D(560.0f, 200.0f), this }, 0.35f, false },
	{ { Enemy::BEE, Enemy::LEFT, 100.0f, Vector2D(520.0f, 200.0f), this }, 0.7f, false },
	{ { Enemy::BEE, Enemy::LEFT, 100.0f, Vector2D(480.0f, 200.0f), this }, 1.05f, false },
	{ { Enemy::BEE, Enemy::LEFT, 100.0f, Vector2D(440.0f, 200.0f), this }, 1.4f, false },
	{ { Enemy::BEE, Enemy::LEFT, 100.0f, Vector2D(400.0f, 200.0f), this }, 1.75f, false },
	{ { Enemy::BEE, Enemy::LEFT, 100.0f, Vector2D(360.0f, 200.0f), this }, 2.1f, false },

	{ { Enemy::BEE, Enemy::TOP, 100.0f, Vector2D(320.0f, 200.0f), this }, 0.0f, false },
	{ { Enemy::BEE, Enemy::TOP, 100.0f, Vector2D(280.0f, 200.0f), this }, 0.35f, false },
	{ { Enemy::BEE, Enemy::TOP, 100.0f, Vector2D(240.0f, 200.0f), this }, 0.7f, false },
	{ { Enemy::BEE, Enemy::TOP, 100.0f, Vector2D(320.0f, 160.0f), this }, 1.05f, false },
	{ { Enemy::BEE, Enemy::TOP, 100.0f, Vector2D(280.0f, 160.0f), this }, 1.4f, false },
	{ { Enemy::BEE, Enemy::TOP, 100.0f, Vector2D(240.0f, 160.0f), this }, 1.75f, false },

	{ { Enemy::BEE, Enemy::BOTTOM, 100.0f, Vector2D(600.0f, 160.0f), this }, 0.0f, false },
	{ { Enemy::BEE, Enemy::BOTTOM, 100.0f, Vector2D(560.0f, 160.0f), this }, 0.35f, false },
	{ { Enemy::BEE, Enemy::BOTTOM, 100.0f, Vector2D(520.0f, 160.0f), this }, 0.7f, false },
	{ { Enemy::BEE, Enemy::BOTTOM, 100.0f, Vector2D(480.0f, 160.0f), this }, 1.05f, false },
	{ { Enemy::BEE, Enemy::BOTTOM, 100.0f, Vector2D(440.0f, 160.0f), this }, 1.4f, false },
	{ { Enemy::BEE, Enemy::BOTTOM, 100.0f, Vector2D(400.0f, 160.0f), this }, 1.75f, false },
	{ { Enemy::BEE, Enemy::BOTTOM, 100.0f, Vector2D(360.0f, 160.0f), this }, 2.1f, false },


	{ { Enemy::BUG, Enemy::RIGHT, 100.0f, Vector2D(600.0f, 120.0f), this }, 0.0f, false },
	{ { Enemy::BUG, Enemy::RIGHT, 100.0f, Vector2D(560.0f, 120.0f), this }, 0.35f, false },
	{ { Enemy::BUG, Enemy::RIGHT, 100.0f, Vector2D(280.0f, 120.0f), this }, 0.7f, false },
	{ { Enemy::BUG, Enemy::RIGHT, 100.0f, Vector2D(240.0f, 120.0f), this }, 1.05f, false },

	{ { Enemy::BOSS, Enemy::TOPLEFT, 100.0f, Vector2D(480.0f, 120.0f), this }, 0.0f, false },
	{ { Enemy::BOSS, Enemy::TOPLEFT, 100.0f, Vector2D(440.0f, 120.0f), this }, 0.35f, false },
	{ { Enemy::BOSS, Enemy::TOPLEFT, 100.0f, Vector2D(400.0f, 120.0f), this }, 0.7f, false },


	};

	m_timer = 0.0f;

}

void Formation::Destroy()
{
}

void Formation::Update()
{
	m_timer = m_timer + Timer::Instance()->DeltaTime();
	for (Info& info : m_formation)
	{
		if (info.isActive == false && m_timer > info.enterTime)
		{
			info.isActive = true;
			Enemy* enemy = m_scene->AddEntity<Enemy>();
			enemy->Create(info.enemyInfo);
		}
	}
		
}

const Formation::Path& Formation::GetRandomAttack()
{
	size_t index = rand() % m_attackPaths.size();
	return m_attackPaths[index];
}
