
#pragma once
#include "GameObject.h"
#include "Goomba.h"
#include "HollowPlatformBBox.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f


#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 24
#define KOOPA_BBOX_SHELL_HEIGHT 16

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_SHELL_STAND 200
#define KOOPA_STATE_SHELL_MOVE 201

#define ID_ANI_KOOPA_WALKING_LEFT 6000
#define ID_ANI_KOOPA_WALKING_RIGHT 6001
#define ID_ANI_KOOPA_SHELL_STAND 6002
#define ID_ANI_KOOPA_SHELL_MOVE 6003

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	float left, top, right, bot;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking();
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CKoopa(float x, float y, int state);
	virtual void SetState(int state);
	void SetShellStateMoveSpeedLeft();
	void SetShellStateMoveSpeedRight();
	void SetYWhenColide();
};