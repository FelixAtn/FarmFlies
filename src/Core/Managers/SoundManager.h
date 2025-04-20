#pragma once

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	// Load a sound from file
	bool LoadSound(const std::string& soundName, const std::string& filePath);

	// Play a sound
	void PlaySound(const std::string& soundName);

	// Stop a sound
	void StopSound(const std::string& soundName);

private:
	std::map<std::string, sf::SoundBuffer> m_SoundBuffers;  // Map of sound name to sound buffer
	std::map<std::string, sf::Sound> m_Sounds;              // Map of sound name to sound instance
};
