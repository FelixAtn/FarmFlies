#include "stdafx.h"
#include "Credits.h"
#include "Core/Utility/Strings.h"
#include "Core/Utility/Helper.h"

Credits::Credits(SceneManager& sceneManager, sf::RenderWindow& window)
	: m_SceneManager(sceneManager), m_Window(window)
{

	CoreHelper::LoadTextureAndSprite(m_CursorTexture, m_CursorSprite, CURSOR);

	// Load your font — make sure this path is correct for your project
	if (!m_Font.loadFromFile(FONT_C))
	{
		throw std::runtime_error("Failed to load font!");
	}

	// Text entries
	std::vector<std::string> entries = 
	{
	"Lead Developer & Technical Architect\nFelix Atanasescu\n\n"
	"Support Programmer\nAndrei Kotlyarenko\n\n"
	"Support Programmer & QA Tester\nAlina Atanasescu\n\n"
	"Game Designer & Visual Artist\nRadu Buzatu"
	};

	const float spacing = 60.f;
	const float startY = m_Window.getSize().y / 2.f - (entries.size() * spacing) / 2.f;

	for (size_t i = 0; i < entries.size(); ++i)
	{
		sf::Text text;
		text.setFont(m_Font);
		text.setString(entries[i]);
		text.setCharacterSize(28);
		text.setFillColor(sf::Color::White);

		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
		text.setPosition(m_Window.getSize().x / 2.f, startY + i * spacing);

		m_CreditTexts.push_back(text);
	}

	// Back button
	m_BackButton.setSize(sf::Vector2f(150.f, 50.f));
	m_BackButton.setFillColor(sf::Color(70, 70, 70));
	m_BackButton.setOutlineColor(sf::Color::White);
	m_BackButton.setOutlineThickness(2.f);
	m_BackButton.setPosition(20.f, m_Window.getSize().y - 70.f);

	m_BackText.setFont(m_Font);
	m_BackText.setString("Back");
	m_BackText.setCharacterSize(20);
	m_BackText.setFillColor(sf::Color::White);

	sf::FloatRect textBounds = m_BackText.getLocalBounds();
	m_BackText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
	m_BackText.setPosition
	(
		m_BackButton.getPosition().x + m_BackButton.getSize().x / 2.f,
		m_BackButton.getPosition().y + m_BackButton.getSize().y / 2.f - 4.f
	);
}

void Credits::Update(float deltaTime)
{
	UpdateCursor();

	// Handle mouse click
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(m_Window);

		if (m_BackButton.getGlobalBounds().contains(mousePos))
		{
			m_SceneManager.Switch(SceneID::MAIN_MENU);
		}
	}

	// Optional: Escape key fallback
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_SceneManager.Switch(SceneID::MAIN_MENU);
	}
}

void Credits::Draw()
{
	for (const auto& text : m_CreditTexts)
	{
		m_Window.draw(text);
	}
	// Draw Back button
	m_Window.draw(m_BackButton);
	m_Window.draw(m_BackText);
	m_Window.draw(m_CursorSprite);
}

void Credits::UpdateCursor()
{
	// Get mouse position relative to the window
	m_MousePos = sf::Mouse::getPosition(m_Window); // Pass the window object here

	// Update the cursor position
	m_CursorSprite.setPosition(static_cast<float>(m_MousePos.x), static_cast<float>(m_MousePos.y));
}
