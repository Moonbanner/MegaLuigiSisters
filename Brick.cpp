#include "Brick.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Utils.h"
#include "PlayScene.h"

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	int aniId = ID_ANI_BRICK;
	if (state == BRICK_STATE_QBRICK) aniId = ID_ANI_QBRICK;
	else if (state == BRICK_STATE_BBRICK) aniId = ID_ANI_BBRICK;
	else if (state == BRICK_STATE_BREAK) aniId = ID_ANI_BREAK;
	else if (state == BRICK_STATE_SECRET) return;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	RenderBoundingBox();
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	if (y <= initial_y - BRICK_BOUNCE_HEIGHT)
	{
		y = initial_y - BRICK_BOUNCE_HEIGHT;
		vy = BRICK_BOUNCING_SPEED;
	}
	if (y > initial_y)
	{
		y = initial_y;
		vy = 0;
		CGameObject* object = NULL;
		float x, y;
		Get(x, y);
		if (item == "red_mushroom") { object = new CMushroom(x, y, BRICK_BBOX_WIDTH, BRICK_BBOX_HEIGHT, MUSHROOM_TYPE_RED); }
		else if (item == "green_mushroom") { object = new CMushroom(x, y, BRICK_BBOX_WIDTH, BRICK_BBOX_HEIGHT, MUSHROOM_TYPE_GREEN); }
		else if (item == "") { return; }
		else
		{
			DebugOut(L"Item $s doesnt exist. \n", ToLPCWSTR(item));
			return;
		}
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(object);
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
}

void CBrick::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	float x_mushroom, y_mushroom;
	mushroom->GetPosition(x_mushroom, y_mushroom);
	if (e->ny > 0)
	{
		if (state == BRICK_STATE_BOUNCE &&
			state == BRICK_STATE_BREAK &&
			state == BRICK_STATE_BBRICK)
		{
			mushroom->SetState(MUSHROOM_STATE_BOUNCING);
			if (x_mushroom < x + 8) mushroom->SetSpeed(-MUSHROOM_SPEED, -MUSHROOM_BOUNCING_SPEED);
			else mushroom->SetSpeed(MUSHROOM_SPEED, -MUSHROOM_BOUNCING_SPEED);
		}
	}
}

void CBrick::Get(float& x, float& y)
{
	x = this->x;
	y = this->y;
}

void CBrick::SetState(int state)
{
	switch (state)
	{
	case BRICK_STATE_NORMAL:
		break;
	case BRICK_STATE_QBRICK:
		break;
	case BRICK_STATE_SECRET:
		break;
	case BRICK_STATE_BBRICK: case BRICK_STATE_BOUNCE:
		vy = -BRICK_BOUNCING_SPEED;
		bouncesLeft--;
		break;
	case BRICK_STATE_BREAK:
		break;
	}

	CGameObject::SetState(state);
}
