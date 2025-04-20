#include "stdafx.h"
#include "SoundManager.h"

static SoundManager g_SoundManager;

SoundManager::SoundManager() = default;

SoundManager::~SoundManager()
{
	// Destructor is empty because sf::Sound automatically cleans up when it goes out of scope
}

bool SoundManager::LoadSound(const std::string& soundName, const std::string& filePath)
{
	// Check if sound is already loaded
	if (m_SoundBuffers.find(soundName) != m_SoundBuffers.end())
	{
		return true;  // Sound already loaded
	}

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(filePath))
	{
		std::cerr << "Failed to load sound from " << filePath << std::endl;
		return false;  // Loading sound failed
	}

	// Store the sound buffer
	m_SoundBuffers[soundName] = buffer;

	// Create the sound instance using the loaded buffer
	sf::Sound sound;
	sound.setBuffer(m_SoundBuffers[soundName]);

	// Store the sound instance
	m_Sounds[soundName] = sound;

	return true;  // Successfully loaded sound
}

void SoundManager::PlaySound(const std::string& soundName)
{
	// Find sound by name
	if (m_Sounds.find(soundName) != m_Sounds.end())
	{
		m_Sounds[soundName].play();  // Play the sound
	}
	else
	{
		std::cerr << "Sound not found: " << soundName << std::endl;
	}
}

void SoundManager::StopSound(const std::string& soundName)
{
	// Find sound by name
	if (m_Sounds.find(soundName) != m_Sounds.end())
	{
		m_Sounds[soundName].stop();  // Stop the sound
	}
	else
	{
		std::cerr << "Sound not found: " << soundName << std::endl;
	}
}