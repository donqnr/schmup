
#include "Actor.h"

Actor::Actor(float posX, float posY)
{
	pos = { posX,posY };
	velocity = { 0,0 };
	rect = { posX, posY, 32, 32 };
}

Actor::Actor(World* wrld, float posX, float posY)
{
	pos = { posX,posY };
	velocity = { 0,0 };
	rect = { posX, posY, 32, 32 };
}

Actor::~Actor()
{
	UnloadTexture(spriteSheet);
}


Vector2 Actor::GetPosition()
{
	return pos;
}

Vector2 Actor::GetCenter()
{
	return {pos.x + (size.x * 0.5f),pos.y + (size.y * 0.5f)};
}

Vector2 Actor::GetVelocity()
{
	return velocity;
}

Vector2 Actor::GetSize()
{
	return size;
}

float Actor::GetAngle()
{
	return angle;
}

float Actor::GetAcceleration()
{
	return acceleration;
}

float Actor::GetDamping()
{
	return damping;
}

int Actor::GetHealth()
{
	return health;
}

World* Actor::GetWorld()
{
	return parentWorld;
}

bool Actor::IsActive()
{
	return active;
}

Rectangle Actor::GetRect()
{
	return rect;
}

Texture2D Actor::GetSprite()
{
	return spriteSheet;
}

void Actor::SetVelocity(Vector2 vel)
{
	velocity = vel;
}

void Actor::SetPosition(Vector2 newPos)
{
	pos = newPos;
}

void Actor::SetWorld(World* wrld)
{
	parentWorld = wrld;
}

void Actor::SetActive(bool a)
{
	active = a;
}


void Actor::MoveTo(float posX, float posY)
{
	pos = { posX,posY };
}

void Actor::MoveBy(float posX, float posY)
{
	pos.x += posX;
	pos.y += posY;
}

void Actor::RotateTo(float newAngle)
{
	angle = newAngle;
}

void Actor::RotateBy(float newAngle)
{
	angle += newAngle;
}

void Actor::Tick(float delta)
{

}

void Actor::Accelerate(Vector2 acc, float delta)
{
	velocity.x += acc.x * delta;
	velocity.y += acc.y * delta;
}

void Actor::Turn(float turnRate, float delta)
{
	RotateBy(turnRate * delta);
}

void Actor::TakeDamage(int dmgTaken)
{
	health = -dmgTaken;
}
