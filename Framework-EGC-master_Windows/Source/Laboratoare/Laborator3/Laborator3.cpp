#include "Laborator3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

void Laborator3::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;


	// compute coordinates of square center
	cx = corner.x + squareSide / 2;
	cy = corner.y + squareSide / 2;
	Bcx = corner.x + squareSide / 2;
	Bcy = corner.y + squareSide / 2;
	moveR = false;
	BmoveR = true;
	pulse = true;
	maxY = true;
	
	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 150;

	BtranslateX = 0;
	BtranslateY = 0;
	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;
	
	// initialize angularStep
	angularStep = 0;
	BangularStep = 0;
	

	Mesh* square1 = Object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);
	
	Mesh* square2 = Object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
	AddMeshToList(square2);

	Mesh* square3 = Object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
	AddMeshToList(square3);

	Mesh* square4 = Object2D::CreateSquare("square4", corner, squareSide, glm::vec3(0, 1, 1));
	AddMeshToList(square4);
}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator3::Update(float deltaTimeSeconds)
{
	// TODO: update steps for translation, rotation, scale, in order to create animations
	glm::ivec2 resolution = window->GetResolution();
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(150, 250);
		// TODO: create animations by multiplying current transform matrix with matrices from Transform 2D

		if (moveR) {
			translateY += deltaTimeSeconds * 100;
			modelMatrix *= Transform2D::Translate(translateX, translateY);

			if (translateY > resolution.y * LIMIT)
				moveR = false;
		}
		else {
			translateY -= deltaTimeSeconds * 100;
			modelMatrix *= Transform2D::Translate(translateX, translateY);

			if (translateY <= 0) {
				moveR = true;
			}
		}
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(400, 250);

		//TODO create animations by multiplying current transform matrix with matrices from Transform 2D
		if (scaleX <= 1.5f && pulse == true) {
			scaleX += deltaTimeSeconds;
			scaleY += deltaTimeSeconds;
			if (scaleX >= 1.5f) pulse = false;
		}
		else {
			scaleX -= deltaTimeSeconds;
			scaleY -= deltaTimeSeconds;
			if (scaleX <= .5f) pulse = true;
		}

		modelMatrix *= Transform2D::Translate(cx, cy);
		modelMatrix *= Transform2D::Scale(scaleX, scaleY);
		modelMatrix *= Transform2D::Translate(-cx, -cy);	
		RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(650, 250);

		angularStep += deltaTimeSeconds;
		modelMatrix *= Transform2D::Translate(cx, cy);
		modelMatrix *= Transform2D::Rotate(angularStep);
		modelMatrix *= Transform2D::Translate(-cx, -cy);
		//TODO create animations by multiplying current transform matrix with matrices from Transform 2D
		RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
	}

	// BONUS
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(250, 50);
		// TODO: create animations by multiplying current transform matrix with matrices from Transform 2D
		if (BmoveR) {
			if (Bcx <= resolution.x * .25f ) {
				printf("tX = %f   Y = %f N = %f  M = %f\n", Bcx, Bcy, resolution.x * .25f, resolution.x * .5f);
				Bcx += deltaTimeSeconds * 200.f;
				Bcy += deltaTimeSeconds * 200.f;
				
				BangularStep -= deltaTimeSeconds;
				modelMatrix *= Transform2D::Translate(Bcx, Bcy);
				modelMatrix *= Transform2D::Rotate(BangularStep);
				modelMatrix *= Transform2D::Translate(-50, -50);
			}
			if (Bcx > resolution.x * .25f && Bcx <= resolution.x * .5f) {
				Bcx += deltaTimeSeconds * 200.f;
				Bcy -= deltaTimeSeconds * 200.f;
				printf("vX = %f   Y = %f N = %f  M = %f\n", Bcx, Bcy, resolution.x * .25f, resolution.x * .5f);
				if (Bcx >= resolution.x * .5f) {
					BmoveR = false;
					//printf("\n");
					Bcx = resolution.x * .5f;
				}
				BangularStep -= deltaTimeSeconds;
				modelMatrix *= Transform2D::Translate(Bcx, Bcy);
				modelMatrix *= Transform2D::Rotate(BangularStep);
				modelMatrix *= Transform2D::Translate(-50, -50);
			}
			
		}
		else {
			if (Bcx >= resolution.x * .25f && Bcx <= resolution.x * .5f) {
				Bcx -= deltaTimeSeconds * 200.f;
				Bcy += deltaTimeSeconds * 200.f;
				printf("pX = %f   Y = %f N = %f  M = %f\n", Bcx, Bcy, resolution.x * .25f, resolution.x * .5f);
				BangularStep += deltaTimeSeconds;
				modelMatrix *= Transform2D::Translate(Bcx, Bcy);
				modelMatrix *= Transform2D::Rotate(BangularStep);
				modelMatrix *= Transform2D::Translate(-50, -50);
			}
			if (Bcx <= resolution.x * .25f) {
				Bcx -= deltaTimeSeconds * 200.f;
				Bcy -= deltaTimeSeconds * 200.f;
				printf("yX = %f   Y = %f N = %f  M = %f\n", Bcx, Bcy, resolution.x * .25f, resolution.x * .5f);
				if (Bcx <= 0) {
					BmoveR = true;
				}
				BangularStep += deltaTimeSeconds;
				modelMatrix *= Transform2D::Translate(Bcx, Bcy);
				modelMatrix *= Transform2D::Rotate(BangularStep);
				modelMatrix *= Transform2D::Translate(-50, -50);
			}
		}
		//printf("X = %f   Y = %f  delta = %f  ang = %f res = %f\n", Bcx, Bcy, BangularStep, deltaTimeSeconds, resolution.x);
		RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);
	}
}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Laborator3::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{
}
