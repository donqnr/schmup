#pragma once

#include "raylib.h"
#include "Actor.h"
#include "Weapon.h"

class Ship : public Actor
{
public:
	Ship(World* wrld, float posX = 0.f, float posY = 0.f); // Initialize the actor, set default position to 0,0 if not specified

	void FireWeapons();	// Fire all regular weapons

	void Tick(float delta);

	Rectangle GetWallSensorUp();
	Rectangle GetWallSensorDn();
	Rectangle GetWallSensorLeft();
	Rectangle GetWallSensorRight();

	void SetWeapon(Weapon* wpn, int wpnSlot);

	Vector2* GetWeaponOffset(int slot);

	Weapon* GetWeapon(int slot); // Get weapon from the selected weapon slot.
	int GetWeaponAmount();

	void TakeDamage(int dmgTaken) override;
	
protected:

	struct WallSensor {
		Rectangle up;
		Rectangle right;
		Rectangle down;
		Rectangle left;
	};

	struct WeaponSlot {			// Where the ship's regular weapons go
		Vector2 offset = { 0,0 };	// The position where the bullets spawn from, relative to the ship. 0,0 is the center of the ship.
		Weapon* wep;				// The weapon class
	};
	WeaponSlot weapons[3];		// Array for the weapon slots, different ships can have a varying amount of slots that they can equip weapons to
	WallSensor sensor;

	

private:

	enum class State {
		Active,
		Death,
	};
	State currentState = State::Active;

};