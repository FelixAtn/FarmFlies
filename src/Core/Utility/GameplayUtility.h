/*!
 * \file GameplayUtility.h
 *
 * \brief Utility functions for gameplay mechanics, including enemy spawning, collision detection, and projectile management.
 *
 * \author Felix Atanasescu - HE20830
 * \date April 2025
 */


#pragma once

// Forward declarations
class Spaceship;
class Projectile;
class Enemy;
enum class DifficultyLevel;


namespace GameplayUtility
{
	/**
   * @brief Spawns a set number of enemies in a grid pattern.
   *
   * This function spawns enemies at specific positions in the grid based on the difficulty level.
   * The number of rows and columns are calculated to fit the required number of enemies.
   * Each enemy is assigned a random generator for unique properties.
   *
   * @param enemies The vector of unique pointers to the enemy objects.
   * @param difficultyLevel The current difficulty level for the enemies.
   * @param rng Random number generator for enemy behavior.
   * @param numberOfEnemies Total number of enemies to spawn.
   * @param rows Number of rows in the grid.
   * @param columns Number of columns in the grid.
   * @param xSpacing Horizontal spacing between enemies.
   * @param ySpacing Vertical spacing between enemies.
   */
	void EnemySpawner(std::vector<std::unique_ptr<Enemy>>& enemies, const std::string& enemyFile, const std::string& projectileFile, DifficultyLevel difficultyLevel, RandomGenerator rng, int numberOfEnemies, int rows, int columns, int xSpacing, int ySpacing);


	/**
	 * @brief Checks for collisions between projectiles and enemies.
	 *
	 * Iterates over all projectiles and checks if they intersect with any of the enemies.
	 * When a collision is detected, the projectile and cow are deactivated, and the cow is removed from the game.
	 *
	 * @param enemies The vector of unique pointers to enemy enemies.
	 * @param projectiles The vector of unique pointers to projectile objects.
	 */
	void CheckEnemyCollision(std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Projectile>>& projectiles);

	    /**
     * @brief Checks if any cow projectiles hit the spaceship.
     *
     * Iterates over all enemies' projectiles and checks if they intersect with the spaceship.
     * If a collision is detected, the spaceship takes damage and the projectile is deactivated.
     *
     * @param enemies The vector of unique pointers to enemy enemies.
     * @param spaceship The spaceship object to check for collisions.
     */
	bool HasEnemyProjectileHitSpaceship(std::vector<std::unique_ptr<Enemy>>& enemies, Spaceship& spaceship);

	  /**
     * @brief Removes inactive projectiles from the game.
     *
     * Iterates through the projectiles and removes those that are no longer active.
     *
     * @param projectiles The vector of unique pointers to projectile objects.
     */
	void RemoveInactiveProjectiles(std::vector<std::unique_ptr<Projectile>>& projectiles);

	/**
	 * @brief Spawns a new projectile with the given properties.
	 *
	 * Creates a new projectile and adds it to the provided projectiles vector.
	 *
	 * @param projectiles The vector of unique pointers to projectile objects.
	 * @param projectileAssetFileName The file name of the projectile asset.
	 * @param startingPosition The position where the projectile will spawn.
	 * @param direction The direction in which the projectile will move (default is upwards).
	 */
	inline void SpawnProjectile(std::vector<std::unique_ptr<Projectile>>& projectiles, const std::string& projectileAssetFileName, const Vector2f& startingPosition, const Vector2f direction = { 0.0f, -1.0f })
	{
		projectiles.emplace_back(std::make_unique<Projectile>(projectileAssetFileName, startingPosition, direction));
	}

	    /**
     * @brief Attempts to shoot a projectile with a random cooldown.
     *
     * Rolls a random number and checks if the projectile should be shot based on the cooldown and random chance.
     * If the projectile is shot, it is added to the projectiles vector and the cooldown is reset.
     *
     * @param projectiles The vector of unique pointers to projectile objects.
     * @param deltaTime Time elapsed since the last update (used to handle cooldown).
     * @param projectileFile The file name for the projectile's texture.
     * @param spawnPos The position to spawn the projectile.
     * @param direction The direction in which the projectile will move.
     * @param shootCooldown The current cooldown time before shooting.
     * @param maxRollValue The maximum value the random roll can have.
     * @param requiredRollToShoot The required roll value to trigger shooting.
     * @param resetCooldownTime The cooldown time to reset after shooting.
     * @param rng Random generator used for determining if the projectile should be shot.
     */
	void TryShootWithRandomCooldown(std::vector<std::unique_ptr<Projectile>>& projectiles,
		float deltaTime,
		const std::string& projectileFile,
		const Vector2f& spawnPos,
		const Vector2f& direction,
		float& shootCooldown,
		int maxRollValue,
		int requiredRollToShoot,
		float resetCooldownTime,
		RandomGenerator& rng);

	/**
	 * @brief Loads a texture and assigns it to a sprite.
	 *
	 * Loads a texture from a file and assigns it to the provided sprite. If the texture fails to load, an error message is logged.
	 *
	 * @param texture The texture object to load the texture into.
	 * @param sprite The sprite object to assign the texture to.
	 * @param fileName The file name of the texture to load.
	 */
	void LoadTextureAndSprite(sf::Texture& texture, sf::Sprite& sprite, const std::string& fileName);


	/**
	 * @brief Loads background music from a file.
	 *
	 * Loads and plays background music from a given file. If loading the music fails, an error message is logged.
	 *
	 * @param music The music object to load the background music into.
	 * @param fileName The file name of the music to load.
	 */
	void LoadMusic(sf::Music& music, const std::string& fileName);
}
