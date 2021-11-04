#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Goomba.h"

enum MushroomStates
{
	MUSHROOM_STATE_IDLE,
	MUSHROOM_STATE_DROP,
	MUSHROOM_STATE_BOUNCING,
};

enum MushroomTypes
{
	MUSHROOM_TYPE_RED,
	MUSHROOM_TYPE_GREEN,
};

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_SPEED 0.04f
#define MUSHROOM_BOUNCING_SPEED 0.4f

#define ID_ANI_RED_MUSHROOM  12110

class CMushroom : public CGameObject
{
	float ax;
	float ay;
	int width;
	int height;
	int type;
	float initialPositionY;

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
public:
	CMushroom(float x, float y, int width, int height, int type):CGameObject(x,y)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->type = type;
	}
	void SetState(int state);
	int GetType() { return this->type; }
};
