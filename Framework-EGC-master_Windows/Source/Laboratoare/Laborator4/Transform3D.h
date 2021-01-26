#pragma once

#include <include/glm.h>

namespace Transform3D
{
	// Translate matrix
	inline glm::mat4 Translate(float tx, float ty, float tz)
	{
		// TODO implement translate matrix
		return glm::mat4(
			1, 0, 0, 0,     // coloana 1 in memorie 
			0, 1, 0, 0,     // coloana 2 in memorie 
			0, 0, 1, 0,     // coloana 3 in memorie 
			tx, ty, tz, 1);
	}

	// Scale matrix
	inline glm::mat4 Scale(float sx, float sy, float sz)
	{
		// TODO implement scale matrix
		return glm::mat4(
			sx, 0, 0, 0,     // coloana 1 in memorie 
			0, sy, 0, 0,     // coloana 2 in memorie 
			0, 0, sz, 0,     // coloana 3 in memorie 
			0, 0, 0, 1);
	}

	// Rotate matrix relative to the OZ axis
	inline glm::mat4 RotateOZ(float radians)
	{
		// TODO implement rotate matrix
		float co = cos(radians);
		float si = sin(radians);

		return glm::mat4(
			1, 0, 0, 0,     // coloana 1 in memorie 
			0, co, si, 0,     // coloana 2 in memorie 
			0, -si, co, 0,     // coloana 3 in memorie 
			0, 0, 0 , 1);
	}

	// Rotate matrix relative to the OY axis
	inline glm::mat4 RotateOY(float radians)
	{
		// TODO implement rotate matrix
		float co = cos(radians);
		float si = sin(radians);

		return glm::mat4(
			co, 0, -si, 0,     // coloana 1 in memorie 
			0, 1, 0, 0,     // coloana 2 in memorie 
			si, 0, co, 0,     // coloana 3 in memorie 
			0, 0, 0, 1);
	}

	// Rotate matrix relative to the OX axis
	inline glm::mat4 RotateOX(float radians)
	{
		// TODO implement rotate matrix
		float co = cos(radians);
		float si = sin(radians);
		return glm::mat4(
			co, si, 0, 0,     // coloana 1 in memorie 
			-si, co, 0, 0,     // coloana 2 in memorie 
			0, 0, 1, 0,     // coloana 3 in memorie 
			0, 0, 0, 1);
	}
}
