/*!
 * \file Projectile.h
 *
 * \brief Contains the Projectile class and its related methods.
 *
 * The Projectile class represents a projectile in the game, such as a bullet or missile fired by an enemy or player.
 * It handles the movement, updating, and drawing of the projectile on the screen, as well as tracking its activation status.
 *
 * \author Felix Atanasescu - HE20830
 * \date April 2025
 */

#pragma once

 /**
  * @class Projectile
  * @brief Represents a projectile in the game, including its movement, appearance, and active status.
  *
  * The Projectile class handles the initialization of a projectile, its movement over time, and drawing it to the screen.
  * The projectile can be set to active or inactive, depending on whether it is in flight or has collided with an object.
  */
class Projectile
{
public:
	/**
	 * @brief Constructor to initialize the projectile with its texture, position, and direction.
	 *
	 * Initializes the projectile's texture from a file, sets its starting position, and gives it an initial direction
	 * of movement (by default, moving upwards).
	 *
	 * @param fileName The file path to the texture for the projectile.
	 * @param startingPosition The initial position of the projectile when it's fired.
	 * @param direction The direction the projectile will move in. Default is upwards.
	 */
	Projectile(const std::string& fileName, const Vector2f& startingPosition, const Vector2f& direction = { 0, -1 });

	/**
	 * @brief Updates the projectile's position and checks if it's still active.
	 *
	 * This function should be called every frame to update the projectile's state and position.
	 *
	 * @param deltaTime The time elapsed since the last frame (in seconds).
	 */
	void Update(float deltaTime);

	/**
	 * @brief Moves the projectile based on its direction and speed.
	 *
	 * Updates the position of the projectile by moving it in the specified direction.
	 *
	 * @param deltaTime The time elapsed since the last frame (in seconds).
	 */
	void MoveProjectile(float deltaTime);

	/**
	 * @brief Draws the projectile to the screen.
	 *
	 * Renders the projectile's sprite to the window at its current position.
	 *
	 * @param window The SFML render window to draw the sprite on.
	 */
	void Draw(sf::RenderWindow& window);

	/**
	 * @brief Gets the current position of the projectile.
	 *
	 * @return The current position of the projectile as a Vector2f.
	 */
	inline const Vector2f GetPosition() { return m_Sprite.getPosition(); }

	/**
	 * @brief Checks if the projectile is currently active.
	 *
	 * @return True if the projectile is active, false if it is inactive.
	 */
	inline const bool IsProjectileActive() const { return m_IsActive; }

	/**
	 * @brief Gets the activation status of the projectile.
	 *
	 * @return True if the projectile is active, false otherwise.
	 */
	inline bool GetStatus() const { return m_IsActive; }

	/**
	 * @brief Gets the bounding box of the projectile for collision detection.
	 *
	 * @return The global bounds of the projectile sprite, which can be used for collision detection.
	 */
	const sf::FloatRect& GetBounds() const { return m_Sprite.getGlobalBounds(); }

	/**
	 * @brief Sets the activation status of the projectile.
	 *
	 * Used to activate or deactivate the projectile, such as when it collides with an object or leaves the screen.
	 *
	 * @param isActive The desired activation status of the projectile.
	 */
	inline void SetStatus(bool isActive) { m_IsActive = isActive; }

private:
	// Texture and Sprite
	sf::Texture m_Texture; ///< The texture used for the projectile's sprite
	sf::Sprite m_Sprite;   ///< The sprite representing the projectile in the game

	// Properties
	Vector2f m_StartingPosition; ///< The initial starting position of the projectile
	Vector2f m_CurrentPosition;  ///< The current position of the projectile
	Vector2f m_Direction;       ///< The direction the projectile is moving in
	bool m_IsActive;            ///< Whether the projectile is currently active (in flight) or not
};
