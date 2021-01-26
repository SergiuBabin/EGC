#include "Player.h"

#include <vector>
#include <iostream>
#include <Core/Engine.h>
#include "Transform2D.h"

using namespace std;

Mesh* Player::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Player::CreateArrow(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),   // 0
		VertexFormat(corner + glm::vec3(length, length / 2, 0), color), // 1
		VertexFormat(corner + glm::vec3(0, length, 0), color), // 2
	};

	Mesh* arrow = new Mesh(name);
	std::vector<unsigned short> indices = {0, 1, 2};
	arrow->InitFromData(vertices, indices);

	return arrow;
}

Mesh* Player::CreateLine(std::string name, glm::vec3 Start, glm::vec3 End, glm::vec3 color, bool fill)
{

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(Start, color), // 0
		VertexFormat(End, color), // 1
	};

	Mesh* line = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1};
	line->SetDrawMode(GL_LINES);
	line->InitFromData(vertices, indices);

	return line;
}

Mesh* Player::CreateCircle(std::string name, glm::vec3 leftBottomCorner, float NrSlices, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	vector<VertexFormat> vertices;
	vector<unsigned short> indices;
	float delta = 2 * 3.14159f / NrSlices;
	for (unsigned int i = 0; i <= NrSlices; i++)
	{
			vertices.emplace_back(corner + glm::vec3(cos(delta * i) * 30, sin(delta * i) * 40, 0), color);
			indices.push_back(i);
	}

	Mesh* circle = new Mesh(name);
	circle->SetDrawMode(GL_TRIANGLE_FAN);
	circle->InitFromData(vertices, indices);

	return circle;
}

Mesh* Player::CreateHalfCircle(std::string name, glm::vec3 leftBottomCorner, float NrSlices, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	vector<VertexFormat> vertices;
	vector<unsigned short> indices;
	unsigned int j = 0;
	for (float i = 3 * M_PI_2; i <= 5 * M_PI_2; i += M_PI/NrSlices, j++)
	{
		vertices.emplace_back(glm::vec3(cos(i) * 40, sin(i) * 70, 0), color);
		indices.push_back(j);
	}

	Mesh* halfCircle = new Mesh(name);

	halfCircle->SetDrawMode(GL_LINE_STRIP);
	halfCircle->InitFromData(vertices, indices);

	return halfCircle;
}

Mesh* Player::CreatePolyline(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),   // 0
		VertexFormat(corner + glm::vec3(-length, -length / 2, 0), color), // 1
		VertexFormat(corner + glm::vec3(0, -length / 2, 0), color), // 2
		VertexFormat(corner + glm::vec3(-length, -2 * length / 2, 0), color), // 3
		VertexFormat(corner + glm::vec3(0, -2 * length / 2, 0), color), // 4
		VertexFormat(corner + glm::vec3(-length, -3 * length / 2, 0), color), // 5
	};

	Mesh* polyline = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5};
	polyline->SetDrawMode(GL_LINE_STRIP);
	polyline->InitFromData(vertices, indices);

	return polyline;
}

Mesh* Player::CreateShuriken(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{	
		VertexFormat(corner + glm::vec3(0, length, 0), color), // 0
		VertexFormat(corner + glm::vec3(length, length, 0), color), // 1
		VertexFormat(corner, color),  // 2
		VertexFormat(corner + glm::vec3(length, 0, 0), color), // 3
		VertexFormat(corner + glm::vec3(length, -length, 0), color), // 4
		VertexFormat(corner + glm::vec3(0, -length, 0), color), // 5
		VertexFormat(corner + glm::vec3(-length, -length, 0), color), // 6
		VertexFormat(corner + glm::vec3(-length, 0, 0), color), // 7
		VertexFormat(corner + glm::vec3(-length, length, 0), color), // 8

	};

	Mesh* arrow = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 2, 5, 6, 2, 7, 8, 2};
	arrow->InitFromData(vertices, indices);

	return arrow;
}
