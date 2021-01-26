#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#define scaleFactorX 1.f
#define scaleFactorY 0.1f
#define scaleFactroZ 10.f

class Player {

public:
	int tX, tY, tZ;
	Player(int x, int y, int z);

	void update();
};

