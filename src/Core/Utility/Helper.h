#pragma once

namespace CoreHelper
{
	/**
 * @brief Loads a texture and assigns it to a sprite.
 *
 * Loads a texture from a file and assigns it to the provided sprite. If the texture fails to load, an error message is logged.
 *
 * @param texture The texture object to load the texture into.
 * @param sprite The sprite object to assign the texture to.
 * @param fileName The file name of the texture to load.
 */
	void LoadTextureAndSprite(sf::Texture& outTexture, sf::Sprite& outSprite, const std::string& fileName);

	/**
 * @brief Loads background music from a file.
 *
 * Loads and plays background music from a given file. If loading the music fails, an error message is logged.
 *
 * @param music The music object to load the background music into.
 * @param fileName The file name of the music to load.
 */
	void LoadMusic(sf::Music& outMusic, const std::string& fileName);


}