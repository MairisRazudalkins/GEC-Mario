#pragma once

#ifndef Utils;
#define Utils

namespace Utils
{
	float Clamp(float value, float min, float max)
	{
		if (value < min) value = min;
		else if (value > max) value = max;
		return value;
	}

	float Clamp(int value, int min, int max)
	{
		if (value < min) value = min;
		else if (value > max) value = max;
		return value;
	}
}

#endif