#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

#define LIMIT (.2f)
class Bow_and_Arrow : public SimpleScene
{
public:
	Bow_and_Arrow();
	~Bow_and_Arrow();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	void RenderArrow(float deltaTimeSeconds, float angle);
	void RenderPowerBar(float deltaTimeSeconds);
	void RenderScoreBar(float deltaTimeSeconds);
	int Random(bool forOY);
	void RenderRedBall(float deltaTimeSeconds);
	void RenderYellowBall(float deltaTimeSeconds);
	void RenderShuriken(float deltaTimeSeconds);
	void RenderBow(float deltaTimeSeconds);
	bool CheckBallToPointColision(float PointX, float PointY, float CenterX, float CenterY);
	bool CheckBallToBallColision(float PointX, float PointY, float CenterX, float CenterY);

protected:
	glm::mat3 modelMatrix;

	float redBallX, yellowBallX, redBallY, yellowBallY, redBallSpeed, yellowBallSpeed, shurikenSpeed;
	float translateX, translateY;
	float BowX, BowY;
	float arrowX, arrowY;
	float markX, markY;
	float mousePosX, mousePosY;
	float Bcx, Bcy;
	float angularStep, angle, ang;
	float power;
	float BangularStep;
	float cx, cy;
	float shurikenY, shurikenX;
	float scaleRedBallX, scaleRedBallY;
	float scaleYellowBallX, scaleYellowBallY;
	float scaleR, scaleY;
	int lifes;
	int score;
	int i;
	bool BmoveR, move, pulse, maxY, powerLimit, redBallOutOfScene, yellowBallOutOfScene, shurikenOutOfScene;
	bool colisionRedBall, colisionYellowBall, colisionShuriken, colisionBow;


};
