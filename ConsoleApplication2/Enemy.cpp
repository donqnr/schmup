#include "Enemy.h"
#include "World.h"
#include "Ship.h"

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
	rect = { pos.x, pos.y, size.x, size.y };
	pos.x += velocity.x * delta;
	pos.y += velocity.y * delta;
	velocity.x = velocity.x / (1.0f + damping * delta);
	velocity.y = velocity.y / (1.0f + damping * delta);
	switch (currentState) {
		case State::Wait :
			if (CheckCollisionCircleRec({ pos.x - rect.width / 2, pos.y - rect.height / 2 }, 200, parentWorld->GetPlayerShip()->GetRect())) {
				currentState = State::Active;
			}
			return;
		case State::Active:
			ContactDamage();
			return;
		case State::Death :
			SetActive(false);
			return;
	}

}

void Enemy::TakeDamage(int dmgTaken)
{
	health = health - dmgTaken;
	if (health <= 0) {
		currentState = State::Death;
	}
}

void Enemy::ContactDamage()
{
	if (parentWorld != nullptr) {
		if (parentWorld->GetPlayerShip() != nullptr) { // Null pointer checks

			Ship* plrPtr = parentWorld->GetPlayerShip(); // Get pointer to the player ship

			if (CheckCollisionRecs(this->GetRect(), plrPtr->GetWallSensorUp())) {
				plrPtr->SetPosition({ plrPtr->GetPosition().x,this->GetRect().y + this->GetRect().height });
				plrPtr->SetVelocity({ plrPtr->GetVelocity().x, -plrPtr->GetVelocity().y * 2.f });
				this->DealDamage(2, plrPtr);
			}
			else if (CheckCollisionRecs(this->GetRect(), plrPtr->GetWallSensorDn())) {
				plrPtr->SetPosition({ plrPtr->GetPosition().x,this->GetRect().y - plrPtr->GetRect().height - 1 });
				plrPtr->SetVelocity({ plrPtr->GetVelocity().x, -plrPtr->GetVelocity().y * 2.f });
				this->DealDamage(2, plrPtr);
			}
			else if (CheckCollisionRecs(this->GetRect(), plrPtr->GetWallSensorLeft())) {
				plrPtr->SetPosition({ this->GetRect().x + this->GetRect().width,plrPtr->GetPosition().y });
				plrPtr->SetVelocity({ -plrPtr->GetVelocity().x * 2.f, plrPtr->GetVelocity().y });
				this->DealDamage(2, plrPtr);
			}
			else if (CheckCollisionRecs(this->GetRect(), plrPtr->GetWallSensorRight())) {
				plrPtr->SetPosition({ this->GetRect().x - plrPtr->GetRect().width - 1,plrPtr->GetPosition().y });
				plrPtr->SetVelocity({ -plrPtr->GetVelocity().x * 2.f, plrPtr->GetVelocity().y });
				this->DealDamage(2, plrPtr);
			}
		}
	}
	
}

int Enemy::GetHealth()
{
	return health;
}
