#pragma once

constexpr uint32_t MAX_KEYS = 650;

enum class KeyBind
{
	Pause,
	Shoot
};

class InputManager
{
public:
	static InputManager& Get()
	{
		static InputManager instance;
		return instance;
	}

	void Update(float deltaTime);
	bool IsKeyPress(KeyBind key);
	bool IsKeyDown(KeyBind key);

private:
	InputManager() = default;
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	void UpdateKeyboard();
	void UpdateMouse();

private:
	std::bitset<MAX_KEYS> m_CurrentKey;
	std::bitset<MAX_KEYS> m_PreviousKey = 0;
};

