#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Player
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

	Mesh* CreateArrow(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

	Mesh* CreateLine(std::string name, glm::vec3 leftBottomCorner, glm::vec3 BottomCorner, glm::vec3 color, bool fill = false);

	Mesh* CreateCircle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

	Mesh* CreateHalfCircle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

	Mesh* CreatePolyline(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

	Mesh* CreateShuriken(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

}

