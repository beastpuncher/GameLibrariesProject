#pragma once


#ifdef ENGINE_EXPORTS  
#define ENGINE_API __declspec(dllexport)   
#else  
#define ENGINE_API __declspec(dllimport)   
#endif 

#pragma warning(disable:4251)
#pragma warning(disable:4305)
#pragma warning(disable:4244)
#pragma warning(disable:4018)


#include "sdl.h"

class textureManager;

class ENGINE_API Engine
{
public:
	Engine() { }
	~Engine() {}

	bool Initialize();
	void Update();
	void Shutdown();

	bool IsQuit() { return m_isQuit; }
	bool IsDebug() { return m_IsDebug; }
	SDL_Window* GetWindow() { return m_window; }

protected:
	bool m_isQuit = false;
	bool m_IsDebug;
	SDL_Window* m_window = nullptr;
	
};
