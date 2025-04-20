#pragma once

class GameOver : public IGameScene
{
public:
	GameOver(SceneManager& stateManager, sf::RenderWindow& window);
	void OnInit() override;
	void OnDestroy() override;
	void OnStart() override;
	void OnStop() override;
	void Update(float deltaTime) override;
	void Draw() override;
	void HandleInput(float deltaTime) override;

private:
	SceneManager& m_StateManager;
	sf::RenderWindow& m_Window;
	sf::Font m_Font;
	sf::Text m_GameOverText;
	sf::Text m_TimeToRestart;
	Timer m_Timer;
	float m_IntervalToRestartInSeconds;
};


