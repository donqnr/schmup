#include "Enemy.h"

Enemy::Enemy(float posX, float posY)
{
	pos = { posX,posY };
	velocity = { 0,0 };
	rect = { posX, posY, 32, 32 };
}

void Enemy::Tick(float delta)
{
	switch (currentState) {
		case State::Wait : 
			return;
		case State::Chase :
			return;
		case State::Death :
			SetActive(false);
	}

}
