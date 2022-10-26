

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

Actor* projectiles[1028]{};

Enemy* enemies[1028]{};

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------

void SpawnProjectile(float posX, float posY) {
    for (int i = 0; i < std::size(projectiles); i++) {
        if (projectiles[i] != nullptr) {    // Checking for null pointers so they aren't referenced
            if (!projectiles[i]->IsActive()) {
                delete projectiles[i];
                projectiles[i] = new Projectile(posX, posY);
                //projectiles[i]->setParent(&thing);
                projectiles[i]->SetActive(true);
                break;
            }
        }
        else if (projectiles[i] == nullptr) {
            projectiles[i] = new Projectile(posX, posY);
            //projectiles[i]->setParent(&thing);
            projectiles[i]->SetActive(true);
            break;
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

    Weapon wep1;

    Ship thing(screenWidth * 0.5, screenHeight * 0.8);
    thing.SetWeapon(wep1, 0);

    Enemy badguy1(screenWidth * 0.3, screenHeight * 0.2);
    badguy1.SetActive(true);

    Texture2D triangle = LoadTexture("resources/triangle.png");

    int frameWidth = triangle.width;
    int frameHeight = triangle.height;

    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };

    Vector2 origin = { (float)frameWidth / 2, (float)frameHeight / 2 };

    // TODO: Initialize all required variables and load all required data here!

    SetTargetFPS(480);               // Set the framerate cap to a high number, the intention is for the game to behave the same regardless of the framerate.
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        float deltaTime = GetFrameTime();

        thing.Tick(deltaTime);

        for (int i = 0; i < std::size(projectiles); i++) {
            if (projectiles[i] != nullptr) {
                if (projectiles[i]->IsActive()) {
                    projectiles[i]->Tick(deltaTime);
                }
            }

        }
        

        if (IsKeyDown(KEY_RIGHT)) thing.Accelerate({ thing.GetAcceleration(), 0.0f}, deltaTime);
        if (IsKeyDown(KEY_LEFT)) thing.Accelerate({ -thing.GetAcceleration(), 0.0f }, deltaTime);
        if (IsKeyDown(KEY_UP)) thing.Accelerate({ 0.0f, -thing.GetAcceleration() }, deltaTime);
        if (IsKeyDown(KEY_DOWN)) thing.Accelerate({ 0.0f, thing.GetAcceleration() }, deltaTime);
        if (IsKeyDown(KEY_A)) thing.Turn(-250, deltaTime);
        if (IsKeyDown(KEY_D)) thing.Turn(250, deltaTime);

        if (IsKeyDown(KEY_LEFT_CONTROL))
        {
            
            if (thing.GetWeapon(0)->CanFire()) {
                SpawnProjectile(thing.GetPosition().x + thing.GetWeaponOffset(0)->x,
                    thing.GetPosition().y + thing.GetWeaponOffset(0)->y);
                thing.GetWeapon(0)->Fire();
            }
            if (thing.GetWeapon(1)->CanFire()) {
                SpawnProjectile(thing.GetPosition().x + thing.GetWeaponOffset(1)->x,
                    thing.GetPosition().y + thing.GetWeaponOffset(1)->y);
                thing.GetWeapon(1)->Fire();
            }
        }

        
  
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTriangle(
            Vector2{ 20,20 },
            Vector2{ 20,40 },
            Vector2{ 40,20 },
            RED);

        //DrawTexture(triangle, thing.GetPosition().x, thing.GetPosition().y, WHITE);
        
        for (int i = 0; i < std::size(projectiles); i++) {
            if (projectiles[i] != nullptr) {
                if (projectiles[i]->IsActive()) {
                    DrawRectangleRec(projectiles[i]->GetRect(), RED);

                    if (badguy1.IsActive() && CheckCollisionRecs(badguy1.GetRect(), projectiles[i]->GetRect())) {
                        DrawText("POW! HAHA!", 200, 260, 20, BLACK);
                        //badguy1.SetActive(false);
                        projectiles[i]->SetActive(false);
                    }
                }
            }
        }

        if (badguy1.IsActive()) {
            DrawRectangleRec(badguy1.GetRect(), ORANGE);
        }

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

