/*!
 * \file Cursor.h
 *
 * \brief Singleton class that manages the in-game cursor.
 *
 * This class handles loading, updating, and rendering a custom cursor sprite,
 * replacing the system cursor if needed. It provides utility functions to retrieve
 * the cursor's position and change its texture.
 *
 * \author Felix AT
 * \date April 2025
 */

#pragma once

 /**
  * @class Cursor
  * @brief Singleton class for managing the game cursor.
  *
  * The Cursor class is a singleton that manages the custom cursor's appearance and behavior.
  * It handles updating the cursor's position every frame based on mouse input, drawing the
  * cursor sprite to the render window, and allowing dynamic changes to its texture.
  *
  * The cursor's position is stored using a custom Vector2i class.
  */
class Cursor
{
public:
    /**
 * @brief Retrieve the singleton instance of the Cursor class.
 *
 * @return A reference to the singleton Cursor instance.
 */
    static Cursor& Get()
    {
        static Cursor instance; 
        return instance;
    }
    // Delete copy constructor and assignment to enforce singleton behavior
    Cursor(const Cursor&) = delete;
    Cursor& operator=(const Cursor&) = delete;

    /**
   * @brief Set the texture for the cursor sprite.
   *
   * This method assigns a new texture to the cursor sprite using the texture name.
   * The texture should be preloaded or handled by a centralized resource manager.
   *
   * @param textureName The name or key of the texture to assign.
   */
    void SetTexture(const std::string& textureName);

    /**
    * @brief Update the cursor's internal state.
    *
    * This method retrieves the mouse position relative to the render window
    * and updates the sprite's position accordingly. Should be called once per frame.
    */
    void Update();

    /**
   * @brief Draw the cursor sprite on the screen.
   *
   * This method renders the custom cursor sprite to the provided SFML window.
   * Typically called during the game's render pass.
   *
   * @param window The SFML window to draw the cursor onto.
   */
    void Draw(sf::RenderWindow& window);

    /**
    * @brief Get the current position of the cursor.
    *
    * Returns the current screen-space position of the cursor in integer pixel coordinates.
    *
    * @return A constant reference to the Vector2i representing the cursor's position.
    */
    const Vector2i& GetPosition() const { return m_CursorPosition; }

private:
    /**
   * @brief Private constructor for enforcing singleton pattern.
   */
    Cursor() = default;

	sf::Sprite m_CursorSprite;        ///< The sprite representing the custom cursor.
	Vector2i m_CursorPosition;        ///< The current position of the cursor in screen coordinates.
	sf::RenderWindow* m_Window;       ///< Pointer to the render window for position calculations.
};

