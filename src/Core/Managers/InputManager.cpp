#include "stdafx.h"
#include "InputManager.h"


void InputManager::Update(float deltaTime)
{
	m_PreviousKey = m_CurrentKey;
	m_CurrentKey.reset(); // Clear the current key states before polling
	UpdateKeyboard();
	UpdateMouse();
}


void InputManager::UpdateKeyboard()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_CurrentKey.set(static_cast<int>(KeyBind::Pause));
	}
}

void InputManager::UpdateMouse()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_CurrentKey.set(static_cast<int>(KeyBind::Shoot));
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		m_CurrentKey.set(static_cast<int>(KeyBind::Right_click));
	}
}

bool InputManager::IsKeyPress(KeyBind key)
{
	auto kb = static_cast<int>(key);
	return m_CurrentKey.test(kb) && !m_PreviousKey.test(kb);
}

bool InputManager::IsKeyDown(KeyBind key)
{
	return m_CurrentKey.test(static_cast<int>(key));
}
