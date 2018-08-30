#pragma once
#include "engine.h"
#include "singleton.h"

class ENGINE_API Timer: public Singleton<Timer>
{
public:

	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	float DeltaTime() const { return m_dt * m_timeScale; }
	float UnscaledDeltaTime() const { return m_dt; }

	void SetTimeScale(float timeScale) { m_timeScale = timeScale; }
	float GetTimeScale() { return m_timeScale; }

	void Pause() { m_paused = true; }
	void UnPause() { m_paused = false; }
	bool IsPaused() { return m_paused; }

	void Reset();

	friend Singleton<Timer>;
	
protected:
	Timer() {};

private:
	Engine * m_engine = nullptr;
	float m_fps;
	float m_dt;
	float m_timeScale;
	int m_frameCounter;
	Uint32 m_prevTicks;
	Uint32 m_startTicks;
	bool m_paused;
	const int FRAME_COUNT = 100;

};