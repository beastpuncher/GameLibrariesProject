#pragma once
#include "engine.h"
#include "singleton.h"
#include <fmod.hpp>
#include <string>
#include <map>

class ENGINE_API AudioSystems : public Singleton<AudioSystems>
{
public:
	AudioSystems() {}
	~AudioSystems() {}


	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	void AddSound(const std::string&id, const std::string& filename);
	void PlaySound(const std::string& id, bool loop);
	void RemoveSound(const std::string& id);

protected:
	Engine* m_engine;
	FMOD::System* m_fmodSystem;
	std::map<std::string, FMOD::Sound*> m_sounds;
};
