#include "stdafx.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Spaceship.h"


Projectile::Projectile(const std::string& fileName, const Vector2f& startingPosition, const Vector2f& direction /*= { 0, -1 }*/) 
	: m_StartingPosition(startingPosition)
	, m_CurrentPosition(m_StartingPosition)
	, m_IsActive(true)
	, m_Direction(direction)
{
	m_Texture.loadFromFile(fileName);
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setPosition(startingPosition);
	m_Sprite.scale(0.5f, 0.5f);
};

void Projectile::Update(float deltaTime)
{
	MoveProjectile(deltaTime);

	MoveProjectile(deltaTime);
	if (m_Sprite.getPosition().y < -1 || m_Sprite.getPosition().y > 1080) // update bounds as needed
	{
		m_IsActive = false;
	}
}

void Projectile::MoveProjectile(float deltaTime)
{
	float speed = 300;
	m_Sprite.move(m_Direction * speed * deltaTime);
}

void Projectile::Draw(sf::RenderWindow& window)
{
	window.draw(m_Sprite);
}
