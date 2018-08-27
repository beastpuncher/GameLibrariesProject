#include "audioSystems.h"
#include "fileSystem.h"
#include <assert.h>

bool AudioSystems::Initialize(Engine* engine)
{
	m_engine = engine;

	FMOD_RESULT result = FMOD::System_Create(&m_fmodSystem);
	assert(result == FMOD_OK);
	void* extradriverdata = nullptr;
	result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	assert(result == FMOD_OK);


	return true;
}

void AudioSystems::Shutdown()
{
	for (auto key: m_sounds)
	{
		key.second->release();
	}
	m_fmodSystem->close();
	m_fmodSystem->release();
}

void AudioSystems::Update()
{
	FMOD_RESULT  result = m_fmodSystem->update();

}

void AudioSystems::AddSound(const std::string & id, const std::string & audioname)
{
	if (m_sounds.find(id) == m_sounds.end())
	{

		FMOD::Sound* fmodsound = nullptr;
		std::string filename = FileSystem::Instance()->GetPathname() + audioname;
		FMOD_RESULT result = m_fmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &fmodsound);
		if (result == FMOD_OK)
		{
			m_sounds[id] = fmodsound;
		}
	}
}

void AudioSystems::PlaySound(const std::string & id,bool loop)
{
	assert(m_sounds.find(id) != m_sounds.end());

	FMOD::Channel* channel;
	auto iter = m_sounds.find(id);
	if (iter != m_sounds.end()) 
	{
		FMOD::Sound* fmodSound = iter->second;
		FMOD_MODE mode = (loop) ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
		fmodSound->setMode(mode);
		FMOD_RESULT result = m_fmodSystem->playSound(fmodSound, 0, false, &channel);
		assert(result == FMOD_OK);
	}
}

void AudioSystems::RemoveSound(const std::string & id)
{
	assert(m_sounds.find(id) != m_sounds.end());

	auto iter = m_sounds.find(id);
	if (iter != m_sounds.end())
	{
		FMOD::Sound* fmodSound = iter->second;
		FMOD_RESULT result = fmodSound->release();
		assert(result == FMOD_OK);
		m_sounds.erase(iter);

	}


}
