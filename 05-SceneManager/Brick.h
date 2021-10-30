#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject {
public:
	int ID_ANI_BRICK;
	CBrick(float x, float y, int ID_ANI_BRICK) : CGameObject(x, y) 
	{
		this->ID_ANI_BRICK = ID_ANI_BRICK;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};