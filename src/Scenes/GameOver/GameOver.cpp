#include "stdafx.h"
#include "GameOver.h"
#include "Core/Utility/strings.h"
#include "Core/Managers/InputManager.h"

GameOver::GameOver(SceneManager& stateManager, sf::RenderWindow& window)
	: m_StateManager(stateManager)
	, m_Window(window)
	, m_IntervalToRestartInSeconds(5)
{

}

void GameOver::OnInit()
{
	m_Timer.SetInterval(5.0f);

	m_Font.loadFromFile(FONT_A);

	m_GameOverText.setFont(m_Font);
	m_GameOverText.setString("You have lost all your lives!");
	m_GameOverText.setOutlineColor(sf::Color::Blue);
	m_GameOverText.setCharacterSize(64); // Adjust as needed
	m_GameOverText.setFillColor(sf::Color::White);
	m_GameOverText.setOutlineThickness(1.2f);
	// Center the origin of the text
	sf::FloatRect textRect = m_GameOverText.getLocalBounds();
	m_GameOverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	m_TimeToRestart.setFont(m_Font);
	m_TimeToRestart.setCharacterSize(22);
	m_TimeToRestart.setOutlineColor(sf::Color::Blue);
	m_TimeToRestart.setOutlineThickness(1.2f);
	m_TimeToRestart.setFillColor(sf::Color::White);
	m_TimeToRestart.setPosition(0, 0);
}

void GameOver::OnDestroy()
{

}

void GameOver::OnStart()
{

}

void GameOver::OnStop()
{

}

void GameOver::Update(float deltaTime)
{
	if (m_Timer.HasTimePassed(deltaTime))
	{
		m_StateManager.Switch(SceneID::CREDITS);
	}


	std::string timeLeftToRestartText = "Restarting in " + std::to_string(static_cast<int>(m_IntervalToRestartInSeconds - m_Timer.GetPassedTime()));
	m_TimeToRestart.setString(timeLeftToRestartText);

	// Position it in the center every frame in case the window resizes
	m_GameOverText.setPosition(m_Window.getSize().x / 2.0f, m_Window.getSize().y / 2.0f);

}

void GameOver::Draw()
{
	m_Window.draw(m_GameOverText);
	m_Window.draw(m_TimeToRestart);
}

void GameOver::HandleInput(float deltaTime)
{
	InputManager::Get().Update(deltaTime);
}
