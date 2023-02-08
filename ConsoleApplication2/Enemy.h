#pragma once
#include "Actor.h"

class Enemy :
    public Actor
{
public:
    Enemy(float posX = 0.0f, float posY = 0.0f);

    Enemy(World* wrld, float posX = 0.0f, float posY = 0.0f);

    void Tick(float delta);

    void TakeDamage(int dmgTaken);

    void ContactDamage();

    int GetHealth() override;

private:
    enum class State {
        Wait,
        Active,
        Death,
    };
    State currentState = State::Wait;

    Actor* target = nullptr;

    int health = 10;
};

