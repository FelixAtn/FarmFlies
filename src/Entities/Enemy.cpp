#include "stdafx.h"
#include "Enemy.h"
#include "Core/Utility/strings.h"
#include "Core/Utility/GameplayUtility.h"
#include "Core/Managers/SoundManager.h"
#include "Projectile.h"

static SoundManager g_SoundManager;

Enemy::Enemy(const std::string& enemyFile, const std::string& projectileFile, DifficultyLevel difficultyLevel, RandomGenerator& rng)
	: m_TimeElapsed(0.0f)
	, m_VerticalDirection(-1.0f)
	, m_CurrentPosition(0.0f, 0.0f)
	, m_IsAlive(true)
	, m_ShootCooldown(0.0f)
	, m_Difficulty(difficultyLevel)
	, m_ProjectileTextureFile(projectileFile)
	, m_RNG(rng)
{
	m_Texture.loadFromFile(enemyFile);
	m_Sprite.setTexture(m_Texture);
	m_ShootCooldown = rng.GetRandomFloat(0.f, 1.f);

	// Load the sound into the SoundManager
	g_SoundManager.LoadSound("cowDeath", COW_DEATH);  // Load death sound
}

Enemy::~Enemy()
{
	g_SoundManager.PlaySound("cowDeath");
}

void Enemy::Update(float deltaTime)
{
	OnMove(deltaTime);
	ReverseMovement(m_VerticalDirection, 200.0f); // If the max limit is hit, reverse the direction
	ProcessShooting(deltaTime, 100, 10, 1.0f);
	UpdateProjectiles(deltaTime);
	GameplayUtility::RemoveInactiveProjectiles(m_Projectiles);
}

void Enemy::Draw(sf::RenderWindow& window)
{
	if (m_IsAlive)
	{
		window.draw(m_Sprite);
	}

	for (auto& projectile : m_Projectiles)
	{
		projectile->Draw(window);
	}
}

void Enemy::OnMove(float deltaTime)
{
	m_TimeElapsed += deltaTime;

	// Vertical movement and set the new position
	float verticalMovement = GetVerticalMovement(deltaTime);
	float horizontalMovement = GetHorizontalMovement(deltaTime);
	m_Sprite.move(horizontalMovement, verticalMovement);
}

void Enemy::UpdateProjectiles(float deltaTime)
{
	// iterate through all cow projectiles
	for (const auto& projectile : m_Projectiles)
	{
		// Update all cow projectiles
		projectile->Update(deltaTime);
	}
}

void Enemy::ReverseMovement(float& verticalDirection, float movementLimit)
{
	// Reverse direction if limits are hit
	sf::Vector2f pos = m_Sprite.getPosition();
	if (pos.y > movementLimit)
	{
		verticalDirection = -1.f;
	}
	else if (pos.y < 0)
	{
		verticalDirection = 1.f;
	}
}

void Enemy::ProcessShooting(float deltaTime, int baseMaxChanceToHit, int baseRequiredRollToShoot, float baseCooldownDuration)
{
	m_ShootCooldown -= deltaTime;

	if (m_ShootCooldown > 0.f)
	{
		return;
	}

	// Adjust shooting parameters based on difficulty
	int maxChanceToHit = baseMaxChanceToHit;
	int requiredRollToShoot = baseRequiredRollToShoot;
	float cooldownDuration = baseCooldownDuration; 

	switch (m_Difficulty)
	{
	case DifficultyLevel::VERY_EASY:
		requiredRollToShoot += 20;
		cooldownDuration += 1.0f;
		break;

	case DifficultyLevel::EASY:
		requiredRollToShoot += 10;
		cooldownDuration += 0.5f;
		break;

	case DifficultyLevel::NORMAL:
		// default values
		break;

	case DifficultyLevel::HARD:
		requiredRollToShoot -= 5;
		cooldownDuration -= 0.2f;
		break;

	case DifficultyLevel::VERY_HARD:
		requiredRollToShoot -= 10;
		cooldownDuration -= 0.4f;
		break;

	case DifficultyLevel::INSANE:
		requiredRollToShoot -= 15;
		cooldownDuration -= 0.6f;
		break;
	}

	requiredRollToShoot = std::clamp(requiredRollToShoot, 1, maxChanceToHit);
	cooldownDuration = std::max(0.1f, cooldownDuration);


	int rollResult = m_RNG.GetRandomInt(1, maxChanceToHit);
	if (rollResult <= requiredRollToShoot)
	{
		GameplayUtility::SpawnProjectile(m_Projectiles, m_ProjectileTextureFile, m_Sprite.getPosition(), Vector2f(0.0f, 1.0f));
		m_ShootCooldown = cooldownDuration;
	}
}


