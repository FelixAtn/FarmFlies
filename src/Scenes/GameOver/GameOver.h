/*!
 * \file GameOver.h
 *
 * \brief Contains the GameOver class for managing the game over state and restart functionality.
 *
 * The `GameOver` class is responsible for displaying the game over screen, handling user input for restarting the game,
 * and managing the timer for the restart interval. This class also deals with rendering the game over text and any relevant
 * instructions for the player.
 *
 * \author Felix Atanasescu - HE20830
 * \date April 2025
 */

#pragma once

 /**
  * @class GameOver
  * @brief Represents the game over scene where the player is shown the end of the game and options to restart.
  *
  * The `GameOver` class displays the game over screen, including any messages and instructions. It handles the user input
  * for restarting the game after a certain interval and manages the timer for the restart countdown.
  */
class GameOver : public IGameScene
{
public:
    /**
     * @brief Constructs the GameOver scene with a reference to the scene manager and window.
     *
     * @param stateManager The scene manager responsible for managing scene transitions
     * @param window The SFML render window to draw the scene on
     */
    GameOver(SceneManager& stateManager, sf::RenderWindow& window);

    /**
     * @brief Initializes the scene and its resources.
     *
     * This function is called when the game over scene is started. It initializes necessary resources, such as
     * font and text objects.
     */
    void OnInit() override;

    /**
     * @brief Destroys resources when the scene is destroyed.
     *
     * This function is called when transitioning away from the game over screen and is used to release any resources.
     */
    void OnDestroy() override;

    /**
     * @brief Starts the game over scene.
     *
     * This function is called when the game over scene is initiated, and it is used to set up any initial state for the scene.
     */
    void OnStart() override;

    /**
     * @brief Stops the game over scene and releases resources.
     *
     * This function is called when transitioning away from the game over screen and is used to clean up any resources.
     */
    void OnStop() override;

    /**
     * @brief Updates the game over scene every frame.
     *
     * This function updates the scene, including checking for restart conditions or input events.
     *
     * @param deltaTime The time elapsed since the last frame (in seconds)
     */
    void Update(float deltaTime) override;

    /**
     * @brief Draws the game over scene to the window.
     *
     * This function renders the game over screen, including the game over text and instructions for restarting.
     */
    void Draw() override;

    /**
     * @brief Handles user input during the game over scene.
     *
     * This function checks for any input from the player, such as mouse clicks or keyboard presses, to handle
     * the restart logic or transitions.
     *
     * @param deltaTime The time elapsed since the last frame (in seconds)
     */
    void HandleInput(float deltaTime) override;

private:
    // Scene Manager
    SceneManager& m_StateManager;  ///< The scene manager responsible for managing scene transitions

    // Window Renderer
    sf::RenderWindow& m_Window;  ///< The render window to display the game over scene

    // Text and Font for the Game Over screen
    sf::Font m_Font;  ///< The font used for displaying text on the game over screen
    sf::Text m_GameOverText;  ///< The text object that displays the "Game Over" message
    sf::Text m_TimeToRestart;  ///< The text object that displays the restart countdown message

    // Timer for handling the restart interval
    Timer m_Timer;  ///< The timer that tracks the time remaining before the game restarts

    // Time interval before restart
    float m_IntervalToRestartInSeconds;  ///< The interval (in seconds) before restarting the game
};