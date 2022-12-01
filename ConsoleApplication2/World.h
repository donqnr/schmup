#pragma once

#include "raylib.h"
#include "Actor.h"
#include "Enemy.h"

class World
{
public:

protected:

private:
	Actor* projectiles[2048]{};

	Enemy* enemies[2048]{};
};

