/*!
 * \file GameInstance.h
 *
 * \brief Contains the GameInstance class that manages the game loop and initialization of game resources.
 *
 * The `GameInstance` class is responsible for initializing and running the core game loop, including loading game assets,
 * managing game states, handling events and input, updating the game logic, and drawing to the window.
 *
 * \author Felix Atanasescu - HE20830
 * \date April 2025
 */
#pragma once

 /**
  * @class GameInstance
  * @brief Manages the game loop, resource loading, and game states.
  *
  * The `GameInstance` class provides the main functionality for running the game, from initializing resources (textures, music,
  * maps, etc.), handling input and events, updating game logic, and rendering the game objects to the window. It contains the core
  * game loop and manages the state transitions.
  */
class GameInstance
{
public:
    /**
     * @brief Constructs the game instance.
     *
     * Initializes all necessary members and prepares the game for execution.
     */
    GameInstance();

    /**
     * @brief Destroys the game instance.
     *
     * Releases any allocated resources and performs clean-up operations.
     */
    ~GameInstance() = default;

    /**
     * @brief Starts the game loop and runs the game.
     *
     * This function is called to start the main game loop, which repeatedly updates, draws, and processes input for the game.
     */
    void Run();

private:
    /**
     * @brief Initializes game resources.
     *
     * This function loads all the necessary resources for the game, including textures, sounds, and maps.
     */
    void InitResources();

    /**
     * @brief Initializes the game window.
     *
     * This function creates the SFML window for the game and sets up any initial window properties.
     */
    void InitWindow();

    /**
     * @brief Initializes game states.
     *
     * This function sets up the initial state of the game, including any active game scenes or menus.
     */
    void InitGameStates();

    /**
     * @brief Handles window events.
     *
     * This function processes events such as window resizing, closing, or focus changes.
     */
    void HandleEvent();

    /**
     * @brief Handles player input.
     *
     * This function checks for user input (keyboard, mouse, etc.) and processes it accordingly.
     */
    void HandleInput();

    /**
     * @brief Updates the game logic.
     *
     * This function updates all game objects and entities, processes game mechanics, and advances the game state.
     */
    void Update();

    /**
     * @brief Draws the game objects to the window.
     *
     * This function renders all game objects to the SFML window.
     */
    void Draw();

private:
    // The SFML window for rendering
    sf::RenderWindow m_Window;  ///< The window used to display the game

    // The scene manager responsible for managing game states
    SceneManager m_StateManager;  ///< The scene manager used to transition between game scenes

    // Event handler for window events
    sf::Event m_Event;  ///< The event object used to manage window events

    // Timer for tracking deltaTime
    Timer m_Timer;  ///< The timer object used to track elapsed time for game updates

    // Clock for tracking the overall game time
    sf::Clock m_Clock;  ///< The clock used to track real time for the game loop

    // Time per frame (deltaTime)
    float m_deltaTime;  ///< The time elapsed between each frame
};

