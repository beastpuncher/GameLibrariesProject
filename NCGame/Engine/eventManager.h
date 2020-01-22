#pragma once
#include "event.h"
#include "engine.h"
#include "singleton.h"
#include "eventReceiver.h"

class ENGINE_API EventManager : public Singleton<EventManager>
{
public:

	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	void SendMessage(const Event& event);
	void SendGameMessage(const Event& event);

	void SetGameEventReceiver(EventReceiver* eventReceiver) { m_gameReceiver = eventReceiver; }

protected:
	friend Singleton<EventManager>;

protected:
	Engine * m_engine;
	EventReceiver* m_gameReceiver;
};