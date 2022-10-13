#pragma once
#include "Actor.h"
class Projectile :
    public Actor
{
public:
    Projectile(float posX = 0.f, float posY = 0.f); // Initialize the actor, set default position to 0,0 if not specified

    void Tick(float delta);

    void setParent(Actor* actor);

protected:
    float speed = 500.0f; // The which the projectile goes forward
    float lifeSpan = 2.0f; // Time in seconds the projectile stays active
    Vector2 size = {8,8};
    Actor* parent; // Pointer to the actor that fired the projectile

private:
    float spawnTime = GetTime();
};

