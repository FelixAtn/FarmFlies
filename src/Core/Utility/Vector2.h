/*!
  * \file Vector2.h
  *
  * \brief A simple 2D vector class based on SFML's sf::Vector2.
  *
  * This class provides essential operations for 2D vectors, useful in game development.
  * It extends SFML's sf::Vector2 with additional mathematical functions to simplify common tasks.
  *
  * \author Felix AT
  * \date October 2024
  */

#pragma once

  /**
   * @class Vector2
   * @brief A basic 2D vector class for game development.
   *
   * 
   * 
   * This class represents a 2D vector and provides useful methods for mathematical operations.
   * It can be used for various purposes like positioning, movement, and physics calculations in games.
   *
   * 
   * 
   * @tparam T The type of the vector components (e.g., float or int).
   */

template <typename T>
class Vector2 : public sf::Vector2<T>
{
public:
    /**
     * @brief Constructor to create a Vector2 instance.
     *
     * Initializes the vector with given x and y coordinates.
     *
     * @param x The x-coordinate of the vector. Default is 0.
     * @param y The y-coordinate of the vector. Default is 0.
     */
    Vector2(T x = 0, T y = 0)
        : sf::Vector2<T>(x, y)
    {}

	// Constructor to allow conversion from sf::Vector2<T>
	Vector2(const sf::Vector2<T>& vector)
		: sf::Vector2<T>(vector)
	{}

	// Implicit conversion operator to sf::Vector2<T>
	operator sf::Vector2<T>() const
	{
		return *this;
	}

    /**
     * @brief Get the length of the vector.
     *
     * This method calculates the length (magnitude) of the vector using the formula:
     * \f$ \text{Length} = \sqrt{x^2 + y^2} \f$.
     *
     * @return The length of the vector as a float.
     */
    float Length() const
    {
        return std::sqrt(this->x * this->x + this->y * this->y);
    }

    /**
     * @brief Get the distance to another vector.
     *
     * This method computes the distance from this vector to another vector.
     *
     * @param other The other vector to calculate the distance to.
     * @return The distance to the other vector as a float.
     */
    float Distance(const Vector2& other) const
    {
        return std::sqrt((this->x - other.x) * (this->x - other.x) +
            (this->y - other.y) * (this->y - other.y));
    }

    /**
     * @brief Get the squared length of the vector.
     *
     * This method returns the square of the length, which avoids the computational cost
     * of taking the square root when it's not necessary.
     *
     * @return The squared length of the vector as a float.
     */
    float LengthSquared() const
    {
        return (this->x * this->x) + (this->y * this->y);
    }

    /**
     * @brief Normalize the vector to a length of 1.
     *
     * This method returns a vector in the same direction but with a length of 1.
     * If the vector is very small, it returns a zero vector.
     *
     * @return A normalized vector.
     */
    Vector2 Normalize() const
    {
        float length = Length();
        if (length > 0.0001f) // Minimal threshold to avoid division by zero
        {
            return Vector2(this->x / length, this->y / length);
        }
        return Vector2(0, 0);
    }

    /**
     * @brief Scale the vector by a given factor.
     *
     * This method scales the vector by multiplying both x and y components with the given scalar.
     *
     * @param scale The factor to scale the vector.
     * @return A new scaled vector.
     */
    Vector2 Scale(T scale) const
    {
        return Vector2(this->x * scale, this->y * scale);
    }

    /**
     * @brief Calculate the dot product with another vector.
     *
     * This method returns the dot product of this vector and another vector.
     *
     * @param other The other vector to calculate the dot product with.
     * @return The dot product as type T.
     */
    T DotProduct(const Vector2& other) const
    {
        return (this->x * other.x) + (this->y * other.y);
    }

    /**
     * @brief Calculate the cross product with another vector.
     *
     * This method calculates the cross product of this vector and another vector.
     *
     * @param other The other vector to calculate the cross product with.
     * @return The cross product as type T.
     */
    T CrossProduct(const Vector2& other) const
    {
        return (this->x * other.y) - (this->y * other.x);
    }

    /**
     * @brief Add another vector to this vector.
     *
     * This operator overload allows adding two Vector2 instances together.
     *
     * @param other The vector to add.
     * @return The resulting vector after addition.
     */
    Vector2 operator+ (const Vector2& other) const
    {
        return Vector2(this->x + other.x, this->y + other.y);
    }

    /**
     * @brief Subtract another vector from this vector.
     *
     * This operator overload allows subtracting two Vector2 instances.
     *
     * @param other The vector to subtract.
     * @return The resulting vector after subtraction.
     */
    Vector2 operator- (const Vector2& other) const
    {
        return Vector2(this->x - other.x, this->y - other.y);
    }

    /**
     * @brief Scale this vector by a scalar.
     *
     * This operator overload allows multiplying a vector by a scalar.
     *
     * @param scalar The scalar value to multiply by.
     * @return The scaled vector.
     */
    Vector2 operator* (T scalar) const
    {
        return Vector2(this->x * scalar, this->y * scalar);
    }

    /**
     * @brief Divide this vector by a scalar.
     *
     * This operator overload allows dividing a vector by a scalar.
     * If the scalar is zero, it returns a zero vector.
     *
     * @param scalar The scalar value to divide by.
     * @return The resulting vector after division.
     */
    Vector2 operator/ (T scalar) const
    {
        if (scalar != 0)
        {
            return Vector2(this->x / scalar, this->y / scalar);
        }
        return Vector2(0, 0);
    }

    /**
     * @brief Check if this vector is equal to another vector.
     *
     * This operator overload allows comparing two vectors for equality.
     *
     * @param other The vector to compare with.
     * @return True if the vectors are equal, false otherwise.
     */
    bool operator==(const Vector2& other) const
    {
        return this->x == other.x && this->y == other.y;
    }

    /**
     * @brief Check if this vector is not equal to another vector.
     *
     * This operator overload allows comparing two vectors for inequality.
     *
     * @param other The vector to compare with.
     * @return True if the vectors are not equal, false otherwise.
     */
    bool operator!=(const Vector2& other) const
    {
        return !(*this == other);
    }

    friend std::ostream& operator<< (std::ostream& os, const Vector2& vector)
    {
        os << "{" << vector.x << ", " << vector.y << "}";
        return os;
    }

private:
    static constexpr float MINIMAL_UNIT = 0.0001f; 
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector2u = Vector2<unsigned int>;