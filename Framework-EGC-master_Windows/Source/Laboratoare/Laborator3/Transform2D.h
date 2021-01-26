#pragma once

#include <include/glm.h>

namespace Transform2D
{
	// Translate matrix
	inline glm::mat3 Translate(float tX, float tY)
	{
		// TODO implement translate matrix
		return glm::mat3(1.f, 0.f, 0.f,
						 0.f, 1.f, 0.f,
						  tX,  tY, 1.f);
	}

	// Scale matrix
	inline glm::mat3 Scale(float sX, float sY)
	{
		// TODO implement scale matrix
		return glm::mat3( sX, 0.f, 0.f,
						 0.f,  sY, 0.f,
						 0.f, 0.f, 1.f);
	}

	// Rotate matrix
	inline glm::mat3 Rotate(float radians)
	{	
		// TODO implement rotate matrix
		float co = cos(radians), si = sin(radians);
		return glm::mat3( co, si, 0.f,
						 -si, co, 0.f,
						  0.f, 0.f, 1.f);
	}
}
