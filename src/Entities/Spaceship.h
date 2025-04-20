#pragma once
#include "Projectile.h"

class Enemy;

class Spaceship
{
public:
	Spaceship();
	void Update(sf::RenderWindow& window, std::vector<std::unique_ptr<Enemy>>& cows, float deltaTime);
	void Draw(sf::RenderWindow& window);

	std::vector<std::unique_ptr<Projectile>>& GetProjectiles() { return m_Projectiles; }
	inline sf::Sprite& GetSprite() { return m_Sprite; }
	inline bool IsAlive() const { return m_IsAlive; }
	inline const void Reset() { m_IsAlive = true; }
	void OnHit();
private:
	void OnProjectileShoot();
	void UpdateProjectiles(float deltaTime);
	void CalculateAndUpdateCursorPosition(sf::RenderWindow& window);
	void DrawProjectile(sf::RenderWindow& window);
	void DrawSpaceship(sf::RenderWindow& window);
	
private:
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
	Vector2f m_Position;
	std::vector<std::unique_ptr<Projectile>> m_Projectiles;
	bool m_IsAlive;
};

