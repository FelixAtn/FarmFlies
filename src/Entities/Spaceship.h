/*!
 * \file Spaceship.h
 *
 * \brief Contains the Spaceship class and its related methods.
 *
 * The Spaceship class represents the player's spaceship in the game. It is responsible for updating the spaceship's
 * state, handling projectile shooting, and drawing the spaceship and its projectiles to the screen.
 *
 * \author Felix Atanasescu - HE20830
 * \date April 2025
 */

#pragma once
#include "Projectile.h"
class Enemy;

 /**
  * @class Spaceship
  * @brief Represents the player's spaceship in the game, managing movement, shooting, and state updates.
  *
  * The Spaceship class handles the functionality of the spaceship, including firing projectiles, updating its position,
  * checking its alive status, and drawing it to the screen. It also manages the spaceship's projectiles and updates their
  * states.
  */
class Spaceship
{
public:
	/**
	 * @brief Default constructor for the Spaceship class.
	 *
	 * Initializes the spaceship with default values and loads the necessary texture for the spaceship.
	 */
	Spaceship();

	/**
	 * @brief Updates the spaceship's state and actions.
	 *
	 * This function should be called each frame to update the spaceship's state, such as its position, firing projectiles,
	 * and any necessary interactions with other game entities like enemies.
	 *
	 * @param window The SFML render window to calculate and update positions.
	 * @param cows A vector of unique pointers to enemies (or "cows" as they may be called in this context).
	 * @param deltaTime The time elapsed since the last frame (in seconds).
	 */
	void Update(sf::RenderWindow& window, std::vector<std::unique_ptr<Enemy>>& cows, float deltaTime);

	/**
	 * @brief Draws the spaceship and its projectiles to the screen.
	 *
	 * Renders the spaceship and its active projectiles to the window.
	 *
	 * @param window The SFML render window to draw the spaceship and projectiles on.
	 */
	void Draw(sf::RenderWindow& window);

	/**
	 * @brief Gets the list of projectiles currently fired by the spaceship.
	 *
	 * @return A reference to the vector containing unique pointers to the spaceship's projectiles.
	 */
	std::vector<std::unique_ptr<Projectile>>& GetProjectiles() { return m_Projectiles; }

	/**
	 * @brief Gets the spaceship's sprite.
	 *
	 * @return A reference to the spaceship's sprite, used for drawing and positioning.
	 */
	inline sf::Sprite& GetSprite() { return m_Sprite; }

	/**
	 * @brief Checks if the spaceship is alive.
	 *
	 * @return True if the spaceship is alive, false if it has been destroyed.
	 */
	inline bool IsAlive() const { return m_IsAlive; }

	/**
	 * @brief Resets the spaceship's state to "alive."
	 *
	 * This function is used to reset the spaceship to a state where it is alive, such as after respawning.
	 */
	inline const void Reset() { m_IsAlive = true; }

	/**
	 * @brief Handles the spaceship being hit by an enemy or obstacle.
	 *
	 * This function is called when the spaceship is hit, and it will handle actions like reducing health or setting
	 * the spaceship to an "inactive" state.
	 */
	void OnHit();

private:
	/**
	 * @brief Handles the spaceship firing a projectile.
	 *
	 * This function is responsible for instantiating new projectiles and adding them to the spaceship's list of projectiles.
	 */
	void OnProjectileShoot();

	/**
	 * @brief Updates the state of all projectiles fired by the spaceship.
	 *
	 * This function should be called every frame to update the projectiles' positions and handle any necessary logic,
	 * such as collisions or whether the projectiles should be deactivated.
	 *
	 * @param deltaTime The time elapsed since the last frame (in seconds).
	 */
	void UpdateProjectiles(float deltaTime);

	/**
	 * @brief Calculates and updates the spaceship's position based on the cursor's position.
	 *
	 * This function updates the spaceship's position according to the cursor or player input.
	 *
	 * @param window The SFML render window used to track the cursor position.
	 */
	void CalculateAndUpdateCursorPosition(sf::RenderWindow& window);

	/**
	 * @brief Draws all active projectiles to the window.
	 *
	 * This function is responsible for rendering each projectile fired by the spaceship.
	 *
	 * @param window The SFML render window used to draw the projectiles.
	 */
	void DrawProjectile(sf::RenderWindow& window);

	/**
	 * @brief Draws the spaceship to the window.
	 *
	 * This function is responsible for rendering the spaceship sprite to the screen.
	 *
	 * @param window The SFML render window used to draw the spaceship.
	 */
	void DrawSpaceship(sf::RenderWindow& window);

private:
	// Texture and Sprite for the spaceship
	sf::Texture m_Texture; ///< The texture used for the spaceship's sprite
	sf::Sprite m_Sprite;   ///< The sprite representing the spaceship in the game
	Vector2f m_Position;   ///< The current position of the spaceship

	// Projectiles fired by the spaceship
	std::vector<std::unique_ptr<Projectile>> m_Projectiles; ///< List of projectiles fired by the spaceship

	// State
	bool m_IsAlive; ///< Whether the spaceship is alive or destroyed
};

