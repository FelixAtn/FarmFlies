/*!
 * \file LevelOne.h
 *
 * \brief Contains the LevelOne class for handling the first level of the game.
 *
 * The `LevelOne` class manages the first level of the game, including initializing objects, handling input, updating
 * entities, performing collision detection, and drawing elements to the screen. It also checks the game condition, such as
 * player lives and game over state.
 *
 * \author Felix Atanasescu - HE20830
 * \date April 2025
 */

#pragma once
#include "Entities/Spaceship.h"
#include "Entities/Enemy.h"

 /**
  * @class LevelOne
  * @brief Represents the first level of the game, including background, spaceship, enemies, and game state.
  *
  * The `LevelOne` class handles the logic for managing the gameplay during the first level of the game. It includes
  * the initialization, updating, and drawing of the background, spaceship, enemies, and UI. It also performs collision
  * detection and manages the player's lives, game pause state, and game-over condition.
  */
class LevelOne : public IGameScene
{
public:
    /**
     * @brief Constructs the LevelOne scene with a reference to the scene manager and window.
     *
     * @param sceneManager The scene manager responsible for managing scene transitions
     * @param window The SFML render window to draw the scene on
     */
    LevelOne(SceneManager& sceneManager, sf::RenderWindow& window);

    /**
     * @brief Initializes the scene.
     *
     * This function is a placeholder that is not used for this scene, as initialization is handled elsewhere.
     */
    void OnInit() override {};

    /**
     * @brief Destroys resources when the scene is destroyed.
     *
     * This function is a placeholder that is not used for this scene, as destruction is handled elsewhere.
     */
    void OnDestroy() override {};

    /**
     * @brief Starts the level scene, preparing necessary resources.
     *
     * This function is called when the level is initialized. It sets up the level-specific resources like background
     * music and text.
     */
    void OnStart() override;

    /**
     * @brief Stops the level scene, releasing resources.
     *
     * This function is called when transitioning away from the level. It stops background music and performs other
     * cleanup tasks.
     */
    void OnStop() override;

    /**
     * @brief Updates the level scene every frame.
     *
     * This function is called every frame to update all entities in the level, such as the spaceship, enemies, and
     * background.
     *
     * @param deltaTime The time elapsed since the last frame (in seconds)
     */
    void Update(float deltaTime) override;

    /**
     * @brief Draws the level scene to the window.
     *
     * This function renders the background, spaceship, enemies, and UI elements to the window.
     */
    void Draw() override;

    /**
     * @brief Handles input events for the level scene.
     *
     * This function checks for user input such as keyboard or mouse actions, allowing interaction with the spaceship
     * and the pause menu.
     *
     * @param deltaTime The time elapsed since the last frame (in seconds)
     */
    void HandleInput(float deltaTime) override;

private:
    /**
     * @brief Initializes the background for the level.
     *
     * This function sets up the background textures and positions for the level.
     */
    void InitBackground();

    /**
     * @brief Initializes the level text for displaying information such as level name and player lives.
     *
     * This function sets up the text for level and lives information on the screen.
     */
    void InitLevelText();

    /**
     * @brief Updates the background, including parallax effects if applicable.
     *
     * This function is called every frame to update the background's position and other related effects.
     *
     * @param deltaTime The time elapsed since the last frame (in seconds)
     */
    void UpdateBackground(float deltaTime);

    /**
     * @brief Updates the spaceship position and actions.
     *
     * This function updates the spaceship's position, movement, and other relevant behaviors.
     *
     * @param deltaTime The time elapsed since the last frame (in seconds)
     */
    void UpdateSpaceship(float deltaTime);

    /**
     * @brief Updates the enemies' behaviors and positions.
     *
     * This function updates the enemies' movements, behaviors, and interactions with the spaceship.
     *
     * @param deltaTime The time elapsed since the last frame (in seconds)
     */
    void UpdateEnemies(float deltaTime);

    /**
     * @brief Updates the level-related UI text, such as level name and lives count.
     */
    void UpdateLevelText();

    /**
     * @brief Draws the background to the window.
     */
    void DrawBackgrounds();

    /**
     * @brief Draws the spaceship to the window.
     */
    void DrawSpaceship();

    /**
     * @brief Draws the enemies to the window.
     */
    void DrawEnemies();

    /**
     * @brief Draws the UI text elements (level, lives, paused text) to the window.
     */
    void DrawTexts();

    /**
     * @brief Checks and resolves collisions between the spaceship and enemies.
     *
     * This function checks for collisions between the spaceship and enemies, resolving the game state accordingly.
     */
    void CheckAndResolveCollisions();

    /**
     * @brief Checks the player's lives and updates the game state if necessary.
     *
     * This function monitors the player's remaining lives and triggers game over if lives reach zero.
     */
    void CheckLives();

    /**
     * @brief Handles the game over state.
     *
     * This function is called when the player runs out of lives, triggering the game-over sequence.
     */
    void OnGameOver();

    /**
     * @brief Resets the level for a new playthrough.
     *
     * This function resets the level's entities and variables to their initial state.
     */
    void Reset();

private:
    // Window Renderer
    sf::RenderWindow& m_Window;  ///< The render window to display the level

    // Scene Manager
    SceneManager& m_SceneManager;  ///< The scene manager for handling scene transitions

    // Objects
    Spaceship m_Spaceship;                  ///< The player's spaceship
    std::vector<std::unique_ptr<Enemy>> m_Enemies;  ///< List of enemies in the level

    // Music
    sf::Music m_BackgroundMusic;  ///< Background music for the level
    sf::Music m_GameOver;         ///< Music for the game over state

    // UI
    sf::Texture m_BackgroundTexture;    ///< Texture for the background
    sf::Sprite m_BackgroundSprite;     ///< Sprite for the background
    sf::Sprite m_BackgroundSpriteTwo;  ///< Another sprite for the background (used for parallax effect)

    sf::Font m_Font;           ///< Font used for UI text
    sf::Text m_LevelText;      ///< Text displaying the current level
    sf::Text m_LivesText;      ///< Text displaying the player's remaining lives
    sf::Text m_PausedText;     ///< Text displaying the paused state message

    // Random Number Generator
    RandomGenerator m_RNG;  ///< Random number generator for enemy spawning

    // Player Lives
    int m_Lives;  ///< The player's remaining lives

    bool m_IsGamePaused;  ///< Flag indicating whether the game is paused
};
