/*
	Symmetry Engine 2.0
	Matt Phillips (c) 2009

	Maths.h

	Maths constants and utility functions
*/

#pragma once

#include <math.h>
#include <stdlib.h>

namespace ion
{
	namespace maths
	{
		const float PI = 3.14159264f;
		const float TWO_PI = PI * 2.0f;
		const float HALF_PI = PI / 2.0f;
		const float PI_DIV_180 = PI / 180.0f;
		const float ONE80_DIV_PI = 180.0f / PI;

		const float DEGREES_TO_RADIANS = PI / 180.0f;
		const float RADIANS_TO_DEGREES = 180.0f / PI;

		const float FLOAT_MIN = 1.175494351e-38f;
		const float FLOAT_MAX = 3.402823466e+38f;
		const float FLOAT_EPSILON = 1.19209290e-7f;

		int Round(double x);
		float RoundToNearest(float Value, int Nearest);
		int NextPowerOfTwo(int x);

		int RandInt();
		float RandFloat();

		float DegreesToRadians(float Degrees);
		float RadiansToDegrees(float Radians);
	}
}