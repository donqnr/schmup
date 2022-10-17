#pragma once

#include "raylib.h"
#include "Actor.h"
#include "Weapon.h"

class Ship : public Actor
{
public:
	Ship(float posX = 0.f, float posY = 0.f); // Initialize the actor, set default position to 0,0 if not specified

	void Attack();				// Fire all regular weapons

	

	void Tick(float delta);
protected:

private:
	struct WeaponSlot {			// Where the ship's regular weapons go
		Vector2 offset = {0,0};	// The position where the bullets spawn from, relative to the ship. 0,0 is the center of the ship.
		Weapon wep;				// The weapon class
	};
	WeaponSlot weapons[2];		// Array for the weapon slots, different ships can have a varying amount of equippable weapons
};