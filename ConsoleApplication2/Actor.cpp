#include <iostream>
#include "Actor.h"

Actor::Actor(float posX, float posY)
{
	pos = { posX,posY };
	velocity = { 0,0 };
	rect = { posX, posY, 32, 32 };
}

Vector2 Actor::GetPosition()
{
	return pos;
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

bool Actor::isActive()
{
	return active;
}

void Actor::setActive(bool a)
{
	active = a;
}

Rectangle Actor::GetRect()
{
	return rect;
}

Texture2D Actor::GetSprite()
{
	return spriteSheet;
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
