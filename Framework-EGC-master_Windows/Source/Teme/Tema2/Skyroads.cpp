#include "Skyroads.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>    // std::max
#include <Core/Engine.h>
#include "Object2D.h"
#include "Transform2D.h"
#include "LabCamera.h"
using namespace std;

Skyroads::Skyroads()
{
}

Skyroads::~Skyroads()
{
}

void Skyroads::Init()
{
	renderCameraTarget = false;
	perspective = true;

	right = 10.f;
	left = .01f;
	bottom = .01f;
	top = 10.f;
	fov = 60.f;

	camera = new Skyroad::Camer();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	
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
		Mesh* mesh = new Mesh("heart");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "heart.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("plane");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "plane50.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* square2 = Object2D::CreateSquare("square2", glm::vec3(0, 0, -0.9f), 0.3f, glm::vec3(1, 1, 1), true);
		AddMeshToList(square2);
	}
	{
		Mesh* square3 = Object2D::CreateSquare("square3", glm::vec3(0, 0, -0.8f), 0.3f, glm::vec3(0.9, 0.5, 0.1), true);
		AddMeshToList(square3);
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderLab7");
		shader->AddShader("Source/Teme/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Teme/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("SphereShader");
		shader->AddShader("Source/Teme/Tema2/Shaders/SphereVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Teme/Tema2/Shaders/SphereFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	space = true;
	up = false;
	down = true;
	gameOver = false;
	onPlatform = false;

	onRed = false;

	redPlatform = false;
	orangePlatform = false;
	yellowPlatform = false;
	greenPlatform = false;

	renderCamera = 0;

	lives = 3;
	counter = 0;
	speedPlatform = 1.5f;

	petrol = 9;

	platforms = { 
		//blue
		Ground(-1.5f, 0.5f, 0, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 4)),
		Ground( 0.0f, 0.5f, 0, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 5)),
		Ground( 1.5f, 0.5f, 0, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 6)),

		Ground(-1.5f, 0.5f, -5, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 8)),
		Ground( 0.0f, 0.5f, -6, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 9)),
		Ground( 1.5f, 0.5f, -3, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 2)),

		//red
		Ground(-1.5f, 0.5f, -25, glm::vec3(1, 0, 0), glm::vec3(1, 0.1f, 5)),
		Ground( 0.0f, 0.5f, -27, glm::vec3(1, 0, 0), glm::vec3(1, 0.1f, 3)),
		Ground( 1.5f, 0.5f, -27, glm::vec3(1, 0, 0), glm::vec3(1, 0.1f, 8)),

		Ground(-1.5f, 0.5f, -25, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 4)),
		Ground( 0.0f, 0.5f, -27, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 4)),
		Ground( 1.5f, 0.5f, -27, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 3)),

		//yellow
		Ground(-1.5f, 0.5f, -25, glm::vec3(1, 1, 0), glm::vec3(1, 0.1f, 5)),
		Ground( 0.0f, 0.5f, -27, glm::vec3(1, 1, 0), glm::vec3(1, 0.1f, 4)),
		Ground( 1.5f, 0.5f, -27, glm::vec3(1, 1, 0), glm::vec3(1, 0.1f, 3)),

		Ground(-1.5f, 0.5f, -25, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 4)),
		Ground( 0.0f, 0.5f, -27, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 8)),
		Ground( 1.5f, 0.5f, -27, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 9)),
		
		//orange
		Ground(-1.5f, 0.5f, -25, glm::vec3(1, 0.5f, 0), glm::vec3(1, 0.1f, 4)),
		Ground( 0.0f, 0.5f, -27, glm::vec3(1, 0.5f, 0), glm::vec3(1, 0.1f, 5)),
		Ground( 1.5f, 0.5f, -27, glm::vec3(1, 0.5f, 0), glm::vec3(1, 0.1f, 8)),

		Ground(-1.5f, 0.5f, -25, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 4)),
		Ground( 0.0f, 0.5f, -27, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 3)),
		Ground( 1.5f, 0.5f, -27, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 6)),

		//green
		Ground(-1.5f, 0.5f, -25, glm::vec3(0, 1, 0), glm::vec3(1, 0.1f, 6)),
		Ground( 0.0f, 0.5f, -27, glm::vec3(0, 1, 0), glm::vec3(1, 0.1f, 8)),
		Ground( 1.5f, 0.5f, -27, glm::vec3(0, 1, 0), glm::vec3(1, 0.1f, 7)),

		Ground(-1.5f, 0.5f, -25, glm::vec3(0, 1, 0), glm::vec3(1, 0.1f, 4)),
		Ground( 0.0f, 0.5f, -27, glm::vec3(0, 1, 0), glm::vec3(1, 0.1f, 3)),
		Ground( 1.5f, 0.5f, -27, glm::vec3(0, 1, 0), glm::vec3(1, 0.1f, 6)),

		Ground(-1.5f, 0.5f, -25, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 7)),
		Ground( 0.0f, 0.5f, -27, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 8)),
		Ground( 1.5f, 0.5f, -27, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 5)),

		Ground(-1.5f, 0.5f, 0, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 4)),
		Ground(0.0f, 0.5f, 0, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 5)),
		Ground(1.5f, 0.5f, 0, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 2)),

		Ground(-1.5f, 0.5f, -5, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 8)),
		Ground(0.0f, 0.5f, -6, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 9)),
		Ground(1.5f, 0.5f, -3, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 2)),

		//red
		Ground(-1.5f, 0.5f, -25, glm::vec3(1, 0, 0), glm::vec3(1, 0.1f, 5)),
		Ground(0.0f, 0.5f, -27, glm::vec3(1, 0, 0), glm::vec3(1, 0.1f, 3)),
		Ground(1.5f, 0.5f, -27, glm::vec3(1, 0, 0), glm::vec3(1, 0.1f, 8)),

		Ground(-1.5f, 0.5f, -25, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 4)),
		Ground(0.0f, 0.5f, -27, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 4)),
		Ground(1.5f, 0.5f, -27, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 3)),

		//yellow
		Ground(-1.5f, 0.5f, -25, glm::vec3(1, 1, 0), glm::vec3(1, 0.1f, 5)),
		Ground(0.0f, 0.5f, -27, glm::vec3(1, 1, 0), glm::vec3(1, 0.1f, 4)),
		Ground(1.5f, 0.5f, -27, glm::vec3(1, 1, 0), glm::vec3(1, 0.1f, 3)),

		Ground(-1.5f, 0.5f, -25, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 4)),
		Ground(0.0f, 0.5f, -27, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 8)),
		Ground(1.5f, 0.5f, -27, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 9)),

		//orange
		Ground(-1.5f, 0.5f, -25, glm::vec3(1, 0.5f, 0), glm::vec3(1, 0.1f, 4)),
		Ground(0.0f, 0.5f, -27, glm::vec3(1, 0.5f, 0), glm::vec3(1, 0.1f, 5)),
		Ground(1.5f, 0.5f, -27, glm::vec3(1, 0.5f, 0), glm::vec3(1, 0.1f, 8)),

		Ground(-1.5f, 0.5f, -25, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 4)),
		Ground(0.0f, 0.5f, -27, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 3)),
		Ground(1.5f, 0.5f, -27, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 6)),

		//green
		Ground(-1.5f, 0.5f, -25, glm::vec3(0, 1, 0), glm::vec3(1, 0.1f, 6)),
		Ground(0.0f, 0.5f, -27, glm::vec3(0, 1, 0), glm::vec3(1, 0.1f, 8)),
		Ground(1.5f, 0.5f, -27, glm::vec3(0, 1, 0), glm::vec3(1, 0.1f, 7)),

		Ground(-1.5f, 0.5f, -25, glm::vec3(0, 1, 0), glm::vec3(1, 0.1f, 4)),
		Ground(0.0f, 0.5f, -27, glm::vec3(0, 1, 0), glm::vec3(1, 0.1f, 3)),
		Ground(1.5f, 0.5f, -27, glm::vec3(0, 1, 0), glm::vec3(1, 0.1f, 6)),

		Ground(-1.5f, 0.5f, -25, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 7)),
		Ground(0.0f, 0.5f, -27, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 8)),
		Ground(1.5f, 0.5f, -27, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 5))
	};

	platformsUpdate = {
		Ground(-1.5f, 0.5f, 0, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 15)),
		Ground(0.0f, 0.5f, 0, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 15)),
		Ground(1.5f, 0.5f, 0, glm::vec3(0, 0, 1), glm::vec3(1, 0.1f, 15))
	};

	for (int i = 3; i < 24; i++) {
		int v = rand() % 66;
		platformsUpdate.push_back(platforms[v]);
		platformsUpdate[i].tZ = platformsUpdate[i - 3].tZ - (platformsUpdate[i].scaleZ + platformsUpdate[i - 3].scaleZ)/2 - ((float)(v/33)+ 0.5f);
		platformsUpdate[i].tX = platformsUpdate[i - 3].tX;
	}

	//Light & material properties
	{
		lightPosition = glm::vec3(0, 2, 0);
		materialShininess = 30;
		materialKd = 0.5;
		materialKs = 0.5;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}

void Skyroads::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);	
}


void Skyroads::Update(float deltaTimeSeconds)
{	
	for (int i = 0; i < lives; i++){
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(3 - i, 2, -1.f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-90.0f), glm::vec3(1, 0, 0));
		RenderStaticMesh(meshes["heart"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
	}

	{
		glm::mat3 modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(-3.5f, 2);
		modelMatrix *= Transform2D::Scale(9, 0.8f);
		RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
	}

	{
		glm::mat3 modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(-3.5f, 2);
		modelMatrix *= Transform2D::Scale(petrol, 0.6f);
		RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
	}
	
	int press = -1;

	for (int k = 0; k < platformsUpdate.size(); k++) {

		if (platformsUpdate[k].tZ > 10) {
			platformsUpdate.erase(platformsUpdate.begin() + k);

			petrol -= 0.1f;
			if (orangePlatform == true) {
				counter++;
				speedPlatform = 8.f;
			}

			if (k != 0) {
				k--;
			}
			int v = rand() % 66;
			platformsUpdate.push_back(platforms[v]);
			platformsUpdate[23].tZ = platformsUpdate[23 - 3].tZ - (platformsUpdate[23].scaleZ + platformsUpdate[23 - 3].scaleZ) / 2 - ((float)(v / 33) + 0.5f);
			platformsUpdate[23].tX = platformsUpdate[23 - 3].tX;
		}

		if (lightPosition.y > 0.69f && down == true && up == false) {
			lightPosition.y -= deltaTimeSeconds * 0.01f * speed;
			speed += 0.02f;
		} else {
			if (lightPosition.y <= 0.69f && down == true) {
				down = false;
				space = false;
			}
		}

		if (lightPosition.y < 1.3f && up == true && down == false  && space == true) {
			lightPosition.y -= deltaTimeSeconds * 0.01f * speed;
			speed -= 0.03f;
		} else {
			if (lightPosition.y >= 1.3f) {
				up = false;
				down = true;
			}
		}


		if (intersect(lightPosition, platformsUpdate[k])) {
			if (platformsUpdate[k].startColor == glm::vec3(1, 0, 0) && onRed == false) {
				redPlatform = true;
				onRed = true;
			}

			if (platformsUpdate[k].startColor == glm::vec3(1, 1, 0) && onRed == false) {
				yellowPlatform = true;
				onRed = true;
			}

			if (platformsUpdate[k].startColor == glm::vec3(1, 0.5f, 0) && onRed == false) {
				orangePlatform = true;
				onRed = true;
			}

			if (platformsUpdate[k].startColor == glm::vec3(0, 1, 0) && onRed == false) {
				greenPlatform = true;
				onRed = true;
			}

			platformsUpdate[k].color = glm::vec3(0.5f, 0, 0.5f);
			press = k;
			
		} else {
			platformsUpdate[k].color = platformsUpdate[k].startColor;
		}
		
		platformsUpdate[k].Update(deltaTimeSeconds * speedPlatform);
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(platformsUpdate[k].tX, platformsUpdate[k].tY, platformsUpdate[k].tZ));
			modelMatrix = glm::scale(modelMatrix, platformsUpdate[k].scale);
			RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, platformsUpdate[k].color);
		}
	}

	if (renderCamera == 1) {
		camera->Set(glm::vec3(lightPosition.x, lightPosition.y + 0.1, lightPosition.z - 0.3f - 0.2f),
			glm::vec3(lightPosition.x, lightPosition.y + 0.1, lightPosition.z - 0.3f - 0.3), glm::vec3(0, 1, 0));    // first     
	} else {         
		camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0)); // thid    
	}

	if (press != -1) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, lightPosition);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f));
		RenderSphereMesh(meshes["sphere"], shaders["SphereShader"], modelMatrix, glm::vec3(1, 0.9f, 0));
	}
	else {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, lightPosition);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0.9f, 0));
	}
	//cout << press;
	if (redPlatform == true) {
		lives--;
		cout << "You have " << lives << " lives" << "\n";
		redPlatform = false;
	}

	if (petrol <= 0.2f) {
		lives--;
		cout << "You have " << lives << " lives" << "\n";
		cout << "you are refueled " << "\n";
		petrol = 9;
	}

	if (yellowPlatform == true) {
		petrol -= petrol / 10.f;
		yellowPlatform = false;
	}

	if (greenPlatform == true) {
		petrol += petrol / 10.f;
		petrol = (petrol <= 9) ? petrol : 9;
		greenPlatform = false;
	}

	//cout << counter;
	if (counter > 20) {
		orangePlatform = false;
		counter = 0;
		speedPlatform = 1.5f;
	}


	if (press == -1 && lightPosition.y < 0.69f) {
		gameOver = true;
	} else if (press != -1) {
		gameOver = false;
	}

	if (gameOver == true || lightPosition.y <= 0.59f) {
		lightPosition.y -= 2 * deltaTimeSeconds;
	}

	if (lightPosition.y <= 0.f || lives <= 0) {
		cout << "==========================    GAME OVER   ======================\n";
		exit(1);
	}

	if (lightPosition.y > 0.79f) {
		onRed = false;
	}
}

bool Skyroads::intersect(glm::vec3 sphere, Ground box) {
	// get box closest point to sphere center by clamping

	float x = max(box.minX, min(sphere.x, box.maxX));
	float y = max(box.minY, min(sphere.y, box.maxY));
	float z = max(box.minZ, min(sphere.z, box.maxZ));

	// this is the same as isPointInsideSphere
	float distance = sqrt((x - sphere.x) * (x - sphere.x) +
		(y - sphere.y) * (y - sphere.y) +
		(z - sphere.z) * (z - sphere.z));

	return distance <= 0.3f/2;
}


void Skyroads::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Skyroads::RenderStaticMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Set shader uniforms for light & material properties
	// TODO: Set light position uniform
	glUniform3fv(glGetUniformLocation(shader->program, "light_position"), 1, glm::value_ptr(lightPosition));

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = GetSceneCamera()->transform->GetWorldPosition();
	glUniform3fv(glGetUniformLocation(shader->program, "eye_position"), 1, glm::value_ptr(eyePosition));

	// TODO: Set material property uniforms (shininess, kd, ks, object color) 
	glUniform1f(glGetUniformLocation(shader->program, "material_shininess"), (float)materialShininess);
	glUniform1f(glGetUniformLocation(shader->program, "material_kd"), materialKd);
	glUniform1f(glGetUniformLocation(shader->program, "material_ks"), materialKs);
	glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	int time = glGetUniformLocation(shader->GetProgramID(), "Time");
	glUniform1f(time, (float)Engine::GetElapsedTime());

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Skyroads::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Set shader uniforms for light & material properties
	// TODO: Set light position uniform
	glUniform3fv(glGetUniformLocation(shader->program, "light_position"), 1, glm::value_ptr(lightPosition)); 

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = GetSceneCamera()->transform->GetWorldPosition();
	glUniform3fv(glGetUniformLocation(shader->program, "eye_position"), 1, glm::value_ptr(eyePosition));

	// TODO: Set material property uniforms (shininess, kd, ks, object color) 
	glUniform1f(glGetUniformLocation(shader->program, "material_shininess"), (float)materialShininess);
	glUniform1f(glGetUniformLocation(shader->program, "material_kd"), materialKd);
	glUniform1f(glGetUniformLocation(shader->program, "material_ks"), materialKs);
	glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	
	// Bind view matrix
	glm::mat4 viewMatrix =	camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	int time = glGetUniformLocation(shader->GetProgramID(), "Time");
	glUniform1f(time, (float)Engine::GetElapsedTime());

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Skyroads::RenderSphereMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	int time = glGetUniformLocation(shader->GetProgramID(), "time");
	glUniform1f(time, (float)Engine::GetElapsedTime());

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Skyroads::OnInputUpdate(float deltaTime, int mods)
{
	float sp = 1.5;

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glm::vec3 upp = glm::vec3(0, 1, 0);
		glm::vec3 right = GetSceneCamera()->transform->GetLocalOXVector();
		glm::vec3 forward = GetSceneCamera()->transform->GetLocalOZVector();
		forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));

		// Control light position using on W, A, S, D, E, Q
		if (window->KeyHold(GLFW_KEY_W) && speedPlatform < 3) { 
			speedPlatform += 0.07f;
		}

		if (window->KeyHold(GLFW_KEY_A)) lightPosition -= right * deltaTime * sp;

		if (window->KeyHold(GLFW_KEY_S) && speedPlatform > 1) {
			speedPlatform -= 0.07f;
		}

		if (window->KeyHold(GLFW_KEY_D)) lightPosition += right * deltaTime * sp;
		if (window->KeyHold(GLFW_KEY_E)) lightPosition += upp * deltaTime * sp;
		if (window->KeyHold(GLFW_KEY_Q)) lightPosition -= upp * deltaTime * sp;
	}
}

void Skyroads::OnKeyPress(int key, int mods)
{
	// add key press event
	if (space == false && key == GLFW_KEY_SPACE && lightPosition.y >= 0.59f) {
		space = true;
		speed = 1;
		up = true;
		down = false; 
	}

	if (key == GLFW_KEY_C) {
		renderCamera ^= 1;
	}
}

void Skyroads::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Skyroads::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Skyroads::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Skyroads::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Skyroads::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Skyroads::OnWindowResize(int width, int height)
{
}
