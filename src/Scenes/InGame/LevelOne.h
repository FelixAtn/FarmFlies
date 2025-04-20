#pragma once
#include "Entities/Spaceship.h"
#include "Entities/Enemy.h"

class LevelOne : public IGameScene
{
public:
	LevelOne(SceneManager& sceneManager, sf::RenderWindow& window);

	void OnInit() override {};
	void OnDestroy() override {};
	void OnStart() override;
	void OnStop() override;
	void Update(float deltaTime) override;
	void Draw() override;
	void HandleInput(float deltaTime) override;

private:
	
	// Inits
	void InitBackground();
	void InitLevelText();

	// Updates
	void UpdateBackground(float deltaTime);
	void UpdateSpaceship(float deltaTime);
	void UpdateEnemies(float deltaTime);
	void UpdateLevelText();

	// Draws 
	void DrawBackgrounds();
	void DrawSpaceship();
	void DrawEnemies();
	void DrawTexts();

	// Collision Detection and Resolution
	void CheckAndResolveCollisions();

	// Check Game condition
	void CheckLives();
	void OnGameOver();

	// Reset / INIT
	void Reset();

private:
	// Window Renderer
	sf::RenderWindow& m_Window;

	// Scene Manager
	SceneManager& m_SceneManager;

	// Objects
	Spaceship m_Spaceship;
	std::vector<std::unique_ptr<Enemy>> m_Enemies;

	// Music
	sf::Music m_BackgroundMusic;
	sf::Music m_GameOver;

	// UI
	sf::Texture m_BackgroundTexture;
	sf::Sprite m_BackgroundSprite;
	sf::Sprite m_BackgroundSpriteTwo;

	sf::Font m_Font;
	sf::Text m_LevelText;
	sf::Text m_LivesText;
	sf::Text m_PausedText;

	// Random Number Generator
	RandomGenerator m_RNG;

	// Player Lives
	int m_Lives;

	bool m_IsGamePaused;
};

