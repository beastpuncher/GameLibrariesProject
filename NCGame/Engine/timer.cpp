#include "timer.h"

bool Timer::Initialize(Engine * engine)
{
	m_engine = engine;
	m_paused = false;
	m_timeScale = 1.0f;
	return true;
}

void Timer::Shutdown()
{
}

void Timer::Update()
{
	Uint32 ticks = SDL_GetTicks();
	Uint32 milliseconds = ticks - m_prevTicks;
	m_prevTicks = ticks;
	m_dt = (m_paused) ? 0.0f : milliseconds / 1000.0f;

}