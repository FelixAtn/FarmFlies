#pragma once

class RandomGenerator
{
public:
	RandomGenerator()
	{
		Seed();
	}
	void Seed(unsigned int seeder = static_cast<unsigned int>(std::time(0))) { m_Random.seed(seeder); }

	int GetRandomInt(int min, int max)
	{
		std::uniform_int_distribution<int> roll(min, max);
		return roll(m_Random);
	}

	float GetRandomFloat(float min, float max)
	{
		std::uniform_real_distribution<float> roll(min, max);
		return roll(m_Random);
	}

private:
	std::default_random_engine m_Random;
};

