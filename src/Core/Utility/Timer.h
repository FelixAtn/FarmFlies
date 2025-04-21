/*!
 * \file Timer.h
 *
 * \brief A simple timer utility class.
 *
 * The Timer class provides functionality for tracking elapsed time and checking when a specified
 * interval has passed. It is designed to be used in scenarios where periodic events need to be triggered,
 * such as handling time-based actions in a game.
 *
 * \author Felix Atanasescu - HE20830
 * \date April 2025
 */

#pragma once

 /**
  * @class Timer
  * @brief Tracks elapsed time and allows periodic actions based on intervals.
  *
  * This class is useful for scenarios where you want to check if a specified amount of time has
  * passed, such as triggering events, animations, or other time-based actions.
  * The timer works by accumulating time and allowing you to check if the interval has been exceeded,
  * at which point it resets or continues to accumulate time.
  */
class Timer
{
public:
	/**
	 * @brief Constructor that initializes the timer with a specified interval.
	 *
	 * This constructor allows you to set the interval (in seconds) at which the timer should trigger.
	 * It starts the clock to begin tracking time.
	 *
	 * @param interval The time interval (in seconds) to trigger the timer (default is 1.0f).
	 */
	Timer(float interval = 1.0f)
		: m_Interval(interval), m_PassedTime(0.0f)
	{
		m_Clock.restart();
	}

	/**
	 * @brief Sets the interval at which the timer triggers.
	 *
	 * You can change the interval after the timer has been created using this method.
	 * The timer will then trigger at the new interval.
	 *
	 * @param interval The new interval (in seconds).
	 */
	inline void SetInterval(float interval)
	{
		m_Interval = interval;
	}

	/**
	 * @brief Restarts the timer, resetting the passed time to zero.
	 *
	 * Resets the timer so that the elapsed time tracking starts over from zero.
	 */
	inline void Restart()
	{
		m_PassedTime = 0.f;
		m_Clock.restart();
	}

	/**
	 * @brief Gets the time that has passed since the timer started or was last restarted.
	 *
	 * Returns the accumulated time since the last restart or reset.
	 *
	 * @return The elapsed time in seconds.
	 */
	inline float GetPassedTime() const
	{
		return m_PassedTime;
	}

	/**
	 * @brief Checks if the specified interval has passed based on the delta time.
	 *
	 * Accumulates time using the `deltaTime` parameter and checks if the interval has been exceeded.
	 * If the interval is reached or exceeded, it resets the passed time and returns true.
	 * If not, it returns false and continues accumulating time.
	 *
	 * @param deltaTime The time that has passed since the last frame (in seconds).
	 * @return True if the interval has passed, false otherwise.
	 */
	bool HasTimePassed(float deltaTime)
	{
		m_PassedTime += deltaTime;

		if (m_PassedTime >= m_Interval)
		{
			m_PassedTime -= m_Interval;
			return true;
		}
		return false;
	}

private:
	sf::Clock m_Clock; ///< SFML clock to track time.
	float m_PassedTime; ///< Accumulated time that has passed since the last reset.
	float m_Interval;   ///< The time interval (in seconds) to trigger the timer.
};