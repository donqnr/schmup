#include "Projectile.h"
#include "World.h"

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
	if (parentWorld != nullptr) {
		for (int i = 0; i < parentWorld->GetEnemyArraySize(); i++) {
			if (parentWorld->GetEnemy(i) != nullptr) {
				if (parentWorld->GetEnemy(i)->IsActive() && CheckCollisionRecs(this->GetRect(), parentWorld->GetEnemy(i)->GetRect())) {
					parentWorld->GetEnemy(i)->TakeDamage(this->damage);
					this->SetActive(false);
				}
			}
		}
	}
}

void Projectile::setParent(Actor* actor)
{
	parent = actor;
}
