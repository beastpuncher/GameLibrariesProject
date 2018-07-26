#pragma once

class Engine;
class Scene;

class Game
{
public:
	Game(Engine* engine) : m_engine(engine) {}
	~Game() {}

	bool Initialize();
	void Shutdown();
	void Update();

	bool Run() { return m_running; }

protected:
	Engine* m_engine;
	bool m_running = false;
	Scene* m_scene = nullptr;

};