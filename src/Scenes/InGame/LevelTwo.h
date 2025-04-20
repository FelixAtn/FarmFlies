#pragma once

class LevelTwo final : public IGameScene
{
public:
	LevelTwo(SceneManager& sceneManager, sf::RenderWindow& window);

	void OnInit() override;
	void OnDestroy() override;

	void OnStart() override;
	void OnStop() override;

	void Update(float deltaTime) override;
	void Draw() override;


private:
	SceneManager& m_SceneManager;
	sf::RenderWindow& m_Window;
};

