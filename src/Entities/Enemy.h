
/*!
 * \file Enemy.h
 *
 * \brief Contains the Enemy class and its related methods.
 *
 * The Enemy class represents an enemy in the game. It manages the enemy's movement, shooting behavior, and interaction with projectiles.
 * The difficulty level affects how the enemy behaves, such as how often it shoots or how it moves.
 * The class is responsible for updating the enemy's state and drawing it on the screen.
 *
 * \author Felix Atanasescu - HE20830
 * \date April 2025
 */
#pragma once
#include "Projectile.h"

 /**
  * @enum DifficultyLevel
  * @brief Represents the different difficulty levels in the game.
  *
  * The difficulty level impacts the behavior of enemies, such as their shooting frequency, movement speed,
  * and chance to hit the player. The levels range from VERY_EASY to INSANE.
  */
enum class DifficultyLevel
{
	VERY_EASY = 0, ///< Very easy difficulty level
	EASY,          ///< Easy difficulty level
	NORMAL,        ///< Normal difficulty level
	HARD,          ///< Hard difficulty level
	VERY_HARD,     ///< Very hard difficulty level
	INSANE         ///< Insane difficulty level
};

/**
 * @class Enemy
 * @brief Represents an enemy in the game, handling movement, shooting, and interaction with projectiles.
 *
 * The Enemy class defines an enemy's behaviors, including its movement, the projectiles it shoots, and
 * its interaction with the player. The difficulty level of the enemy influences its actions. This class
 * handles the periodic updating of the enemy's state, such as its position and shooting behavior.
 */
class Enemy
{
public:
	/**
	 * @brief Constructor that initializes an enemy with specific properties.
	 *
	 * Initializes the enemy using a texture file, a projectile texture file, a difficulty level, and a random number generator.
	 * The difficulty level will determine the enemy's behavior, such as shooting chances and movement speed.
	 *
	 * @param enemyFile The texture file for the enemy's sprite.
	 * @param projectileFile The texture file for the enemy's projectiles.
	 * @param difficultyLevel The difficulty level that influences the enemy's behavior.
	 * @param rng The random number generator used for determining shooting behavior.
	 */
	Enemy(const std::string& enemyFile, const std::string& projectileFile, DifficultyLevel difficultyLevel, RandomGenerator& rng);

	/**
	 * @brief Destructor that cleans up resources used by the enemy.
	 */
	~Enemy();

	/**
	 * @brief Updates the enemy's state.
	 *
	 * This function should be called each frame to update the enemy's behavior, such as its movement and shooting.
	 *
	 * @param deltaTime The time elapsed since the last frame (in seconds).
	 */
	void Update(float deltaTime);

	/**
	 * @brief Draws the enemy's sprite to the window.
	 *
	 * Renders the enemy sprite to the window at its current position.
	 *
	 * @param window The SFML render window to draw the sprite on.
	 */
	void Draw(sf::RenderWindow& window);

	// Getters

	/**
	 * @brief Gets the list of projectiles fired by the enemy.
	 *
	 * @return A constant reference to the vector of projectiles.
	 */
	inline const std::vector<std::unique_ptr<Projectile>>& GetProjectiles() const { return m_Projectiles; }

	/**
	 * @brief Gets the current position of the enemy.
	 *
	 * @return The current position of the enemy as a Vector2f.
	 */
	inline Vector2f GetPosition() { return m_Sprite.getPosition(); }

	/**
	 * @brief Gets the sprite of the enemy.
	 *
	 * @return The reference to the enemy's sprite.
	 */
	inline sf::Sprite& GetSprite() { return m_Sprite; }

	/**
	 * @brief Checks if the enemy is alive.
	 *
	 * @return True if the enemy is alive, false if dead.
	 */
	inline bool IsAlive() const { return m_IsAlive; }

	// Setters

	/**
	 * @brief Sets the position of the enemy.
	 *
	 * @param position The new position to set for the enemy.
	 */
	inline void SetPosition(const Vector2f& position) { m_Sprite.setPosition(position); }

	/**
	 * @brief Sets the alive status of the enemy.
	 *
	 * @param isAlive Whether the enemy is alive or not.
	 */
	inline void SetStatus(bool isAlive) { m_IsAlive = isAlive; }

private:
	/**
	 * @brief Updates the enemy's projectiles, checking for collisions and updating their positions.
	 *
	 * This function is called within Update to handle projectile behavior.
	 *
	 * @param deltaTime The time elapsed since the last frame (in seconds).
	 */
	void UpdateProjectiles(float deltaTime);

	/**
	 * @brief Processes the enemy's shooting behavior.
	 *
	 * Determines if the enemy should shoot based on its difficulty level and the time passed.
	 *
	 * @param deltaTime The time elapsed since the last frame (in seconds).
	 * @param baseMaxChanceToHit The base maximum chance for the enemy to hit the player.
	 * @param baseRequiredRollToShoot The base required roll for the enemy to shoot.
	 * @param baseCooldownDuration The base cooldown duration between shots.
	 */
	void ProcessShooting(float deltaTime, int baseMaxChanceToHit, int baseRequiredRollToShoot, float baseCooldownDuration);

	/**
	 * @brief Handles the enemy's movement behavior.
	 *
	 * Updates the enemy's position based on its movement pattern.
	 *
	 * @param deltaTime The time elapsed since the last frame (in seconds).
	 */
	void OnMove(float deltaTime);

	/**
	 * @brief Gets the vertical movement for the enemy based on a speed and direction.
	 *
	 * Returns the vertical movement offset for the enemy's position.
	 *
	 * @param deltaTime The time elapsed since the last frame (in seconds).
	 * @param verticalSpeed The vertical movement speed of the enemy.
	 * @return The vertical movement offset for this frame.
	 */
	float GetVerticalMovement(float deltaTime, float verticalSpeed = 50.0f) const { return verticalSpeed * m_VerticalDirection * deltaTime; }

	/**
	 * @brief Gets the horizontal movement for the enemy based on a sine wave pattern.
	 *
	 * Returns the horizontal movement offset for the enemy's position.
	 *
	 * @param deltaTime The time elapsed since the last frame (in seconds).
	 * @param amplitude The amplitude of the horizontal movement.
	 * @param frequency The frequency of the sine wave movement.
	 * @return The horizontal movement offset for this frame.
	 */
	float GetHorizontalMovement(float deltaTime, float amplitude = 50.0f, float frequency = 2.0f) const { return amplitude * std::sin(frequency * m_TimeElapsed) * deltaTime; }

	/**
	 * @brief Reverses the movement direction when the enemy reaches a movement limit.
	 *
	 * This function is called to reverse the enemy's movement direction, ensuring it stays within bounds.
	 *
	 * @param verticalDirection The vertical movement direction to reverse if necessary.
	 * @param movementLimit The limit beyond which the movement direction should reverse.
	 */
	void ReverseMovement(float& verticalDirection, float movementLimit);

private:
	// Random Number Generator
	RandomGenerator m_RNG; ///< The random number generator used to control shooting behavior

	// Texture and Sprite
	sf::Texture m_Texture; ///< The texture used for the enemy's sprite
	sf::Sprite m_Sprite;   ///< The sprite representing the enemy in the game

	// Projectiles
	std::string m_ProjectileTextureFile; ///< The file path for the enemy's projectile texture
	std::vector<std::unique_ptr<Projectile>> m_Projectiles; ///< The list of projectiles fired by the enemy

	// Enemy Properties
	Vector2f m_CurrentPosition; ///< The current position of the enemy
	float m_ShootCooldown; ///< The cooldown between consecutive shots
	float m_VerticalDirection; ///< The direction of vertical movement
	float m_TimeElapsed; ///< Time elapsed for the enemy's movement pattern
	DifficultyLevel m_Difficulty; ///< The difficulty level of the enemy
	bool m_IsAlive = true; ///< Indicates whether the enemy is alive
};