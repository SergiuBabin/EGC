#pragma once

#include <window/InputWindow.h>

class SimpleScene;

class SceneInput : public InputController
{
	public:
		SceneInput(SimpleScene *camera);
		void OnKeyPress(int key, int mods) override;

	public:
		SimpleScene *scene;
};

