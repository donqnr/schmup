#include <iostream>
#include "Ship.h"

Ship::Ship(float posX, float posY)
{
	pos = { posX,posY };
	velocity = { 0,0 };
	rect = { posX, posY, 32, 32 };
	weapons[0].offset = { 0, 16 };
	weapons[1].offset = { 24, 16 };
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
}

void Ship::SetWeapon(Weapon wpn, int wpnSlot)
{
	if (wpnSlot < std::size(weapons) && wpnSlot >= 0) {
		weapons[wpnSlot].wep = wpn;
	}
}

Vector2* Ship::GetWeaponOffset(int slot)
{
	return &weapons[slot].offset;
}

Weapon* Ship::GetWeapons()
{
	static Weapon wpns[2];
	for (int i = 0; i < std::size(weapons); i++) {
		
	}
	return wpns;
}

Weapon* Ship::GetWeapon(int slot)
{
	return &weapons[slot].wep;
}
