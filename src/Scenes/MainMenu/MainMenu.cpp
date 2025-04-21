#include "stdafx.h"
#include "Core/Utility/strings.h"
#include "MainMenu.h"
#include "Core/Managers/InputManager.h"
#include "Core/Utility/Helper.h"

// Button layout constants
constexpr int BUTTON_SIZE_X = 500;
constexpr int BUTTON_SIZE_Y = 135;
constexpr int BUTTON_DEFAULT_X_POS = 640;
constexpr int BUTTON_DEFAULT_Y_POS = 440;
constexpr int SPRITESHEET_DEFAULT_POS_Y = 0;

MenuState::MenuState(SceneManager& stateManager, sf::RenderWindow& window)
	: m_StateManager(stateManager)
	, m_Window(window)
	, time(0)
{
	CoreHelper::LoadTextureAndSprite(m_BackgroundTexture, m_Background, MAIN_MENU_BACKGROUND);
	CoreHelper::LoadTextureAndSprite(m_CursorTexture, m_Cursor, CURSOR);
	InitButtons();
}

void MenuState::OnStart()
{
	
}

void MenuState::OnStop()
{

}

void MenuState::Update(float deltaTime)
{
	UpdateCursor();
	UpdateButtons();
}

void MenuState::Draw()
{
	m_Window.draw(m_Background);

	for (const auto& button : m_Buttons)
	{
		m_Window.draw(button.sprite);
	}

	m_Window.draw(m_Cursor);
}

void MenuState::HandleInput(float deltaTime)
{
	for (size_t i = 0; i < m_Buttons.size(); ++i)
	{
		if (InputManager::Get().IsKeyPress(KeyBind::Shoot) && m_Buttons[i].isHovered)
		{
			switch (m_ButtonActions[i])
			{
			case ButtonAction::START:
				m_StateManager.Switch(SceneID::LEVEL_ONE);
				break;
			case ButtonAction::CREDITS:
				m_StateManager.Switch(SceneID::CREDITS);
				break;
			case ButtonAction::EXIT:
				m_Window.close();
				break;
			}
		}
	}

	if (InputManager::Get().IsKeyPress(KeyBind::Pause))
	{
		m_Window.close();
	}

	InputManager::Get().Update(deltaTime);
}

void MenuState::InitButtons()
{
	// Attempt to load the texture from the specified file
	if (!m_ButtonTexture.loadFromFile(BUTTONS_SPRITESHEET))
	{
		// Log an error if the texture loading fails
		Log::Print("Texture failed to load! ", LogLevel::ERROR_);
		return;
	}

	// Create buttons
	MenuButton start
	(
		sf::IntRect(BUTTON_SIZE_X * 0, SPRITESHEET_DEFAULT_POS_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y),
		sf::IntRect(BUTTON_SIZE_X * 1, SPRITESHEET_DEFAULT_POS_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y),
		sf::Vector2f(BUTTON_DEFAULT_X_POS, BUTTON_DEFAULT_Y_POS)
	);

	MenuButton credits
	(
		sf::IntRect(BUTTON_SIZE_X * 4, SPRITESHEET_DEFAULT_POS_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y),
		sf::IntRect(BUTTON_SIZE_X * 5, SPRITESHEET_DEFAULT_POS_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y),
		sf::Vector2f(BUTTON_DEFAULT_X_POS, BUTTON_DEFAULT_Y_POS + BUTTON_SIZE_Y)
	);

	MenuButton exit
	(
		sf::IntRect(BUTTON_SIZE_X * 6, SPRITESHEET_DEFAULT_POS_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y),
		sf::IntRect(BUTTON_SIZE_X * 7, SPRITESHEET_DEFAULT_POS_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y),
		sf::Vector2f(BUTTON_DEFAULT_X_POS, BUTTON_DEFAULT_Y_POS + BUTTON_SIZE_Y * 2)
	);

	// Init and store
	for (auto& btn : { &start, &credits, &exit })
	{
		btn->Init(m_ButtonTexture);
		m_Buttons.push_back(*btn);
	}

	m_ButtonActions = { ButtonAction::START, ButtonAction::CREDITS, ButtonAction::EXIT };
}

void MenuState::UpdateButtons()
{	
	// Update hover state for all buttons
	for (auto& button : m_Buttons)
	{
		button.UpdateHoverState(m_MousePos);
	}
}

void MenuState::UpdateCursor()
{
	// Get mouse position relative to the window
	m_MousePos = sf::Mouse::getPosition(m_Window); // Pass the window object here

	// Update the cursor position
	m_Cursor.setPosition(static_cast<float>(m_MousePos.x), static_cast<float>(m_MousePos.y));
}


