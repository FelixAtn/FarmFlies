#pragma once

class Enemy;
class Spaceship;

class Projectile
{
public:
	Projectile(const std::string& fileName, const Vector2f& startingPosition, const Vector2f& direction = { 0, -1 });

	void Update(float deltaTime);

	void MoveProjectile(float deltaTime);

	void Draw(sf::RenderWindow& window);

	inline const Vector2f GetPosition() {	return m_Sprite.getPosition(); }
	inline const bool IsProjectileActive() const { return m_IsActive; }
	inline bool GetStatus() const { return m_IsActive; }
	const sf::FloatRect& GetBounds() const { return m_Sprite.getGlobalBounds(); }


	inline void SetStatus(bool isActive) { m_IsActive = isActive; }

private:
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
	Vector2f m_StartingPosition;
	Vector2f m_CurrentPosition;
	Vector2f m_Direction;
	bool m_IsActive;
};

