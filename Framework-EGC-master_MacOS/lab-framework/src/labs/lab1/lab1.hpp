#pragma once

#include <component/SimpleScene.h>
#include "object.hpp"

#define DEFAULT_CLEAR_R 0
#define DEFAULT_CLEAR_G 0
#define DEFAULT_CLEAR_B 0

#define trans_factor 0.5f

class Laborator1 : public SimpleScene
{
	public:
		Laborator1();
		~Laborator1();

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
private:
  float clear_r, clear_g, clear_b;
  bool clear_changed;
  Object to_render;
  float pos_x, pos_y, pos_z;
  bool update_pos_x, update_neg_x;
  bool update_pos_y, update_neg_y;
  bool update_pos_z, update_neg_z;
  float speed_factor;
};
