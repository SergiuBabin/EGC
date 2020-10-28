#pragma once

/*
 *	Graphic Engine
 */

#include <defines/gl.h>
#include <defines/glm.h>
#include <defines/math.h>
#include <defines/utils.h>

#include <gpu/GPUBuffers.h>
#include <gpu/Mesh.h>
#include <gpu/Shader.h>
#include <gpu/Texture2D.h>

#include "World.h"

#include <defines/Component/Camera.h>

#include <managers/ResourcePath.h>
#include <managers/TextureManager.h>

// #include <window/WindowObject.h>
// #include <window/InputController.h>
#include <window/InputWindow.h>

class Engine
{
	public:
		static WindowObject* Init(WindowProperties &props);

		static WindowObject* GetWindow();

		// Get elapsed time in seconds since the application started
		static double GetElapsedTime();

		static void Exit();

	private:
		static WindowObject* window;
};