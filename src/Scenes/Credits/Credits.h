#pragma once

class Credits : public IGameScene
{
public:
	Credits(SceneManager& sceneManager, sf::RenderWindow& window);
	void Update(float deltaTima) override;
	void Draw() override;

private:
	SceneManager& m_SceneManager;
	sf::RenderWindow& m_Window;

};

