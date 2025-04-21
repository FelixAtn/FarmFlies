#include "stdafx.h"
#include "Core/Managers/InputManager.h"
#include "LevelOne.h"
#include "Core/Utility/GameplayUtility.h"
#include "Core/Utility/Helper.h"
#include "Core/Utility/strings.h"

// ********************* LEVEL ONE CONSTANTS ********************
constexpr int MAX_COWS = 45;
constexpr int ENEMIES_ON_ROW = 15;
constexpr int ENEMIES_ON_COLUMN = 15;
constexpr int ENEMIES_SPACING_X = 130;
constexpr int ENEMIES_SPACING_Y = 150;
constexpr int LEVEL = 1;
// ****************************************************

LevelOne::LevelOne(SceneManager& sceneManager, sf::RenderWindow& window)
	: m_SceneManager(sceneManager)
	, m_Window(window)
	, m_Lives(3)
	, m_IsGamePaused(false)
{
	InitBackground();
	InitLevelText();
	CoreHelper::LoadMusic(m_BackgroundMusic, GAME_MUSIC);
	CoreHelper::LoadMusic(m_GameOver, GAME_OVER_MUSIC);
}

void LevelOne::OnStart()
{
	Reset();
}

void LevelOne::OnStop()
{
	m_BackgroundMusic.stop();
}

void LevelOne::Update(float deltaTime)
{
	if (!m_IsGamePaused)
	{
		UpdateBackground(deltaTime);
		UpdateSpaceship(deltaTime);
		UpdateEnemies(deltaTime);
		UpdateLevelText();
		CheckAndResolveCollisions();
		CheckLives();
	}
}

void LevelOne::Draw()
{
	DrawBackgrounds();
	DrawTexts();
	DrawSpaceship();
	DrawEnemies();
}


void LevelOne::HandleInput(float deltaTime)
{
	if (InputManager::Get().IsKeyPress(KeyBind::Pause) && !m_IsGamePaused)
	{
		m_IsGamePaused = true; 
	}
	else if (InputManager::Get().IsKeyPress(KeyBind::Pause) && m_IsGamePaused)
	{
		m_IsGamePaused = false;
	}

	InputManager::Get().Update(deltaTime);
}

void LevelOne::InitBackground()
{
	CoreHelper::LoadTextureAndSprite(m_BackgroundTexture, m_BackgroundSprite, GAME_BACKGROUND);
	CoreHelper::LoadTextureAndSprite(m_BackgroundTexture, m_BackgroundSpriteTwo, GAME_BACKGROUND);
	const float height = static_cast<float>(m_BackgroundTexture.getSize().y);
	m_BackgroundSprite.setPosition(0.f, 0.f);
	m_BackgroundSpriteTwo.setPosition(0.f, +height); // Make sure this is ABOVE the first
}

void LevelOne::InitLevelText()
{
	// Load font
	if (!m_Font.loadFromFile(FONT_A))  // Make sure to replace with the correct path
	{
		Log::Print("Error loading font!", LogLevel::ERROR_);
		return;
	}

	// Initialize Level Text
	m_LevelText.setFont(m_Font);
	m_LevelText.setCharacterSize(24);  // Set the font size
	m_LevelText.setFillColor(sf::Color::White);
	m_LevelText.setPosition(10.f, 10.f);  // Position at top-left corner
	m_LevelText.setOutlineThickness(1.2f);
	m_LevelText.setOutlineColor(sf::Color::Blue);

	// Initialize Lives Text
	m_LivesText.setFont(m_Font);
	m_LivesText.setCharacterSize(24);  // Set the font size
	m_LivesText.setFillColor(sf::Color::White);
	m_LivesText.setPosition(10.f, 40.f);  // Position below level text
	m_LivesText.setOutlineThickness(1.2f);
	m_LivesText.setOutlineColor(sf::Color::Blue);

	// Initialize Pause Text
	m_PausedText.setFont(m_Font);
	m_PausedText.setCharacterSize(50);  // Set the font size
	m_PausedText.setFillColor(sf::Color::White);
	// First, set the origin to the center of the text
	m_PausedText.setOrigin(
		m_PausedText.getLocalBounds().width * 0.5f,
		m_PausedText.getLocalBounds().height * 0.5f
	);

	// Then, set the position to the center of the window
	m_PausedText.setPosition(
		sf::Vector2f(
			static_cast<float>(m_Window.getSize().x * 0.4f),
			static_cast<float>(m_Window.getSize().y * 0.4f)
		));
	m_PausedText.setOutlineThickness(1.2f);
	m_PausedText.setOutlineColor(sf::Color::Blue);
	m_PausedText.setString("GAME PAUSE");
}

void LevelOne::UpdateBackground(float deltaTime)
{
	float scrollSpeed = 300.0f;
	float moveY = scrollSpeed * deltaTime;

	m_BackgroundSprite.move(0.0f, moveY);
	m_BackgroundSpriteTwo.move(0.0f, moveY);

	float height = static_cast<float>(m_BackgroundTexture.getSize().y);

	// If a sprite moved completely off screen (above), reposition it below the other
	if (m_BackgroundSprite.getPosition().y >= height)
	{
		m_BackgroundSprite.setPosition(0.f, m_BackgroundSpriteTwo.getPosition().y - height);
	}

	if (m_BackgroundSpriteTwo.getPosition().y >= height)
	{
		m_BackgroundSpriteTwo.setPosition(0.f, m_BackgroundSprite.getPosition().y - height);
	}
}


void LevelOne::UpdateSpaceship(float deltaTime)
{
	m_Spaceship.Update(m_Window, m_Enemies, deltaTime);
}


void LevelOne::UpdateEnemies(float deltaTime)
{
	for (const auto& enemy : m_Enemies)
	{
		if (enemy->IsAlive())
		{
			enemy->Update(deltaTime);
		}
	}
}


void LevelOne::UpdateLevelText()
{
	// Update level and lives texts based on current game state
	m_LevelText.setString("Level: " + std::to_string(LEVEL));
	m_LivesText.setString("Lives: " + std::to_string(m_Lives));
	if (m_Enemies.empty())
	{
		m_SceneManager.Switch(SceneID::LEVEL_TWO);
	}
}


void LevelOne::DrawBackgrounds()
{
	m_Window.draw(m_BackgroundSprite);
	m_Window.draw(m_BackgroundSpriteTwo);

}


void LevelOne::DrawSpaceship()
{
	m_Spaceship.Draw(m_Window);
}


void LevelOne::DrawEnemies()
{
	for (const auto& enemy : m_Enemies)
	{
		enemy->Draw(m_Window);
	}
}


void LevelOne::DrawTexts()
{
	if (m_IsGamePaused)
	{
		m_Window.draw(m_PausedText);
	}

	// Draw UI text (level and lives)
	m_Window.draw(m_LevelText);
	m_Window.draw(m_LivesText);


}

void LevelOne::CheckAndResolveCollisions()
{
	GameplayUtility::CheckEnemyCollision(m_Enemies, m_Spaceship.GetProjectiles());

	if (GameplayUtility::HasEnemyProjectileHitSpaceship(m_Enemies, m_Spaceship))
	{
		m_Lives--;
	};
}


void LevelOne::CheckLives()
{
	if (m_Lives <= 0)
	{
		m_SceneManager.Switch(SceneID::GAME_OVER);
	}
}

void LevelOne::OnGameOver()
{
	m_GameOver.setLoop(false);
	m_GameOver.play();
	m_SceneManager.Switch(SceneID::GAME_OVER);
}

void LevelOne::Reset()
{
	m_Lives = 3;
	// Clear previous game state
	m_Enemies.clear();
	m_Spaceship.Reset();
	m_BackgroundMusic.stop();

	// Reinitialize enemies
	GameplayUtility::EnemySpawner(m_Enemies, PIG, EGG, DifficultyLevel::VERY_EASY, m_RNG, MAX_COWS, ENEMIES_ON_ROW, ENEMIES_ON_COLUMN, ENEMIES_SPACING_X, ENEMIES_SPACING_Y);

	// Reinitialize background
	InitBackground();

	// Restart music
	m_BackgroundMusic.setLoop(true);
	m_BackgroundMusic.play();
}