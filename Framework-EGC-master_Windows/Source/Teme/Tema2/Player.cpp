#include "Player.h"

#include <vector>
#include <iostream>
#include <Core/Engine.h>

using namespace std;

Player::Player(int x, int y, int z) {
	tX = x;
	tY = y;
	tZ = z;
}

void Player::update() {
	Skyroads s;
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.5f, -5));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1f, 10));
	s.RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0.5, 0));
}