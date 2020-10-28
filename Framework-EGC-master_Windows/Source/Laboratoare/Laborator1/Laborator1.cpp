#include "Laborator1.h"

#include <vector>
#include <iostream>
#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1() 
{
	angularStep = 0;
	colordel = false;
	cicle = 1;
	rotation = false;

	x_pos = false;
	x_neg = false;
	y_pos = false;
	y_neg = false;
	z_pos = false;
	z_neg = false;

	x_position = -1;
	y_position = 0.5f;
	z_position = 0;
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("teapot");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(0, 0, 0, 1);
	if (colordel == true) {
		glClearColor(1, 0, 0, 1);
	}
	else {
		glClearColor(0, 0, 0, 1);
	}

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["sphere"], glm::vec3(2, 0.5f, 0));
	switch (cicle) {
		case 1:
			RenderMesh(meshes["box"], glm::vec3(x_position, y_position, z_position));
			break; 
		case 2:
			RenderMesh(meshes["sphere"], glm::vec3(x_position, y_position, z_position));
			break;
		case 3:
			RenderMesh(meshes["teapot"], glm::vec3(x_position, y_position, z_position));
			break;
	}

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		if (x_pos) {
			x_position += deltaTimeSeconds;
		}

		if (y_pos) {
			y_position += deltaTimeSeconds;
		}

		if (z_pos) {
			z_position += deltaTimeSeconds;
		}

		if (x_neg) {
			x_position -= deltaTimeSeconds;
		}

		if (y_neg) {
			y_position -= deltaTimeSeconds;
		}

		if (z_neg) {
			z_position -= deltaTimeSeconds;
		}
	}

	if (rotation) {
		raza = sqrt(pow(x_position, 2) + pow(y_position, 2));
		angularStep += deltaTimeSeconds;
		cout << deltaTimeSeconds << "\n";
		x_position = raza * cos(angularStep);
		y_position = raza * sin(angularStep);
		cout << x_position << "  " << y_position << "\n";
	}
}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		colordel = !colordel;
	}


	if (key == GLFW_KEY_P) {
		if (cicle != 3) {
			cicle++;
		}
		else {
			cicle = 1;
		}
	}

	if (key == GLFW_KEY_S) {
		z_pos = true;
	}

	if (key == GLFW_KEY_W) {
		z_neg = true;
	}

	if (key == GLFW_KEY_E) {
		y_pos = true;
	}

	if (key == GLFW_KEY_Q) {
		y_neg = true;
	}

	if (key == GLFW_KEY_D) {
		x_pos = true;
	}

	if (key == GLFW_KEY_A) {
		x_neg = true;
	}

	if (key == GLFW_KEY_R) {
		rotation = true;
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event

	if (key == GLFW_KEY_S) {
		z_pos = false;
	}

	if (key == GLFW_KEY_W) {
		z_neg = false;
	}

	if (key == GLFW_KEY_E) {
		y_pos = false;
	}

	if (key == GLFW_KEY_Q) {
		y_neg = false;
	}

	if (key == GLFW_KEY_D) {
		x_pos = false;
	}

	if (key == GLFW_KEY_A) {
		x_neg = false;
	}

	if (key == GLFW_KEY_R) {
		rotation = false;
	}
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
