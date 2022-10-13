

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

#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Actor.h"
#include "Ship.h"
#include "Projectile.h"



//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
// Main entry point
//------------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic screen manager");

    Projectile* projectiles[1028]{};

    Ship thing(screenWidth * 0.5, screenHeight * 0.8);

    Texture2D triangle = LoadTexture("resources/triangle.png");

    int frameWidth = triangle.width;
    int frameHeight = triangle.height;

    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };

    Vector2 origin = { (float)frameWidth / 2, (float)frameHeight / 2 };

    bool isColliding = false;

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
                if (projectiles[i]->isActive()) {
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
            thing.Attack();
            
            for (int i = 0; i < std::size(projectiles); i++) {
                if (projectiles[i] != nullptr) {
                    if (!projectiles[i]->isActive()) {
                        delete projectiles[i];
                        projectiles[i] = new Projectile(thing.GetRect().x, thing.GetRect().y);
                        projectiles[i]->setParent(&thing);
                        projectiles[i]->setActive(true);
                        break;
                    }
                }
                else if (projectiles[i] == nullptr) {
                    projectiles[i] = new Projectile(thing.GetRect().x, thing.GetRect().y);
                    projectiles[i]->setParent(&thing);
                    projectiles[i]->setActive(true);
                    break;
                }
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
                if (projectiles[i]->isActive()) {
                    DrawRectangleRec(projectiles[i]->GetRect(), RED);

                    if (CheckCollisionRecs(thing.GetRect(), projectiles[i]->GetRect())) {
                        DrawText("POW! HAHA!", 200, 260, 20, BLACK);
                    }
                }
            }
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
