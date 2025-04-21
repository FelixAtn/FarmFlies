#pragma once

class Intro final: public IGameScene
{
public:
	Intro(SceneManager& sceneManager, sf::RenderWindow& window);
	void Update(float deltaTima) override;
	void Draw() override;

private:
	SceneManager& m_SceneManager;
	sf::RenderWindow& m_Window;
};

