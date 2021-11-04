#pragma once

#include "GameObject.h"

class CBackground : public CGameObject
{
	int spriteId;
public:
	CBackground(float x, float y, int id_sprite) :CGameObject(x, y)
	{
		this->spriteId = id_sprite;
	}
	void Render();

	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

