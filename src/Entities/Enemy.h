#pragma once
#include "Projectile.h"

enum class DifficultyLevel
{
	VERY_EASY = 0,
	EASY,
	NORMAL,
	HARD,
	VERY_HARD,
	INSANE
};

class Enemy
{
public:
	// Constructor
	Enemy(const std::string& enemyFile, const std::string& projectileFile, DifficultyLevel difficultyLevel, RandomGenerator& rng);
	
	// Destructor 
	~Enemy();
	// Core
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	// Getters
	inline const std::vector<std::unique_ptr<Projectile>>& GetProjectiles() const { return m_Projectiles; }
	inline Vector2f GetPosition() { return m_Sprite.getPosition(); }
	inline sf::Sprite& GetSprite() { return m_Sprite; }
	inline bool IsAlive() const { return m_IsAlive; }

	// Setters
	inline void SetPosition(const Vector2f& position){ m_Sprite.setPosition(position); }
	inline void SetStatus(bool isAlive) {m_IsAlive = isAlive;}

private:
	// Projectile Update
	void UpdateProjectiles(float deltaTime);

	// Process Shooting
	void ProcessShooting(float deltaTime, int baseMaxChanceToHit, int baseRequiredRollToShoot, float baseCooldownDuration);

	// Actions
	void OnMove(float deltaTime);

	// Process Movement
	float GetVerticalMovement(float deltaTime, float verticalSpeed = 50.0f) const { return verticalSpeed * m_VerticalDirection * deltaTime; }
	float GetHorizontalMovement(float deltaTime, float aplitude = 50.0f, float frequency = 2.0f) const { return aplitude * std::sin(frequency * m_TimeElapsed) * deltaTime; }
	void ReverseMovement(float& verticalDirection, float movementLimit);

private:
	// Random Number Generator
	RandomGenerator m_RNG;

	// Texture
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	// Projectiles
	std::string m_ProjectileTextureFile;
	std::vector<std::unique_ptr<Projectile>> m_Projectiles;
	
	// Properties
	Vector2f m_CurrentPosition;
	float m_ShootCooldown;
	float m_VerticalDirection;
	float m_TimeElapsed;
	DifficultyLevel m_Difficulty;
	bool m_IsAlive = true;

};

