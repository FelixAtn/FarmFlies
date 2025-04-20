#include "stdafx.h"
#include "Cursor.h"

void Cursor::SetTexture(const std::string& textureName)
{
	// This line rotates the sprite by 20 degrees.
  // Normally, we would load a texture from a resource manager using textureName
  // and assign it to m_CursorSprite. This appears to be placeholder/test code.
	m_CursorSprite.rotate(20);
	m_CursorSprite.rotate(20);
}

void Cursor::Update()
{
	// Ensure the window is valid before proceeding
	if (m_Window != nullptr)
	{
		// Get the mouse position relative to the render window
		m_CursorPosition = sf::Mouse::getPosition(*m_Window);

		// Update the position of the cursor sprite to match the mouse position.
		// sf::Sprite::setPosition expects float values, so we cast from int to float.
		m_CursorSprite.setPosition(static_cast<float>(m_CursorPosition.x), static_cast<float>(m_CursorPosition.y));
	}
}

void Cursor::Draw(sf::RenderWindow& window)
{
	// Store the pointer to the render window for use in Update()
	m_Window = &window;

	// Check if the pointer is valid before drawing
	if (m_Window != nullptr)
	{
		// Draw the cursor sprite to the window
		m_Window->draw(m_CursorSprite);
	}
}


