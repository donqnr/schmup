#include <iostream>
#include "Ship.h"

Ship::Ship(float posX, float posY)
{
	pos = { posX,posY };
	velocity = { 0,0 };
	rect = { posX, posY, 32, 32 };
}

void Ship::Attack()
{
	//std::cout << "Pew";
}

void Ship::Tick(float delta)
{
	pos.x += velocity.x * delta;
	pos.y += velocity.y * delta;
	velocity.x = velocity.x / (1.0f + damping * delta);
	velocity.y = velocity.y / (1.0f + damping * delta);
	rect = { pos.x, pos.y, size.x, size.y };
}
