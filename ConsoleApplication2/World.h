#pragma once

#include <memory>
#include "raylib.h"
#include "Enemy.h"
#include "Ship.h"

class World
{
public:
	World();

	~World();

	void Tick(float delta);

	void ProjectileCollision();

	void SpawnProjectile(float posX, float posY, Actor* parent);

	void SpawnEnemy(float posX, float posY);

	int GetProjectileArraySize();

	int GetEnemyArraySize();

	Projectile* GetProjectile(int index);

	Enemy* GetEnemy(int index);

	void SpawnPlayer();

	Ship* GetPlayerShip();

	void PlayerShipCollision();

	void PurgeEnemies();

	void PurgeProjectiles();

	void PurgeObstacles();

	void TestThing();

protected:

private:
	Ship playerShip = Ship(640, 600);

	Projectile* projectiles[2048]{};

	Enemy* enemies[2048]{};

	Rectangle* obstacles[2048]{};

};

