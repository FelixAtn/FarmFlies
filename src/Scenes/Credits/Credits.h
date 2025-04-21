#pragma once

class Credits : public IGameScene
{
public:
	Credits(SceneManager& sceneManager, sf::RenderWindow& window);
	void Update(float deltaTime) override;
	void Draw() override;

private:
	void UpdateCursor();

private:
	SceneManager& m_SceneManager;
	sf::RenderWindow& m_Window;

	sf::Texture m_CursorTexture;
	sf::Sprite m_CursorSprite;
	sf::Vector2i m_MousePos;

	sf::Font m_Font;
	std::vector<sf::Text> m_CreditTexts;

	sf::RectangleShape m_BackButton;
	sf::Text m_BackText;
};

