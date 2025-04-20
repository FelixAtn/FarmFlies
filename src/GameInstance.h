#pragma once


class GameInstance
{
public:
	GameInstance();
	~GameInstance() = default;

	void Run();

private:
	void InitResources();
	void InitWindow();
	void InitGameStates();

	void HandleEvent();
	void HandleInput();
	void Update();
	void Draw();

	void LoadCharacterData()
	{

	}
	void LoadMusic()
	{
		
	}
	void LoadTextures()
	{

	}
	void LoadMap()
	{
		
	}

private:
	sf::RenderWindow m_Window;
	SceneManager m_StateManager;
	sf::Event m_Event;
	Timer m_Timer;
	sf::Clock m_Clock;
	float m_deltaTime;    
};


