
/*!
 * \file SoundManager.h
 *
 * \brief Declares the SoundManager class used to load and manage sound effects.
 *
 * The SoundManager is responsible for handling short, non-streamed sound effects
 * using SFML’s sf::Sound and sf::SoundBuffer. It allows for sounds to be loaded,
 * played, and stopped using string identifiers.
 *
 * This system is designed for in-game sound effects like attacks, footsteps, UI clicks, etc.
 * Music streaming should be handled separately via sf::Music.
 *
 * \author Felix Atanasescu - HE20830
 * \date April 2025
 */

#pragma once

 /**
  * @class SoundManager
  * @brief Manages one-shot sound effects in the game.
  *
  * Handles the loading and playback of short sounds via string keys.
  * Sounds must be loaded before they can be played.
  *
  * Features:
  * - Load sound effects from disk
  * - Play a sound on demand
  * - Stop a currently playing sound
  */
class SoundManager
{
public:
	/**
	* @brief Constructs the SoundManager.
	*/
	SoundManager();

	/**
	 * @brief Destroys the SoundManager and frees any loaded resources.
	 */
	~SoundManager();

	/**
	 * @brief Loads a sound file into memory and stores it under a name.
	 *
	 * If the sound was previously loaded, it will be overwritten.
	 *
	 * @param soundName A unique identifier for the sound.
	 * @param filePath The path to the audio file to load (e.g., "assets/sound.wav").
	 * @return True if the sound loaded successfully, false otherwise.
	 */
	bool LoadSound(const std::string& soundName, const std::string& filePath);

	/**
	 * @brief Plays the sound associated with the given name.
	 *
	 * If the sound is not loaded, nothing will happen.
	 *
	 * @param soundName The identifier of the sound to play.
	 */
	void PlaySound(const std::string& soundName);

	/**
	 * @brief Stops playback of the sound associated with the given name.
	 *
	 * Has no effect if the sound is not currently playing or not loaded.
	 *
	 * @param soundName The identifier of the sound to stop.
	 */
	void StopSound(const std::string& soundName);

private:
	std::map<std::string, sf::SoundBuffer> m_SoundBuffers; ///< Maps sound names to their loaded audio data
	std::map<std::string, sf::Sound> m_Sounds;             ///< Maps sound names to their playable sf::Sound instances
};
