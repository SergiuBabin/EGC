#include "SceneInput.h"
#include <iostream>

#include <defines/gl.h>
#include <window/InputWindow.h>

#include "SimpleScene.h"

#include <defines/Component/Transform.h>

using namespace std;

SceneInput::SceneInput(SimpleScene *scene)
{
	this->scene = scene;
}

void SceneInput::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_F3)
		scene->drawGroundPlane = !scene->drawGroundPlane;

	if (key == GLFW_KEY_F5)
		scene->ReloadShaders();

	if (key == GLFW_KEY_ESCAPE)
		scene->Exit();
}