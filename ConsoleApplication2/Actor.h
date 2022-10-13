#pragma once

#include "raylib.h"

class Actor
{

public:
	Actor(float posX = 0.f, float posY = 0.f); // Initialize the actor, set default position to 0,0 if not specified

	Vector2 GetPosition();	// Return the current position of the actor

	Vector2 GetVelocity();	// Return the current velocity of the actor

	Vector2 GetSize();	// Return the current size of the actor

	Rectangle GetRect(); // Return the rectangle of the actor

	Texture2D GetSprite(); // Return the sprite/texture of the actor

	float GetAngle(); // Return the angle of the actor

	float GetAcceleration(); // Return the current acceleration value of the actor

	float GetDamping(); // Return the current damping value of the actor

	bool isActive(); // 

	void setActive(bool a);

	void MoveTo(float posX, float posY);	// Set the position of the object to the specified coordinates

	void MoveBy(float posX, float posY);	// Move the object from it's current position by the specified amounts, ignoring acceleration or damping

	void RotateTo(float newAngle);

	void RotateBy(float newAngle);

	void Tick(float delta); // What gets called every frame the actor is active

	void Accelerate(Vector2 acc, float delta); 

	void Turn(float turningRate, float delta);

protected:
	Vector2 size = { 32, 32 }; // The size of the actor
	Vector2 pos = { 0, 0 };	// The current position of the object
	Vector2 velocity = { 0, 0 }; // The current velocity of the actor
	Rectangle rect = { 0, 0, 0 ,0 }; // Rectangle for collision detection
	Rectangle spriteRect = { 0, 0, 32, 32 }; // Rectangle for handling animations and etc. with the sprite sheet
	Texture2D spriteSheet = LoadTexture("resources/triangle.png"); // All the sprites, animations of the actor in a single image
	float angle = 0.0f; // Which way the actor is facing
	float acceleration = 1500.0f; // How fast the actor can accelerate
	float damping = 6.5f; // 
	bool active = false;

private:

};