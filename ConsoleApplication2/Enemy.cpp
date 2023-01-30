#include "Enemy.h"
#include "World.h"

Enemy::Enemy(float posX, float posY)
{
	pos = { posX,posY };
	velocity = { 0,0 };
	rect = { posX, posY, 32, 32 };
}

Enemy::Enemy(World* wrld, float posX, float posY)
{
	pos = { posX,posY };
	velocity = { 0,0 };
	rect = { posX, posY, 32, 32 };
	parentWorld = wrld;
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

void Enemy::TakeDamage(int dmgTaken)
{
	health = health - dmgTaken;
	if (health <= 0) {
		currentState = State::Death;
	}
}

void Enemy::TestWorldPtr()
{
	if (parentWorld != nullptr) {
		parentWorld->TestThing();
	}
}
