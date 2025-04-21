/*!
 * \file LevelTwo.h
 *
 * \brief Contains the LevelTwo class for managing the second level of the game.
 *
 * The `LevelTwo` class is responsible for the second level of the game, handling initialization, updating, and drawing
 * the level's entities and objects. This class also manages transitions in and out of the level, as well as updating
 * and rendering the scene.
 *
 * \author Felix Atanasescu - HE20830
 * \date April 2025
 */

#pragma once

 /**
  * @class LevelTwo
  * @brief Represents the second level of the game, including scene management and rendering.
  *
  * The `LevelTwo` class manages the gameplay during the second level of the game. It implements the required functions
  * for initializing the level, handling scene transitions, and updating the entities within the scene.
  */
class LevelTwo final : public IGameScene
{
public:
    /**
     * @brief Constructs the LevelTwo scene with a reference to the scene manager and window.
     *
     * @param sceneManager The scene manager responsible for managing scene transitions
     * @param window The SFML render window to draw the scene on
     */
    LevelTwo(SceneManager& sceneManager, sf::RenderWindow& window);

    /**
     * @brief Initializes the scene and its resources.
     *
     * This function is called to initialize necessary resources for the level when the scene starts.
     */
    void OnInit() override;

    /**
     * @brief Destroys resources when the scene is destroyed.
     *
     * This function is called to release resources when the level is no longer in use.
     */
    void OnDestroy() override;

    /**
     * @brief Starts the level scene, preparing necessary resources.
     *
     * This function is called when the level is initialized and is used to start gameplay and set up any initial state.
     */
    void OnStart() override;

    /**
     * @brief Stops the level scene, releasing resources.
     *
     * This function is called when transitioning away from the level and is used to clean up any resources.
     */
    void OnStop() override;

    /**
     * @brief Updates the level scene every frame.
     *
     * This function updates the scene elements (such as entities) each frame. It is called in the game loop to keep
     * the level's state updated.
     *
     * @param deltaTime The time elapsed since the last frame (in seconds)
     */
    void Update(float deltaTime) override;

    /**
     * @brief Draws the level scene to the window.
     *
     * This function is called every frame to render all of the elements in the level, including objects,
     * backgrounds, and UI elements.
     */
    void Draw() override;

private:
    // Scene Manager
    SceneManager& m_SceneManager;  ///< The scene manager responsible for managing scene transitions

    // Window Renderer
    sf::RenderWindow& m_Window;  ///< The render window to display the level
};