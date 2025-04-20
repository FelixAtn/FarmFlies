#include "stdafx.h"
#include "Spaceship.h"
#include "Core/Managers/InputManager.h"
#include "Core/Managers/SoundManager.h"
#include "Enemy.h"
#include "Core/Utility/strings.h"
#include "Core/Utility/GameplayUtility.h"
#include "Entities/Projectile.h"

static SoundManager g_ShootSound;
static SoundManager g_DeadSound;

Spaceship::Spaceship()
	: m_IsAlive(true)
{
	m_Texture.loadFromFile(SPACESHIP);
	m_Sprite.setTexture(m_Texture);
	g_ShootSound.LoadSound("shoot", SHOOTING_SOUND);
	g_DeadSound.LoadSound("dead", SPACESHIP_HIT);
}

void Spaceship::Update(sf::RenderWindow& window, std::vector<std::unique_ptr<Enemy>>& cows, float deltaTime)
{
	CalculateAndUpdateCursorPosition(window);
	OnProjectileShoot();
	UpdateProjectiles(deltaTime);
}

void Spaceship::Draw(sf::RenderWindow& window)
{
	DrawProjectile(window);
	DrawSpaceship(window);
}

void Spaceship::OnHit()
{
	g_DeadSound.PlaySoundW("dead");
}

void Spaceship::OnProjectileShoot()
{
	if (InputManager::Get().IsKeyPress(KeyBind::Shoot))
	{
		g_ShootSound.PlaySound("shoot");
		GameplayUtility::SpawnProjectile(m_Projectiles, BOMB, m_Sprite.getPosition());
	}
}

void Spaceship::UpdateProjectiles(float deltaTime)
{
	// Update active projectiles
	for (const auto& projectile : m_Projectiles)
	{
		projectile->Update(deltaTime);
	}

	// Remove inactive projectiles
	GameplayUtility::RemoveInactiveProjectiles(m_Projectiles);
}

void Spaceship::CalculateAndUpdateCursorPosition(sf::RenderWindow& window)
{
	// Get mouse position and set cursor
	Vector2i cursorPosition = sf::Mouse::getPosition(window);

	// Get sprite size
	Vector2f spriteSize(m_Sprite.getGlobalBounds().width, m_Sprite.getGlobalBounds().height);

	// Center the sprite at the cursor
	m_Sprite.setPosition(static_cast<float>(cursorPosition.x) - spriteSize.x / 2, static_cast<float>(cursorPosition.y) - spriteSize.y / 2);
}

void Spaceship::DrawProjectile(sf::RenderWindow& window)
{
	for (const auto& it : m_Projectiles)
	{
		it->Draw(window);
	}
}

void Spaceship::DrawSpaceship(sf::RenderWindow& window)
{
	if (m_IsAlive)
	{
		window.draw(m_Sprite);
	}
}


