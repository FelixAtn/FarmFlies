#pragma once

class Timer
{
public:
	Timer(float interval = 1.0f)
		: m_Interval(interval), m_PassedTime(0.0f)
	{
		m_Clock.restart();
	}

	inline void SetInterval(float interval)
	{
		m_Interval = interval;
	}

	inline void Restart()
	{
		m_PassedTime = 0.f;
		m_Clock.restart();
	}
	
	inline float GetPassedTime() const
	{
		return m_PassedTime;
	}

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
	sf::Clock m_Clock; 
	float m_PassedTime;
	float m_Interval;  
};

