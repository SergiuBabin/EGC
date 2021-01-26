#include "Bow_and_Arrow.h"

#include <vector>
#include <iostream>
#include <time.h> 
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Player.h"

using namespace std;

Bow_and_Arrow::Bow_and_Arrow()
{
}

Bow_and_Arrow::~Bow_and_Arrow()
{
}

void Bow_and_Arrow::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	printf("X = %f     Y = %f  ", (float)resolution.x, (float)resolution.y);
	glm::vec3 corner = glm::vec3(0, 0, 0);
	glm::vec3 corn = glm::vec3(50, -10, 0);
	float squareSide = 100;


	// compute coordinates of square center
	cx = corner.x + squareSide / 2;
	cy = corner.y + squareSide / 2;
	Bcx = corner.x + squareSide / 2;
	Bcy = corner.y + squareSide / 2;
	move = false;
	BmoveR = true;
	pulse = true;
	maxY = true;

	redBallOutOfScene = true;
	yellowBallOutOfScene = true;
	shurikenOutOfScene = true;

	colisionRedBall = false; 
	colisionYellowBall = false; 
	colisionShuriken = false;
	colisionBow = false;

	scaleRedBallX = 1;
	scaleRedBallY = 1;

	scaleYellowBallX = 1;
	scaleYellowBallY = 1;

	angle = 0;
	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 150;

	BowX = 10;
	BowY = 250;

	arrowX = BowX;
	arrowY = BowY;

	redBallX = 0;
	yellowBallX = 0;
	shurikenX = 0;

	redBallY = 0;
	yellowBallY = 0;
	shurikenY = 0;


	scaleR = 1;
	scaleY = 1;
	// initialize angularStep
	angularStep = 0;
	BangularStep = 0;

	lifes = 3;

	score = 1;

	powerLimit = false;

	Mesh* line = Player::CreateLine("line", glm::vec3(0, 0, 0), glm::vec3(50, 0, 0), glm::vec3(51, 25, 0));
	AddMeshToList(line);

	Mesh* arrow1 = Player::CreateArrow("arrow1", corn, 20, glm::vec3(0, 102, 102));
	AddMeshToList(arrow1);

	Mesh* halfCircle = Player::CreateHalfCircle("halfCircle", corner, 30, glm::vec3(51, 25, 0));
	AddMeshToList(halfCircle);

	Mesh* line1 = Player::CreateLine("line1", glm::vec3(0, sin(3 * M_PI_2) * 70, 0), glm::vec3(cos(5 * M_PI_2) * 40, sin(5 * M_PI_2) * 70, 0), glm::vec3(51, 25, 0));
	AddMeshToList(line1);

	Mesh* YellowBall = Player::CreateCircle("YellowBall", corner, 100, glm::vec3(1, 1, 0));
	AddMeshToList(YellowBall);

	Mesh* lineYellow = Player::CreatePolyline("lineYellow", glm::vec3(20, sin(3 * M_PI_2) * 30, 0), 30, glm::vec3(1, 1, 0));
	AddMeshToList(lineYellow);

	Mesh* RedBall = Player::CreateCircle("RedBall", corner, 100, glm::vec3(1, 0, 0), false);
	AddMeshToList(RedBall);

	Mesh* lineRed = Player::CreatePolyline("lineRed", glm::vec3(20, sin(3 * M_PI_2) * 30, 0), 30, glm::vec3(1, 0, 0));
	AddMeshToList(lineRed);

	Mesh* shuriken = Player::CreateShuriken("shuriken", corner, 30, glm::vec3(204, 0, 102));
	AddMeshToList(shuriken);

	Mesh* powerBar = Player::CreateSquare("powerBar", corner, 10, glm::vec3(1, 0, 1), true);
	AddMeshToList(powerBar);

	Mesh* scoreBar = Player::CreateSquare("scoreBar", corner, 10, glm::vec3(1, 1, 1), true);
	AddMeshToList(scoreBar);
}

void Bow_and_Arrow::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Bow_and_Arrow::Update(float deltaTimeSeconds)
{
	if (lifes == 0) {
		deltaTimeSeconds = 0;
	}

	angle = (mousePosY + mousePosX == 0) ? 0 : atan((mousePosY - BowY) / (mousePosX - BowX));

	RenderArrow(deltaTimeSeconds, angle);

	RenderPowerBar(deltaTimeSeconds);

	RenderRedBall(deltaTimeSeconds);

	RenderYellowBall(deltaTimeSeconds);

	RenderBow(deltaTimeSeconds);

	RenderShuriken(deltaTimeSeconds);

	RenderScoreBar(deltaTimeSeconds);
}

void Bow_and_Arrow::RenderRedBall(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	if (CheckBallToPointColision(arrowX + 50, arrowY, redBallX, redBallY) || colisionRedBall) {
		colisionRedBall = true;
		scaleRedBallX -= deltaTimeSeconds;
		scaleRedBallY -= deltaTimeSeconds;
		scaleR = 0;

		if (scaleRedBallX <= 0) {
			colisionRedBall = false;
			scaleRedBallX = 1;
			scaleRedBallY = 1;
			redBallY = 0;
			redBallOutOfScene = true;
			scaleR = 1;
			score++;
		}

	}

	if (!colisionRedBall) {
		if (resolution.y <= redBallY) {
			redBallY = 0;
			redBallOutOfScene = true;
		}

		if (redBallOutOfScene) {
			redBallX = (float)Random(false);
			redBallSpeed = 100 + (rand() % 200);
			redBallOutOfScene = false;
		}

		redBallY += deltaTimeSeconds * redBallSpeed;
	}


	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(redBallX, redBallY);
	modelMatrix *= Transform2D::Scale(scaleRedBallX, scaleRedBallY);
	RenderMesh2D(meshes["RedBall"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(redBallX, redBallY);
	modelMatrix *= Transform2D::Scale(scaleR, scaleR);
	RenderMesh2D(meshes["lineRed"], shaders["VertexColor"], modelMatrix);

}

void Bow_and_Arrow::RenderYellowBall(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();
	if (CheckBallToPointColision(arrowX + 50, arrowY, yellowBallX, yellowBallY) || colisionYellowBall) {
		colisionYellowBall = true;
		scaleYellowBallX -= deltaTimeSeconds;
		scaleYellowBallY -= deltaTimeSeconds;
		scaleY = 0;

		if (scaleYellowBallX <= 0) {
			colisionYellowBall = false;
			scaleYellowBallX = 1;
			scaleYellowBallY = 1;
			yellowBallY = 0;
			yellowBallOutOfScene = true;
			scaleY = 1;
			score--;
		}

	}

	if (!colisionYellowBall) {
		if (resolution.y <= yellowBallY) {
			yellowBallY = 0;
			yellowBallOutOfScene = true;
		}

		if (yellowBallOutOfScene) {
			yellowBallX = (float)Random(false);
			yellowBallSpeed = 100 + (rand() % 200);
			yellowBallOutOfScene = false;
		}


		yellowBallY += deltaTimeSeconds * yellowBallSpeed;
	}



	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(yellowBallX, yellowBallY);
	modelMatrix *= Transform2D::Scale(scaleYellowBallX, scaleYellowBallY);
	RenderMesh2D(meshes["YellowBall"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(yellowBallX, yellowBallY);
	modelMatrix *= Transform2D::Scale(scaleY, scaleY);
	RenderMesh2D(meshes["lineYellow"], shaders["VertexColor"], modelMatrix);

}

void Bow_and_Arrow::RenderShuriken(float deltaTimeSeconds) 
{
	glm::ivec2 resolution = window->GetResolution();

	if (CheckBallToPointColision(arrowX + 50, arrowY, shurikenX, shurikenY) && shurikenX > 100 || colisionShuriken) {
		colisionShuriken = true;
		shurikenY -= deltaTimeSeconds * 200;
		if (shurikenY <= 0) {
			colisionShuriken = false;
			shurikenX = resolution.x;
			shurikenOutOfScene = true;
		}

	}

	if (!colisionShuriken) {
		if (0 >= shurikenX) {
			shurikenX = resolution.x;
			shurikenOutOfScene = true;
		}

		if (shurikenOutOfScene) {
			shurikenY = (float)Random(true);
			shurikenSpeed = 100 + (rand() % 200);
			shurikenOutOfScene = false;
		}

		shurikenX -= deltaTimeSeconds * shurikenSpeed;
		angularStep += deltaTimeSeconds * 3;
	}

	

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(shurikenX, shurikenY);
	modelMatrix *= Transform2D::Rotate(angularStep);
	RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);
}

void Bow_and_Arrow::RenderBow(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();
	if (CheckBallToBallColision(shurikenX, shurikenY, BowX, BowY)) {
		shurikenX = resolution.x;
		shurikenOutOfScene = true;
		lifes--;
	}

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(BowX, BowY);
	modelMatrix *= Transform2D::Rotate(angle);
	RenderMesh2D(meshes["halfCircle"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(BowX, BowY);
	modelMatrix *= Transform2D::Rotate(angle);
	RenderMesh2D(meshes["line1"], shaders["VertexColor"], modelMatrix);
}

void Bow_and_Arrow::RenderArrow(float deltaTimeSeconds, float angl) 
{
	if (move) {
		angl = ang;
		arrowX += deltaTimeSeconds * sqrt(power) * 100 * cos(ang);
		arrowY += deltaTimeSeconds * sqrt(power) * 100 * sin(ang);
		
		glm::ivec2 resolution = window->GetResolution();
		if (arrowX < 0 || arrowX > resolution.x
			|| arrowY < 0 || arrowY > resolution.y) {
			move = false;
			power = 2;
		}

	} else {

		arrowX = BowX;
		arrowY = BowY;
		
		
	}

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(arrowX, arrowY);
	modelMatrix *= Transform2D::Rotate(angl);
	RenderMesh2D(meshes["line"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(arrowX, arrowY);
	modelMatrix *= Transform2D::Rotate(angl);
	RenderMesh2D(meshes["arrow1"], shaders["VertexColor"], modelMatrix);

}

bool Bow_and_Arrow::CheckBallToPointColision(float PointX, float PointY, float CenterX, float CenterY)
{
	if (pow(PointX - CenterX, 2) / pow(30, 2) + pow(PointY - CenterY, 2) / pow(40, 2) <= 1) {
		return true;
	}
	return false;
}

bool Bow_and_Arrow::CheckBallToBallColision(float PointX, float PointY, float CenterX, float CenterY)
{
	float dx = PointX - CenterX;
	float dy = PointY - CenterY;
	if (sqrt(dx * dx + dy * dy) < 70 + 30) {
		return true;
	}
	return false;
}

void Bow_and_Arrow::RenderPowerBar(float deltaTimeSeconds) 
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT) && !move) {
		if (!powerLimit) {
			if (power > 100) {
				powerLimit = true;
			}
			power += deltaTimeSeconds * 70;
		}
		else {
			if (power < 2) {
				powerLimit = false;
			}
			power -= deltaTimeSeconds * 70;
		}
	}
	
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(20, 20);
	modelMatrix *= Transform2D::Scale(power, 1);
	RenderMesh2D(meshes["powerBar"], shaders["VertexColor"], modelMatrix);
}

void Bow_and_Arrow::RenderScoreBar(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();
	if (score >= 0) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(20, resolution.y - 20);
		modelMatrix *= Transform2D::Scale(score, 1);
		RenderMesh2D(meshes["scoreBar"], shaders["VertexColor"], modelMatrix);
	} else {
		lifes--;
		score = 5;
	}

}

int Bow_and_Arrow::Random(bool forOY) {
	glm::ivec2 resolution = window->GetResolution();
	if (forOY) {
		return  resolution.y / 2 + (rand() % resolution.y / 2 - 50);
	}
	else {
		return  resolution.x / 2 + (rand() % resolution.x / 2 - 50);
	}
}

void Bow_and_Arrow::FrameEnd()
{

}

void Bow_and_Arrow::OnInputUpdate(float deltaTime, int mods)
{
	glm::ivec2 resolution = window->GetResolution();

	if (window->KeyHold(GLFW_KEY_W))
	{
		if (BowY <= resolution.y - 80)
				BowY += 100*deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_S))
	{	
		if (BowY >= 90)
			BowY -= 100*deltaTime;
	}
}


void Bow_and_Arrow::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Bow_and_Arrow::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Bow_and_Arrow::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	
	glm::ivec2 resolution = window->GetResolution();
	mousePosX = mouseX;
	mousePosY = resolution.y - mouseY;

}

void Bow_and_Arrow::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event

}

void Bow_and_Arrow::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	markX = mouseX;
	markY = mouseY;

	if (!move) {
		ang = angle;
	}

	move = true;

}

void Bow_and_Arrow::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Bow_and_Arrow::OnWindowResize(int width, int height)
{
}
