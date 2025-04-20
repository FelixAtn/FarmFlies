#include "stdafx.h"
#include "GameInstance.h"
#include "Core/Utility/strings.h"
#include "Scenes/InGame/LevelOne.h"
#include "Scenes/InGame/LevelTwo.h"
#include "Scenes/MainMenu/MainMenu.h"
#include "Scenes/GameOver/GameOver.h"
#include "Core/Managers/InputManager.h"

const sf::Color RED_COLOR = { 120,6,6 };
constexpr const char* GAME_NAME = "FARM FLIES";
constexpr int DEFAULT_RESOLUTION_WIDTH = 1920;
constexpr int DEFAULT_RESOLUTION_HEIGHT = 1080;

GameInstance::GameInstance()
	: m_deltaTime(0.0f)
{
	InitResources();
	InitWindow();
	InitGameStates();
}

void GameInstance::InitResources()
{

}

void GameInstance::InitWindow()
{
	m_Window.create(sf::VideoMode(DEFAULT_RESOLUTION_WIDTH, DEFAULT_RESOLUTION_HEIGHT), GAME_NAME, sf::Style::Close);
	m_Window.setMouseCursorVisible(false);

	sf::Image icon; 
	if (!icon.loadFromFile(COW))
	{
		return;
	}

	m_Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

}

void GameInstance::InitGameStates()
{
	std::shared_ptr<MenuState> menuState = std::make_shared<MenuState>(m_StateManager, m_Window);
	std::shared_ptr<LevelOne> levelOne = std::make_shared<LevelOne>(m_StateManager, m_Window);
	std::shared_ptr<LevelTwo> levelTwo = std::make_shared<LevelTwo>(m_StateManager, m_Window);
	std::shared_ptr<GameOver> gameOverState = std::make_shared<GameOver>(m_StateManager, m_Window);

	m_StateManager.Add(menuState, SceneID::MAIN_MENU);
	m_StateManager.Add(levelOne, SceneID::LEVEL_ONE);
	m_StateManager.Add(levelTwo, SceneID::LEVEL_TWO);
	m_StateManager.Add(gameOverState, SceneID::GAME_OVER);
	m_StateManager.Switch(SceneID::MAIN_MENU);
}

void GameInstance::HandleEvent()
{
	while (m_Window.pollEvent(m_Event))
	{
		switch (m_Event.type)
		{
		case sf::Event::Closed:
			m_Window.close();
			break;

		default:
			break;
		}
	}
}

void GameInstance::HandleInput()
{
	m_StateManager.HandleInput(m_deltaTime);
}

void GameInstance::Run()
{
	while (m_Window.isOpen())
	{
		Cursor::Get().Update();
		HandleInput();
		HandleEvent();
		Update();
		Draw(); 
		m_deltaTime = m_Clock.restart().asSeconds();
	}
}

void GameInstance::Update()
{
	m_StateManager.Update(m_deltaTime);

}

void GameInstance::Draw()
{
	m_Window.clear();
	m_StateManager.Draw(m_Window);
	m_Window.display();
}
