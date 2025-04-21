
/*!
 * \file InputManager.h
 *
 * \brief Contains the KeyBind enum and InputManager singleton class.
 *
 * The InputManager class handles input detection for both keyboard and mouse.
 * It uses a bitset to track the current and previous state of keys/buttons.
 * This system allows the game to check for key presses and key holds efficiently.
 *
 * \author Felix Atanasescu - HE20830
 * \date April 2025
 */

#pragma once

constexpr uint32_t MAX_KEYS = 650; ///< Maximum number of keys supported

/**
 * @enum KeyBind
 * @brief Represents custom game actions mapped to keyboard or mouse inputs.
 *
 * These enums are mapped manually in the Update functions.
 * They abstract away specific SFML keys to allow rebinding in the future.
 */

enum class KeyBind
{
	Pause,        ///< Pauses the game (mapped to Escape key)
	Shoot,        ///< Fires a projectile or triggers an attack (mapped to Left Mouse)
	Right_click,  ///< Executes a secondary action (mapped to Right Mouse)

};

/**
 * @class InputManager
 * @brief Singleton class responsible for handling player input.
 *
 * Tracks key/button states using bitsets to efficiently determine
 * whether a key is held down or was just pressed during the frame.
 *
 * Supports:
 * - Detecting key presses (single-frame)
 * - Detecting key holds (multi-frame)
 * - Abstracting low-level SFML input to game-level actions
 */
class InputManager
{
public:
	/**
	* @brief Retrieves the singleton instance of the InputManager.
	*
	* @return Reference to the global InputManager instance.
	*/
	static InputManager& Get()
	{
		static InputManager instance;
		return instance;
	}

	/**
	 * @brief Updates the input state each frame.
	 *
	 * Should be called once per frame. Stores the previous state,
	 * clears current state, and polls new keyboard/mouse inputs.
	 *
	 * @param deltaTime Time elapsed since the last frame (currently unused).
	 */
	void Update(float deltaTime);

	/**
	 * @brief Checks if a specific key was just pressed.
	 *
	 * Returns true only on the frame the key is initially pressed.
	 *
	 * @param key The logical game key to check.
	 * @return True if the key was pressed this frame, false otherwise.
	 */
	bool IsKeyPress(KeyBind key);

	/**
	 * @brief Checks if a specific key is currently held down.
	 *
	 * Returns true if the key is being pressed continuously.
	 *
	 * @param key The logical game key to check.
	 * @return True if the key is down, false if not.
	 */
	bool IsKeyDown(KeyBind key);

private:
	/**
	* @brief Private constructor to enforce singleton pattern.
	*/
	InputManager() = default;

	// Deleted copy constructor and assignment operator
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	/**
	 * @brief Polls SFML keyboard state and sets flags accordingly.
	 *
	 * Maps specific SFML keys to game-level KeyBind enums.
	 */
	void UpdateKeyboard();

	/**
	 * @brief Polls SFML mouse button state and sets flags accordingly.
	 *
	 * Maps mouse buttons to KeyBind enums.
	 */
	void UpdateMouse();

private:
	std::bitset<MAX_KEYS> m_CurrentKey;   ///< Bitset for current frame key states
	std::bitset<MAX_KEYS> m_PreviousKey = 0; ///< Bitset for previous frame key states
};

