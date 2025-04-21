#include "stdafx.h"
#include "GameplayUtility.h"
#include "Entities/Spaceship.h"
#include "Entities/Enemy.h"
#include "Entities/Projectile.h"

// Spawns a specified number of enemies and positions them in a grid formation.
void GameplayUtility::EnemySpawner(std::vector<std::unique_ptr<Enemy>>& enemies, const std::string& enemyFile, const std::string& projectileFile, DifficultyLevel difficultyLevel, RandomGenerator rng, int numberOfEnemies, int rows, int columns, int xSpacing, int ySpacing)
{
	// Validate input parameters. Exit if any parameter is invalid.
	if (numberOfEnemies <= 0 || rows <= 0 || columns <= 0 || xSpacing <= 0 || ySpacing <= 0)
	{
		Log::Print("Invalid input parameters.");
		return;  // Exit if any parameter is invalid
	}

	// Adjust the number of rows needed to fit all the enemies
	rows = (numberOfEnemies + columns - 1) / columns;

	// Reserve space in the vector to improve performance
	enemies.reserve(numberOfEnemies); // Reserve memory for efficiency
	int index = 0;

	// Loop through the grid positions (rows and columns) and spawn enemies
	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			// If the number of enemies already spawned reaches the desired number, exit the loop
			if (index >= numberOfEnemies) return;  // Stop if we reached the desired number of enemies

			// Create a new enemy based on the difficulty level and RNG for variation
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(enemyFile, projectileFile, difficultyLevel, rng);

			// Calculate the position of the enemy in the grid
			float xPos = static_cast<float>(x * xSpacing);
			float yPos = static_cast<float>(y * ySpacing);

			// Set the position of the newly created enemy
			enemy->SetPosition(Vector2f(xPos, yPos));  // Set position based on the grid

			// Add the enemy to the vector of enemies
			enemies.emplace_back(std::move(enemy));  // Add to the vector

			// Increment the index
			++index;
		}
	}
}

// Checks for collisions between enemies and projectiles, and handles their interaction
void GameplayUtility::CheckEnemyCollision(std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Projectile>>& projectiles)
{
	// Iterate over all projectiles to check for collisions
	for (auto& projectile : projectiles)
	{
		// Skip inactive projectiles (those not currently in use)
		if (!projectile->IsProjectileActive())
		{
			// Skip inactive projectiles
			continue;
		}

		// Get the global bounding box of the projectile
		sf::FloatRect projBounds = projectile->GetBounds();

		// Iterate over the enemies to check for collisions with each
		for (auto it = enemies.begin(); it != enemies.end(); /* no increment here */)
		{
			auto& enemy = *it;

			// Skip dead enemies
			if (!enemy->IsAlive())
			{
				++it;
				continue;
			}

			sf::FloatRect enemyBounds = enemy->GetSprite().getGlobalBounds();
			if (projBounds.intersects(enemyBounds))  // Check for intersection
			{
				enemy->SetStatus(false);  // Mark enemy as dead
				projectile->SetStatus(false);  // Deactivate projectile

				// Remove dead enemy from the vector using a lambda
				it = std::remove_if(enemies.begin(), enemies.end(), [](const std::unique_ptr<Enemy>& enemy)
					{
						return !enemy->IsAlive();
					});
				enemies.erase(it, enemies.end());  // Erase the dead enemies

				break;  // Once collision is detected, no need to check further for this projectile
			}
			else
			{
				++it;  // Only increment the iterator if the enemy is not dead
			}
		}
	}
}

// Checks if any projectiles fired by enemies hit the spaceship, and handles the impact
bool GameplayUtility::HasEnemyProjectileHitSpaceship(std::vector<std::unique_ptr<Enemy>>& enemies, Spaceship& spaceship)
{
	// Get the global bounding box of the spaceship
	const sf::FloatRect& spaceshipHitbox = spaceship.GetSprite().getGlobalBounds();

	// Iterate over the enemies
	for (auto& enemy : enemies)
	{
		// Skip dead enemies
		if (!enemy->IsAlive())
		{
			continue;
		}

		// Iterate over all projectiles fired by the enemy
		auto& projectiles = enemy->GetProjectiles();
		for (auto& projectile : projectiles)
		{
			// Skip inactive projectiles
			if (!projectile->GetStatus())
			{
				continue;
			}

			// Check if the projectile intersects with the spaceship's hitbox
			if (projectile->GetBounds().intersects(spaceshipHitbox))
			{
				// If the spaceship is hit, trigger the spaceship's OnHit function (damage/death)
				spaceship.OnHit();                   // Trigger damage/death
				projectile->SetStatus(false);         // Mark for removal
				return true; // Once a hit is detected, no need to check further for this projectile
			}
		}
	}

	return false;
}

// Removes inactive projectiles from the list of projectiles
void GameplayUtility::RemoveInactiveProjectiles(std::vector<std::unique_ptr<Projectile>>& projectiles)
{
	// Remove all projectiles that are inactive from the vector using a lambda function
	projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
		[](const std::unique_ptr<Projectile>& p) { return !p->IsProjectileActive(); }),
		projectiles.end());
}

// Attempts to shoot a projectile with a random cooldown. If the random roll succeeds, the projectile is spawned.
void GameplayUtility::TryShootWithRandomCooldown(std::vector<std::unique_ptr<Projectile>>& projectiles, float deltaTime, const std::string& projectileFile, const Vector2f& spawnPos, const Vector2f& direction, float& shootCooldown, int maxRollValue, int requiredRollToShoot, float resetCooldownTime, RandomGenerator& rng)
{
	// Reduce the cooldown by the time passed since the last frame
	shootCooldown -= deltaTime;

	// If the cooldown is still active, exit the function without shooting
	if (shootCooldown > 0.f)
	{
		return;
	}

	// Generate a random roll between 1 and maxRollValue
	int roll = rng.GetRandomInt(1, maxRollValue);
	if (roll <= requiredRollToShoot)
	{
		// Shoot a new projectile if the random roll is successful
		projectiles.emplace_back(std::make_unique<Projectile>(projectileFile, spawnPos, direction));

		// Reset the cooldown after shooting
		shootCooldown = resetCooldownTime;
	}
	else
	{
		// If the roll fails, set a short retry delay before trying again
		shootCooldown = 0.01f; // short retry delay
	}
}

