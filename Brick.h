#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Utils.h"

enum BrickStates
{
	BRICK_STATE_NORMAL,
	BRICK_STATE_QBRICK,
	BRICK_STATE_BBRICK,
	BRICK_STATE_BOUNCE,
	BRICK_STATE_BREAK,
	BRICK_STATE_SECRET,
};

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define ID_ANI_QBRICK 12100
#define ID_ANI_BBRICK 12200
#define ID_ANI_BREAK 12900

#define BRICK_BOUNCING_SPEED 0.2f
#define BRICK_BOUNCE_HEIGHT 12

#define NUMBER_OF_BOUNCE 5

class CBrick : public CGameObject 
{
	string item;
	float initial_y;
	int bouncesLeft;
public:
	CBrick(float x, float y, int state, string item = "");
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Get(float& x, float& y);
	virtual int GetBouncesLeft()
	{
		return bouncesLeft;
	}
	virtual bool NoItem()
	{
		return item == "";
	}
	int IsCollidable()
	{
		return 1;
	};
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
};