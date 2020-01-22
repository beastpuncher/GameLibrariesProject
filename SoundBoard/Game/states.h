#pragma once 
#include "state.h" 


class TitleState : public IState 
{ public:     
	TitleState(StateMachine* owner) : IState(owner) {}     

void Enter();     
void Update();     
void Exit();  

protected:     
	size_t m_credits = 0; 


};

class EnterStageState : public IState {

public:
	EnterStageState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
protected:
	
};

class GameState : public IState {
public:     
	GameState(StateMachine* owner) : IState(owner) {}      
			void Enter();     
			void Update();    
			void Exit(); 
protected:
	float m_respawnTimer = 0.0f;
	float m_respawnRate = 3.0f;
};
