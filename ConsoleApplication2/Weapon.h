#pragma once
#include "Projectile.h"

// Weapon class
// Player's ship is fitted with weapons that the player acquires throughout the game

class Weapon
{
private:
	Projectile projectile; // Which projetile the weapon fires
	float firerate = 0.5; // Cooldown time in seconds between shots
};

