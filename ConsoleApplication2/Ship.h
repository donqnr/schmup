#pragma once

#include "raylib.h"
#include "Actor.h"
#include "Weapon.h"

class Ship : public Actor
{
public:
	Ship(float posX = 0.f, float posY = 0.f); // Initialize the actor, set default position to 0,0 if not specified

	void Attack();

	void TakeDamage(int dmgTaken);

	void Tick(float delta);
protected:

private:
	struct WeaponSlot {
		Vector2 offset = {0,0};
		Weapon wep;
	};
	WeaponSlot weapons[2];
	int maxHealth = 100;
	int health = 100;
};