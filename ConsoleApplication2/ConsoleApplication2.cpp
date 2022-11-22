

/*******************************************************************************************
*
*   raylib [core] examples - basic screen manager
*
*   This example illustrates a very simple screen manager based on a states machines
*
*   This test has been created using raylib 1.1 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <memory>
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Actor.h"
#include "Ship.h"
#include "Projectile.h"
#include "Enemy.h"
#include "HeavyMachineGun.h"

Actor *projectiles[2048]{};

Enemy *enemies[2048]{};

struct Obstacle {
    Rectangle rect = { 0, 0, 0 ,0 }; // Rectangle for collision detection

};

//------------------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------------------

void SpawnProjectile(float posX, float posY) {
    for (int i = 0; i < std::size(projectiles); i++) {
        if (projectiles[i] != nullptr) {    // Checking for null pointers so they aren't referenced
            if (!projectiles[i]->IsActive()) {
                delete projectiles[i];
                projectiles[i] = new Projectile(posX - 4, posY);
                //projectiles[i]->setParent(&thing);
                projectiles[i]->SetActive(true);
                break;
            }
        }
        else if (projectiles[i] == nullptr) {
            projectiles[i] = new Projectile(posX - 4, posY);
            //projectiles[i]->setParent(&thing);
            projectiles[i]->SetActive(true);
            break;
        }
        else {

        }
    }
}

//------------------------------------------------------------------------------------------
// Main entry point
//------------------------------------------------------------------------------------------
int main(void)
{
// Initialization
//--------------------------------------------------------------------------------------

const int screenWidth = 1280;
const int screenHeight = 720;

InitWindow(screenWidth, screenHeight, "gaem");

Obstacle o1;
o1.rect = { 256, 400, 512, 64 };

HeavyMachineGun wep1;
HeavyMachineGun wep2;

Weapon* gun = new HeavyMachineGun();

Ship thing(screenWidth * 0.5, screenHeight * 0.8);
thing.SetWeapon(gun, 0);
thing.SetWeapon(&wep2, 1);
thing.SetWeapon(&wep1, 2);

Enemy badguy1(screenWidth * 0.3, screenHeight * 0.2);
badguy1.SetActive(true);

Texture2D triangle = LoadTexture("resources/triangle.png");

int frameWidth = triangle.width;
int frameHeight = triangle.height;

Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };

Vector2 origin = { (float)frameWidth / 2, (float)frameHeight / 2 };

// TODO: Initialize all required variables and load all required data here!

SetTargetFPS(10000);               // Set the framerate cap to a high number, the intention is for the game to behave the same regardless of the framerate.
//--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    float deltaTime = GetFrameTime();

    thing.Tick(deltaTime);

    badguy1.Tick(deltaTime);

    for (int i = 0; i < std::size(projectiles); i++) {
        if (projectiles[i] != nullptr) {
            if (projectiles[i]->IsActive()) {
                projectiles[i]->Tick(deltaTime);
            }
        }

    }


    if (IsKeyDown(KEY_RIGHT)) thing.Accelerate({ thing.GetAcceleration(), 0.0f }, deltaTime);
    if (IsKeyDown(KEY_LEFT)) thing.Accelerate({ -thing.GetAcceleration(), 0.0f }, deltaTime);
    if (IsKeyDown(KEY_UP)) thing.Accelerate({ 0.0f, -thing.GetAcceleration() }, deltaTime);
    if (IsKeyDown(KEY_DOWN)) thing.Accelerate({ 0.0f, thing.GetAcceleration() }, deltaTime);
    if (IsKeyDown(KEY_A)) thing.Turn(-250, deltaTime);
    if (IsKeyDown(KEY_D)) thing.Turn(250, deltaTime);

    if (IsKeyDown(KEY_LEFT_CONTROL))
    {

        for (int i = 0; i < thing.GetWeaponAmount(); i++) { // Player firing his weapons
            if (thing.GetWeapon(i)->CanFire()) {
                SpawnProjectile(
                    thing.GetPosition().x + thing.GetWeaponOffset(i)->x,
                    thing.GetPosition().y + thing.GetWeaponOffset(i)->y
                );
                thing.GetWeapon(i)->Fire();
            }
        }
    }

    // Collision between projectiles and enemies
    for (int i = 0; i < std::size(projectiles); i++) {
        if (projectiles[i] != nullptr) {    // Check for a null pointer, so it won't get referenced
            if (projectiles[i]->IsActive()) {
                DrawRectangleRec(projectiles[i]->GetRect(), RED);

                if (badguy1.IsActive() && CheckCollisionRecs(badguy1.GetRect(), projectiles[i]->GetRect())) {
                    //badguy1.SetActive(false);
                    badguy1.TakeDamage(5);
                    projectiles[i]->SetActive(false);
                }
            }
        }
    }

    //Collision between players and the environment
    if (CheckCollisionRecs(thing.GetWallSensorUp(), o1.rect)) {
        thing.SetPosition({ thing.GetPosition().x,o1.rect.y + o1.rect.height});
        thing.SetVelocity({ thing.GetVelocity().x, -thing.GetVelocity().y * 1.2f});
    }
    if (CheckCollisionRecs(thing.GetWallSensorDn(), o1.rect)) {
        thing.SetPosition({ thing.GetPosition().x,o1.rect.y - thing.GetRect().height - 1});
        thing.SetVelocity({ thing.GetVelocity().x, -thing.GetVelocity().y * 1.2f });
    }
    if (CheckCollisionRecs(thing.GetWallSensorLeft(), o1.rect)) {
        thing.SetPosition({ o1.rect.x + o1.rect.width,thing.GetPosition().y });
        thing.SetVelocity({ -thing.GetVelocity().x * 1.2f, thing.GetVelocity().y });
    }
    if (CheckCollisionRecs(thing.GetWallSensorRight(), o1.rect)) {
        thing.SetPosition({ o1.rect.x - thing.GetRect().width - 1,thing.GetPosition().y});
        thing.SetVelocity({ -thing.GetVelocity().x * 1.2f, thing.GetVelocity().y });
    }


        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        //DrawTexture(triangle, thing.GetPosition().x, thing.GetPosition().y, WHITE);

        DrawRectangleRec(thing.GetWallSensorUp(), RED);
        DrawRectangleRec(thing.GetWallSensorDn(), RED);
        DrawRectangleRec(thing.GetWallSensorLeft(), RED);
        DrawRectangleRec(thing.GetWallSensorRight(), RED);

        // Draw environment and obstacles
        DrawRectangleRec(o1.rect, RED);

        // Draw enemies
        if (badguy1.IsActive()) {
            DrawRectangleRec(badguy1.GetRect(), ORANGE);
        }

        // Draw Player
        DrawTexturePro(triangle,
            sourceRec,
            {
                thing.GetRect().x + 16,
                thing.GetRect().y + 16,
                thing.GetRect().width,
                thing.GetRect().height
            },
            { 16 , 16 },
            thing.GetAngle(),
            WHITE);

        DrawText(TextFormat("%f", GetTime()), 200, 220, 20, BLACK);
        DrawText(TextFormat("%i", badguy1.GetHealth()), 200, 260, 20, BLACK);

        int pamount = 0;

        for (int i = 0; i < std::size(projectiles); i++) {
            if (projectiles[i] != nullptr) {
                if (projectiles[i]->IsActive()) {
                    pamount++;
                }
            }
        }

        DrawText(TextFormat("%i", pamount), 200, 300, 20, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

