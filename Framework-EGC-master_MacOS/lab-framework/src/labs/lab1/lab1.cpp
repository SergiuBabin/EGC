#include "lab1.hpp"

#include <vector>
#include <iostream>

#include <Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
  clear_r = DEFAULT_CLEAR_R;
  clear_g = DEFAULT_CLEAR_G;
  clear_b = DEFAULT_CLEAR_B;

  clear_changed = false;
  to_render = CUBE;

  pos_x = 3;
  pos_y = 2;
  pos_z = 0;

  update_pos_x = false;
  update_pos_y = false;
  update_pos_z = false;
  update_neg_x = false;
  update_neg_y = false;
  update_neg_z = false;

  speed_factor = 1.0f;
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

  // Load a second mesh from file into GPU memory
  {
    Mesh* mesh = new Mesh("teapot");
    mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
    meshes[mesh->GetMeshID()] = mesh;
  }

  // Load aditional meshes into GPU memory
  {
    Mesh* mesh = new Mesh("sphere");
    mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
    meshes[mesh->GetMeshID()] = mesh;
  }
}

void Laborator1::FrameStart()
{
  // check if 'c' key was pressed
  if (clear_changed == true) {
    clear_r = 1;
  } else {
    clear_r = 0;
  }


}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(clear_r, clear_g, clear_b, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));
	RenderMesh(meshes["box"], glm::vec3(5, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

  // TODO: Ex 2
  //  RenderMesh(meshes["teapot"], glm::vec3(3, 2, 0), glm::vec3(0.5f));

  // TODO: Ex 5
  if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
  if (update_pos_x) {
    pos_x += deltaTimeSeconds * trans_factor * speed_factor;
  }

  if (update_neg_x) {
    pos_x -= deltaTimeSeconds * trans_factor * speed_factor;
  }

  if (update_pos_y) {
    pos_y += deltaTimeSeconds * trans_factor * speed_factor;
  }

  if (update_neg_y) {
    pos_y -= deltaTimeSeconds * trans_factor * speed_factor;
  }

  if (update_pos_z) {
    pos_z += deltaTimeSeconds * trans_factor * speed_factor;
  }

  if (update_neg_z) {
    pos_z -= deltaTimeSeconds * trans_factor * speed_factor;
  }
  }
  // TODO: Ex 4
  switch(to_render) {
  case CUBE:
    RenderMesh(meshes["box"], glm::vec3(pos_x, pos_y, pos_z), glm::vec3(0.5f));
    break;
  case TEAPOT:
    RenderMesh(meshes["teapot"], glm::vec3(pos_x, pos_y, pos_z), glm::vec3(0.5f));
    break;
  case SPHERE:
    RenderMesh(meshes["sphere"], glm::vec3(pos_x, pos_y, pos_z), glm::vec3(0.5f));
    break;
  }
}

void Laborator1::FrameEnd()
{
  // DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
}

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
    // change displayed object
    if (to_render == TEAPOT) {
      to_render = CUBE;
    } else {
      to_render = static_cast<Object>(static_cast<int>(to_render) + 1);
    }
	}

  if (key == GLFW_KEY_LEFT_SHIFT) {
    speed_factor = 2.5f;
  }

  if (key == GLFW_KEY_P) {
    clear_changed = !clear_changed;
  }

  if (key == GLFW_KEY_W) {
    update_pos_x = true;
  }

  if (key == GLFW_KEY_S) {
    update_neg_x = true;
  }

  if (key == GLFW_KEY_D) {
    update_pos_z = true;
  }

  if (key == GLFW_KEY_A) {
    update_neg_z = true;
  }

  if (key == GLFW_KEY_E) {
    update_pos_y = true;
  }

  if (key == GLFW_KEY_Q) {
    update_neg_y = true;
  }
}

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
  if (key == GLFW_KEY_LEFT_SHIFT) {
    speed_factor = 1.0f;
  }

  if (key == GLFW_KEY_W) {
    update_pos_x = false;
  }

  if (key == GLFW_KEY_S) {
    update_neg_x = false;
  }

  if (key == GLFW_KEY_D) {
    update_pos_z = false;
  }

  if (key == GLFW_KEY_A) {
    update_neg_z = false;
  }

  if (key == GLFW_KEY_E) {
    update_pos_y = false;
  }

  if (key == GLFW_KEY_Q) {
    update_neg_y = false;
  }
}

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

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
