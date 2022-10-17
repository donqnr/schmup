#pragma once
#include "Actor.h"
class Enemy :
    public Actor
{
private:
    enum State {
        Wait,
        Chase,
        Death,
    };
};

