#include "Weapon.h"

Weapon::Weapon()
{

}

bool Weapon::CanFire()
{
	if (GetTime() > lastFiredAt + firerate) {
		return true;
	}
	return false;
}

void Weapon::Fire()
{
	lastFiredAt = GetTime();
}
