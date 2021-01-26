#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>
#include "LabCamera.h"

#define Z_FAR (100.f) 
#define Z_NEAR (.01f)

class Ground {

public:
	float tX, tY, tZ;
	glm::vec3 color;
	glm::vec3 startColor;
	glm::vec3 scale;
	float scaleZ;
	float minX, minY, minZ;
	float maxX, maxY, maxZ;

	Ground() {

	}


	Ground(float x, float y, float z, glm::vec3 c, glm::vec3 s) {
		tX = x;
		tY = y;
		tZ = z;
		color = c;
		startColor = c;
		scale = s;
		scaleZ = s.z;
	}

	void Update(float deltaTimeSeconds) {
		tZ += deltaTimeSeconds;
		minX = tX - 0.5f;
		maxX = tX + 0.5f;
		minY = tY - 0.05f;
		maxY = tY + 0.05f;
		minZ = tZ - scaleZ / 2;
		maxZ = tZ + scaleZ / 2;
	}
}; 

class Skyroads : public SimpleScene
{
	public:
		Skyroads();
		~Skyroads();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color = glm::vec3(1));
		void RenderSphereMesh(Mesh* mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3& color = glm::vec3(1));
		void RenderStaticMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1));

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		
		bool intersect(glm::vec3 sphere, Ground box);

		glm::vec3 lightPosition;
		bool space, up, down, gameOver, onPlatform;
		float speed;
		float speedPlatform;
		int lives;
		float petrol;
		bool redPlatform, yellowPlatform, orangePlatform, greenPlatform;
		bool onRed;

		int counter;
		unsigned int materialShininess;
		float materialKd;
		float materialKs;
		std::vector<Ground> platforms;
		std::vector<Ground> platformsUpdate;
	protected:
		Skyroad::Camer* camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
		int renderCamera;
		bool perspective;
		float right, left, bottom, top, fov;
};
