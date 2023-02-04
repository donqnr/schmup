#pragma once
#include "Projectile.h"

// Weapon class
// Player's ship is fitted with weapons that the player acquires throughout the game

class Weapon
{
public:
	Weapon();

	virtual bool CanFire();

	virtual void Fire();

protected:
	Projectile projectile; // Which projetile the weapon fires
	float firerate = 0.5f; // Cooldown time in seconds between shots
	float lastFiredAt = 0.0f; // 
	bool firing = false;

private:

};

