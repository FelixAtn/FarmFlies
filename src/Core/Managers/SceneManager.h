
/*!
 * \file SceneManager.h
 *
 * \brief Contains the SceneID enum, IGameScene interface, and SceneManager class.
 *
 * These elements together manage the scene lifecycle in a game.
 * Scenes can be main menus, levels, game over screens, etc.
 * The SceneManager enables adding, switching, and removing scenes at runtime.
 *
 * \author Felix Atanasescu - HE20830
 * \date April 2025
 */

#pragma once


enum SceneID
{
	MAIN_MENU = 0,  ///< Main menu scene
	LEVEL_ONE,      ///< First level of the game
	LEVEL_TWO,      ///< Second level of the game
	GAME_OVER,      ///< Game over screen
	CREDITS         ///< Credits screen   
};

/**
 * @class IGameScene
 * @brief Interface for all game scenes.
 *
 * This abstract base class defines the lifecycle of a game scene.
 * Each scene must implement update and draw behavior.
 * Optional lifecycle hooks include initialization, destruction, start, and stop methods.
 */
class IGameScene
{
public:
	/**
	 * @brief Virtual destructor.
	 *
	 * Ensures proper cleanup of derived classes.
	 */

	virtual ~IGameScene() = default;

	/**
	 * @brief Called once when the scene is created.
	 *
	 * Useful for resource loading or setup.
	 */
	virtual void OnInit() {};

	/**
	* @brief Called once when the scene is being destroyed.
	*
	* Used to free resources and perform cleanup.
	*/
	virtual void OnDestroy() {};

	/**
   * @brief Called every time the scene becomes the active one.
   *
   * Ideal for resetting values or playing music.
   */
	virtual void OnStart() {};

	/**
   * @brief Called every time the scene is replaced by another.
   *
   * Can be used to pause timers, animations, etc.
   */
	virtual void OnStop() {};

	/**
   * @brief Updates the scene logic.
   *
   * This is a pure virtual method that must be implemented by all scenes.
   *
   * @param deltaTime Time elapsed since the last frame, in seconds.
   */
	virtual void Update(float deltaTime) = 0;

	/**
  * @brief Draws the scene content to the screen.
  *
  * Must be implemented by each scene to render its visual content.
  */
	virtual void Draw() = 0;

	/**
	* @brief Handles input events for the scene.
	*
	* Can be overridden for input-specific logic.
	*
	* @param deltaTime Optional time delta for handling input (default = 0).
	*/
	virtual void HandleInput(float deltaTime = 0) {};
};

/**
 * @class SceneManager
 * @brief Manages game scenes, allowing for seamless transitions between them.
 *
 * This class stores and manages multiple game scenes, supporting operations such as:
 * - Adding new scenes
 * - Switching to a different scene
 * - Removing scenes from memory
 * - Updating and drawing the current active scene
 */
class SceneManager
{
public:
	/**
   * @brief Destructor.
   *
   * Ensures proper cleanup of all stored scenes.
   */
	~SceneManager();

	/**
   * @brief Updates the currently active scene.
   *
   * Calls the Update method of the current scene.
   *
   * @param deltaTime Time elapsed since the last frame.
   */
	void Update(float deltaTime);

	/**
   * @brief Draws the currently active scene.
   *
   * Forwards the drawing responsibility to the active scene.
   *
   * @param window Reference to the SFML window where content will be drawn.
   */
	void Draw(sf::RenderWindow& window);

	/**
	   * @brief Handles input for the active scene.
	   *
	   * Delegates input handling to the current scene.
	   *
	   * @param deltaTime Time elapsed since the last frame.
	   */
	void HandleInput(float deltaTime);

	/**
	 * @brief Adds a new scene to the manager.
	 *
	 * Associates a scene with a unique SceneID. Throws if the ID already exists.
	 *
	 * @param pushingState A shared pointer to the scene to be added.
	 * @param allocationID The ID used to reference this scene.
	 */
	void Add(std::shared_ptr<IGameScene> pushingState, SceneID allocationID);

	/**
   * @brief Switches the currently active scene.
   *
   * Calls OnStop() on the current scene and OnStart() on the new one.
   *
   * @param stateID The ID of the scene to switch to.
   */
	void Switch(SceneID stateID);

	/**
	   * @brief Removes a scene from the manager.
	   *
	   * Frees memory and invalidates the SceneID. Safe to call on inactive scenes.
	   *
	   * @param stateID The ID of the scene to remove.
	   */
	void Remove(SceneID stateID);

	/**
	 * @brief Prints all currently stored scene IDs.
	 *
	 * Primarily used for debugging purposes. Outputs to the log.
	 */
	void PrintStates() const {
		for (const auto& [id, state] : m_States) {
			Log::Print("State ID: " + std::to_string(id), LogLevel::INFO);
		}
	}

private:
	/**
	 * @brief Validates that a SceneID is not already in use.
	 *
	 * Throws an error if the ID already exists in the scene map.
	 *
	 * @param ID The SceneID to validate.
	 */
	void Validate(SceneID ID);

private:
	std::unordered_map<SceneID, std::shared_ptr<IGameScene>> m_States;  ///< All registered scenes
	std::shared_ptr<IGameScene> m_Current;                              ///< The currently active scene
	int m_CurrentID;                                                    ///< ID of the active scene
};

