#include "stdafx.h"
#include "Helper.h"

void CoreHelper::LoadTextureAndSprite(sf::Texture& outTexture, sf::Sprite& outSprite, const std::string& fileName)
{
	// Attempt to load the texture from the specified file
	if (!outTexture.loadFromFile(fileName))
	{
		// Log an error if the texture loading fails
		Log::Print("Texture failed to load! ", LogLevel::ERROR_);
		return;
	}

	// Set the sprite's texture once it has successfully loaded
	outSprite.setTexture(outTexture);
}

void CoreHelper::LoadMusic(sf::Music& outMusic, const std::string& fileName)
{
	// Attempt to load and play the music from the specified file
	if (!outMusic.openFromFile(fileName))  // Replace with your music file
	{
		// Log an error if the music loading fails
		Log::Print("Failed to load background music.", LogLevel::ERROR_);
		return;
	};
}
