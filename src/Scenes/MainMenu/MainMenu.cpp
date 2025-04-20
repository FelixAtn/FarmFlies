#include "stdafx.h"
#include "Core/Utility/strings.h"
#include "MainMenu.h"
#include "Core/Managers/InputManager.h"

MenuState::MenuState(SceneManager& stateManager, sf::RenderWindow& window)
	: m_StateManager(stateManager)
	, m_Window(window)
	, time(0)
{

}

void MenuState::OnInit()
{
	m_CursorTexture.loadFromFile(CURSOR);
	m_CursorSprite.setTexture(m_CursorTexture);

	if (!m_Font.loadFromFile(FONT_B)) 
	{
		// Handle error
	}

	// Create the Start button (you can adjust the size and position)
	m_StartButton.setSize(sf::Vector2f(200.0f, 50.0f)); // Width x Height
	m_StartButton.setFillColor(sf::Color::Green); // Button color
	m_StartButton.setPosition(400.0f, 300.0f); // Position on screen (adjust as needed)

	// Set the text for the button
	m_StartButtonText.setFont(m_Font);
	m_StartButtonText.setString("Start");
	m_StartButtonText.setCharacterSize(30); // Adjust size
	m_StartButtonText.setFillColor(sf::Color::White);

	// Center the text in the button
	sf::FloatRect textRect = m_StartButtonText.getLocalBounds();
	m_StartButtonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_StartButtonText.setPosition(m_StartButton.getPosition().x + m_StartButton.getSize().x / 2.0f, m_StartButton.getPosition().y + m_StartButton.getSize().y / 2.0f);
}

void MenuState::OnDestroy()
{

}

void MenuState::OnStart()
{
	
}

void MenuState::OnStop()
{

}

void MenuState::Update(float deltaTime)
{
	// Get mouse position relative to the window
	m_MousePos = sf::Mouse::getPosition(m_Window); // Pass the window object here

	// Update the cursor position
	m_CursorSprite.setPosition(static_cast<float>(m_MousePos.x), static_cast<float>(m_MousePos.y));

	// Check if the mouse is over the button (change button color on hover)
	bool mouseOverButton = m_StartButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(m_MousePos));

	if (mouseOverButton) {
		m_StartButton.setFillColor(sf::Color::Yellow); // Highlight color
	}
	else {
		m_StartButton.setFillColor(sf::Color::Green); // Normal color
	}
}

void MenuState::Draw()
{
	m_Window.draw(m_StartButton); // Draw the button shape
	m_Window.draw(m_StartButtonText); // Draw the text on top of the button
	m_Window.draw(m_CursorSprite);
}

void MenuState::HandleInput(float deltaTime)
{
	bool mouseOverButton = m_StartButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(m_MousePos));

	// Detect mouse click (left mouse button)
	if (InputManager::Get().IsKeyPress(KeyBind::Shoot) && mouseOverButton)
	{
		// Transition to the next state
		m_StateManager.Switch(SceneID::LEVEL_ONE); // Adjust the state transition accordingly
	}

	if (InputManager::Get().IsKeyPress(KeyBind::Pause))
	{
		m_Window.close();
	}

	InputManager::Get().Update(deltaTime);
}
