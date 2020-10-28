// Copyright 2020 <Anton Puiu>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ctime>

#include <Engine.h>
#include <labs/lablist.hpp>
#include <cstdlib>

int main(int argc, char **argv)
{
  srand((unsigned int)time(NULL));

  // Create a window property structure
  WindowProperties wp;
  wp.resolution = glm::vec2(1920, 1080);

  // Init the Engine and create a new window with the defined properties
  WindowObject* window = Engine::Init(wp);

  // Create a new 3D world and start running it
  World *world = new Laborator1();
  world->Init();
  world->Run();

  // Signals to the Engine to release the OpenGL context
  Engine::Exit();

  return 0;
}
