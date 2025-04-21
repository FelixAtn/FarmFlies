#pragma once

enum class ButtonAction { START, CREDITS, EXIT };

struct MenuButton
{
	sf::Sprite sprite;
	sf::IntRect rectNormal;
	sf::IntRect rectHover;
	sf::Vector2f position;
	bool isHovered = false;

	MenuButton(const sf::IntRect& normal, const sf::IntRect& hover, const sf::Vector2f& pos)
		: rectNormal(normal)
		, rectHover(hover)
		, position(pos)
	{}

	void Init(sf::Texture& texture)
	{
		sprite.setTexture(texture);
		sprite.setTextureRect(rectNormal);
		sprite.setPosition(position);
	}

	void UpdateHoverState(const sf::Vector2i& mousePos)
	{
		isHovered = sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
		sprite.setTextureRect(isHovered ? rectHover : rectNormal);
	}
};

class MenuState final : public IGameScene
{
public:
	MenuState(SceneManager& stateManager, sf::RenderWindow& window);
	void OnStart() override;
	void OnStop() override;
	void Update(float deltaTime) override;
	void Draw() override;
	void HandleInput(float deltaTime) override;

private:
	void InitButtons();
	void UpdateButtons();
	void UpdateCursor();

private:
	SceneManager& m_StateManager;
	sf::RenderWindow& m_Window;

	// Sprites
	sf::Sprite m_Background;
	sf::Sprite m_Cursor;

	// Textures
	sf::Texture m_BackgroundTexture;
	sf::Texture m_CursorTexture;
	sf::Texture m_ButtonTexture;
	
	// Button Vectors
	std::vector<MenuButton> m_Buttons;
	std::vector<ButtonAction> m_ButtonActions;

	// Variables
	sf::Vector2i m_MousePos;
	Timer m_Timer;

	int time;
	bool startCounting = false;
};