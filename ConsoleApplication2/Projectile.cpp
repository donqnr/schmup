#include "Projectile.h"

Projectile::Projectile(float posX, float posY)
{
	pos = { posX,posY };
	velocity = { 0,0 };
	rect = { posX, posY, 8, 8 };
	spawnTime = GetTime();
}

Projectile::Projectile(World* wrld, float posX, float posY)
{
	pos = { posX,posY };
	velocity = { 0,0 };
	rect = { posX, posY, 8, 8 };
	parentWorld = wrld;
	spawnTime = GetTime();
}

void Projectile::Tick(float delta)
{
	pos.y -= speed * delta;
	rect = { pos.x, pos.y, size.x, size.y };
	if (GetTime() > (spawnTime + lifeSpan)) {
		active = false;
	}
}

void Projectile::setParent(Actor* actor)
{
	parent = actor;
}
