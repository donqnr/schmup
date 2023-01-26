#include "World.h"
#include <iostream>

World::World()
{

}

World::~World()
{

}

void World::Tick(float delta)
{
    ProjectileCollision();

    playerShip.Tick(delta);

    for (Projectile* proj : projectiles) {
        if (proj != nullptr) {
            if (proj->IsActive()) {
                proj->Tick(delta);
            }
        }
    }

    for (Enemy* nme : enemies) {
        if (nme != nullptr) {
            if (nme->IsActive()) {
                nme->Tick(delta);
            }
        }
    }
}

void World::ProjectileCollision()
{
    // Collision between projectiles and enemies
    for (Projectile* proj : projectiles) {
        if (proj != nullptr) {    // Check for a null pointer, so it won't get referenced
            if (proj->IsActive()) {

                for (Enemy* nme : enemies) {
                    if (nme != nullptr) {
                        if (nme->IsActive() && CheckCollisionRecs(nme->GetRect(), proj->GetRect())) {
                            nme->TakeDamage(5);
                            proj->SetActive(false);
                        }
                    }
                }
            }
        }
    }
}

void World::SpawnProjectile(float posX, float posY)
{
    for (int i = 0; i < std::size(projectiles); i++) {
        if (projectiles[i] != nullptr) {    // Checking for null pointers so they aren't referenced
            if (!projectiles[i]->IsActive()) {
                delete projectiles[i];
                projectiles[i] = new Projectile(this, posX - 4, posY);
                //projectiles[i]->setParent(&playerShip);
                projectiles[i]->SetActive(true);
                break;
            }
        }
        else if (projectiles[i] == nullptr) {
            projectiles[i] = new Projectile(this, posX - 4, posY);
            //projectiles[i]->setParent(&playerShip);
            projectiles[i]->SetActive(true);
            break;
        }
        else {

        }
    }
}

void World::SpawnEnemy(float posX, float posY)
{
    for (int i = 0; i < std::size(enemies); i++) {
        if (enemies[i] != nullptr) {
            if (!enemies[i]->IsActive()) {
                delete enemies[i];
                enemies[i] = new Enemy(this, posX, posY);
                enemies[i]->SetActive(true);
                break;
            }
        }
        else if (enemies[i] == nullptr) {
            enemies[i] = new Enemy(this, posX, posY);
            enemies[i]->SetActive(true);
            break;
        }
    }
}



int World::GetProjectileArraySize()
{
    return std::size(projectiles);
}

int World::GetEnemyArraySize()
{
    return std::size(enemies);
}

Projectile* World::GetProjectile(int index)
{
    return projectiles[index];
}

Enemy* World::GetEnemy(int index)
{
    return enemies[index];
}

void World::SpawnPlayer()
{

}

Ship* World::GetPlayerShip()
{
    return &playerShip;
}

void World::PlayerShipCollision()
{
    for (Rectangle* o : obstacles) {
        if (CheckCollisionRecs(playerShip.GetWallSensorUp(), *o)) {
            playerShip.SetPosition({ playerShip.GetPosition().x,o->y + o->height });
            playerShip.SetVelocity({ playerShip.GetVelocity().x, -playerShip.GetVelocity().y * 2.f });
        }
        if (CheckCollisionRecs(playerShip.GetWallSensorDn(), *o)) {
            playerShip.SetPosition({ playerShip.GetPosition().x,o->y - playerShip.GetRect().height - 1 });
            playerShip.SetVelocity({ playerShip.GetVelocity().x, -playerShip.GetVelocity().y * 2.f });
        }
        if (CheckCollisionRecs(playerShip.GetWallSensorLeft(), *o)) {
            playerShip.SetPosition({ o->x + o->width,playerShip.GetPosition().y });
            playerShip.SetVelocity({ -playerShip.GetVelocity().x * 2.f, playerShip.GetVelocity().y });
        }
        if (CheckCollisionRecs(playerShip.GetWallSensorRight(), *o)) {
            playerShip.SetPosition({ o->x - playerShip.GetRect().width - 1,playerShip.GetPosition().y });
            playerShip.SetVelocity({ -playerShip.GetVelocity().x * 2.f, playerShip.GetVelocity().y });
        }
    }

}

void World::PurgeEnemies()
{
    for (Enemy* nme : enemies) {
        delete nme;
    }
}

void World::PurgeProjectiles()
{
    for (Projectile* proj : projectiles) {
        delete proj;
    }
}

void World::PurgeObstacles()
{
    for (Rectangle* rect : obstacles) {
        delete rect;
    }
}
