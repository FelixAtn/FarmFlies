#pragma once

class MenuState : public IGameScene
{
public:
	MenuState(SceneManager& stateManager, sf::RenderWindow& window);
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
	sf::RectangleShape m_StartButton;
	sf::Text m_StartButtonText;
	sf::Font m_Font;
	sf::Texture m_CursorTexture;
	sf::Sprite m_CursorSprite;
	sf::Vector2i m_MousePos;
	Timer m_Timer;
	int time;
	bool startCounting = false;
};
