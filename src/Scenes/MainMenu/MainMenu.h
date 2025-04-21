/*!
 * \file MenuState.h
 *
 * \brief Contains the MenuState class and the MenuButton struct for handling the main menu screen.
 *
 * The `MenuState` class manages the main menu scene of the game, including button interactions, input handling, and
 * the overall drawing of the menu. It includes the `MenuButton` struct, which represents individual buttons and their
 * behaviors such as hover states and actions.
 *
 * \author Felix Atanasescu - HE20830
 * \date April 2025
 */

#pragma once

enum class ButtonAction { START, CREDITS, EXIT };

/**
 * @struct MenuButton
 * @brief Represents a button in the main menu, with hover effects and click regions.
 *
 * This struct holds the sprite, normal and hover texture regions, position, and hover state for each button. It also
 * provides methods to initialize the button and update its hover state based on mouse position.
 */
struct MenuButton
{
    sf::Sprite sprite;         ///< The sprite representing the button in the menu
    sf::IntRect rectNormal;    ///< The texture rectangle for the normal (non-hovered) state
    sf::IntRect rectHover;     ///< The texture rectangle for the hovered state
    sf::Vector2f position;     ///< The position of the button on the screen
    bool isHovered = false;    ///< Whether the button is currently being hovered over

    /**
     * @brief Constructs a MenuButton with the given texture rectangles and position.
     *
     * @param normal The texture rectangle for the normal state
     * @param hover The texture rectangle for the hover state
     * @param pos The position of the button on the screen
     */
    MenuButton(const sf::IntRect& normal, const sf::IntRect& hover, const sf::Vector2f& pos)
        : rectNormal(normal)
        , rectHover(hover)
        , position(pos)
    {}

    /**
     * @brief Initializes the button by setting its texture and position.
     *
     * This function is called to load the button's texture and set its initial texture rectangle and position.
     *
     * @param texture The texture to apply to the button
     */
    void Init(sf::Texture& texture)
    {
        sprite.setTexture(texture);
        sprite.setTextureRect(rectNormal);
        sprite.setPosition(position);
    }

    /**
     * @brief Updates the hover state of the button based on the mouse position.
     *
     * This function checks if the mouse cursor is hovering over the button and updates the button's appearance
     * accordingly (normal or hovered texture).
     *
     * @param mousePos The current mouse position to check for hover state
     */
    void UpdateHoverState(const sf::Vector2i& mousePos)
    {
        isHovered = sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
        sprite.setTextureRect(isHovered ? rectHover : rectNormal);
    }
};

/**
 * @class MenuState
 * @brief Represents the main menu state in the game.
 *
 * The `MenuState` class handles the functionality of the main menu, including button updates, input handling, and
 * rendering. It initializes and updates buttons, manages cursor interactions, and triggers scene changes when buttons
 * are pressed.
 */
class MenuState final : public IGameScene
{
public:
    /**
     * @brief Constructs the MenuState with a reference to the scene manager and the render window.
     *
     * @param stateManager The scene manager that handles scene transitions
     * @param window The SFML render window to draw the menu on
     */
    MenuState(SceneManager& stateManager, sf::RenderWindow& window);

    /**
     * @brief Starts the menu scene.
     *
     * This function is called when the menu scene is initialized. It sets up necessary variables and prepares the
     * menu for interaction.
     */
    void OnStart() override;

    /**
     * @brief Stops the menu scene.
     *
     * This function is called when transitioning away from the menu scene. It cleans up resources or resets variables
     * as needed.
     */
    void OnStop() override;

    /**
     * @brief Updates the menu scene every frame.
     *
     * This function is called every frame to update the state of the menu, such as button hover states and input
     * handling.
     *
     * @param deltaTime The time elapsed since the last frame (in seconds)
     */
    void Update(float deltaTime) override;

    /**
     * @brief Draws the menu scene to the window.
     *
     * This function is called to render the menu, including background, buttons, and cursor.
     */
    void Draw() override;

    /**
     * @brief Handles user input in the menu scene.
     *
     * This function is called every frame to check for user input such as mouse clicks or key presses.
     *
     * @param deltaTime The time elapsed since the last frame (in seconds)
     */
    void HandleInput(float deltaTime) override;

private:
    /**
     * @brief Initializes the buttons for the menu.
     *
     * This function sets up all the menu buttons by loading textures and positioning them on the screen.
     */
    void InitButtons();

    /**
     * @brief Updates the state of the buttons (hover effects, click actions).
     *
     * This function is called every frame to update the buttons' hover states and check for clicks.
     */
    void UpdateButtons();

    /**
     * @brief Updates the position of the cursor.
     *
     * This function checks for the current position of the cursor and updates its sprite position accordingly.
     */
    void UpdateCursor();

private:
    SceneManager& m_StateManager;  ///< The scene manager responsible for handling scene transitions
    sf::RenderWindow& m_Window;    ///< The render window to display the menu

    // Sprites for background and cursor
    sf::Sprite m_Background;      ///< The background sprite of the menu
    sf::Sprite m_Cursor;          ///< The cursor sprite in the menu

    // Textures
    sf::Texture m_BackgroundTexture; ///< The texture for the background
    sf::Texture m_CursorTexture;     ///< The texture for the cursor
    sf::Texture m_ButtonTexture;     ///< The texture for the buttons

    // Menu buttons and actions
    std::vector<MenuButton> m_Buttons;          ///< List of menu buttons
    std::vector<ButtonAction> m_ButtonActions;  ///< Corresponding actions for each button

    // Mouse position and timer variables
    sf::Vector2i m_MousePos;     ///< The current mouse position
    Timer m_Timer;               ///< Timer used for animations or time-based actions
    int time;                    ///< Time tracking for animations or transitions
    bool startCounting = false;  ///< Flag to indicate when to start a countdown 
};