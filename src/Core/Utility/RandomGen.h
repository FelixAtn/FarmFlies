/*!
 * \file RandomGenerator.h
 *
 * \brief Provides a random number generator utility.
 *
 * The RandomGenerator class wraps around the C++ standard library's random number
 * generation facilities, offering methods to generate both random integers and floating-point numbers
 * within a specified range. It allows seeding for reproducibility and ensures the numbers are generated
 * with sufficient randomness.
 *
 * \author Felix Atanasescu - HE20830
 * \date April 2025
 */

#pragma once

 /**
  * @class RandomGenerator
  * @brief Provides random number generation utilities for integers and floats.
  *
  * Uses the C++ <random> library to generate random numbers.
  * The class can generate random integers and floating-point numbers in a specified range.
  * It also allows seeding to control randomness or for reproducible results.
  */
class RandomGenerator
{
public:
	/**
	 * @brief Default constructor that automatically seeds the random generator.
	 *
	 * Calls the Seed method to initialize the random number generator with the current time.
	 */
	RandomGenerator()
	{
		Seed();
	}

	/**
	 * @brief Seeds the random number generator with a given value.
	 *
	 * The default seed value is the current time, but this can be overridden
	 * to ensure reproducibility by providing a custom seed.
	 *
	 * @param seeder The value used to seed the random number generator (default is the current time).
	 */
	void Seed(unsigned int seeder = static_cast<unsigned int>(std::time(0))) { m_Random.seed(seeder); }

	/**
	 * @brief Generates a random integer in the specified range.
	 *
	 * Uses a uniform distribution to return a random integer between `min` and `max` (inclusive).
	 *
	 * @param min The minimum value of the random integer.
	 * @param max The maximum value of the random integer.
	 * @return A random integer between `min` and `max`.
	 */
	int GetRandomInt(int min, int max)
	{
		std::uniform_int_distribution<int> roll(min, max);
		return roll(m_Random);
	}

	/**
	 * @brief Generates a random floating-point number in the specified range.
	 *
	 * Uses a uniform real distribution to return a random float between `min` and `max`.
	 *
	 * @param min The minimum value of the random float.
	 * @param max The maximum value of the random float.
	 * @return A random float between `min` and `max`.
	 */
	float GetRandomFloat(float min, float max)
	{
		std::uniform_real_distribution<float> roll(min, max);
		return roll(m_Random);
	}

private:
	/// Random engine used to generate random numbers.
	std::default_random_engine m_Random;
};