#include <iostream>
#include "Ship.h"

Ship::Ship(float posX, float posY)
{
	pos = { posX,posY };
	velocity = { 0,0 };
	rect = { posX, posY, 32, 32 };
	weapons[0].offset = { 0, 0 };
	weapons[1].offset = { 32, 0 };
	weapons[2].offset = { 16, 0 };

	sensor.up = { posX,posY + 1 ,rect.x - 2,1 };
	sensor.down = { posX,posY + rect.y + 1 ,rect.x - 2,1 };

}

void Ship::StartAttack()
{
	//std::cout << "Pew";
}

void Ship::EndAttack()
{
}

void Ship::Tick(float delta)
{
	pos.x += velocity.x * delta;
	pos.y += velocity.y * delta;
	velocity.x = velocity.x / (1.0f + damping * delta);
	velocity.y = velocity.y / (1.0f + damping * delta);
	rect = { pos.x, pos.y, size.x, size.y };
	sensor.up = { pos.x + 3,pos.y,size.x - 6, 1 };
	sensor.down = { pos.x + 3,pos.y + size.y,size.x - 6, 1 };
	sensor.left = { pos.x,pos.y + 3,1,size.y - 6 };
	sensor.right = { pos.x + size.x,pos.y + 3,1,size.y - 6 };
}

Rectangle Ship::GetWallSensorUp()
{
	return sensor.up;
}

Rectangle Ship::GetWallSensorDn()
{
	return sensor.down;
}

Rectangle Ship::GetWallSensorLeft()
{
	return sensor.left;
}

Rectangle Ship::GetWallSensorRight()
{
	return sensor.right;
}

void Ship::SetWeapon(Weapon* wpn, int wpnSlot)
{
	weapons[wpnSlot].wep = wpn;
}

Vector2* Ship::GetWeaponOffset(int slot)
{
	return &weapons[slot].offset;
}

Weapon* Ship::GetWeapon(int slot)
{
	return weapons[slot].wep;
}

int Ship::GetWeaponAmount()
{
	return std::size(weapons);
}
