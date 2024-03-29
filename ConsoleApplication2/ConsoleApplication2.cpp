#include <memory>
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Actor.h"
#include "Ship.h"
#include "Projectile.h"
#include "Enemy.h"
#include "HeavyMachineGun.h"
#include "World.h"

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

    World world;

    HeavyMachineGun wep1;
    HeavyMachineGun wep2;

    Weapon* gun = new HeavyMachineGun();

    world.GetPlayerShip()->SetWeapon(gun, 0);
    world.GetPlayerShip()->SetWeapon(&wep2, 1);
    world.GetPlayerShip()->SetWeapon(&wep1, 2);

    world.SpawnEnemy(screenWidth * 0.3, screenHeight * 0.2);

    Texture2D triangle = LoadTexture("resources/triangle.png");

    int frameWidth = triangle.width;
    int frameHeight = triangle.height;

    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };

    Vector2 origin = { (float)frameWidth / 2, (float)frameHeight / 2 };

    Camera2D camera;
    camera.target = { 0,0 };
    camera.offset = { 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(10000);               // Set the framerate cap to a high number, the intention is for the game to behave the same regardless of the framerate.
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        float deltaTime = GetFrameTime();

        world.Tick(deltaTime);

        // Player Controls
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT)) world.GetPlayerShip()->Accelerate({ world.GetPlayerShip()->GetAcceleration(), 0.0f }, deltaTime);
        if (IsKeyDown(KEY_LEFT)) world.GetPlayerShip()->Accelerate({ -world.GetPlayerShip()->GetAcceleration(), 0.0f }, deltaTime);
        if (IsKeyDown(KEY_UP)) world.GetPlayerShip()->Accelerate({ 0.0f, -world.GetPlayerShip()->GetAcceleration() }, deltaTime);
        if (IsKeyDown(KEY_DOWN)) world.GetPlayerShip()->Accelerate({ 0.0f, world.GetPlayerShip()->GetAcceleration() }, deltaTime);
        if (IsKeyDown(KEY_A)) world.GetPlayerShip()->Turn(-250, deltaTime);
        if (IsKeyDown(KEY_D)) world.GetPlayerShip()->Turn(250, deltaTime);

        if (IsKeyDown(KEY_LEFT_CONTROL))
        {
            world.GetPlayerShip()->FireWeapons();
        }


        //Prevent player from going offscreen

        // Update camera, move player ship with it

        camera.target = Vector2Add(camera.target, {0 * deltaTime, -50 * deltaTime});
        world.GetPlayerShip()->MoveBy( 0 * deltaTime, -50 * deltaTime );


        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode2D(camera);


        DrawTexturePro(triangle,
            sourceRec,
            {
                world.GetPlayerShip()->GetRect().x + 16,
                world.GetPlayerShip()->GetRect().y + 16,
                world.GetPlayerShip()->GetRect().width,
                world.GetPlayerShip()->GetRect().height
            },
            { 16 , 16 },
            world.GetPlayerShip()->GetAngle(),
            WHITE);


        // Draw enemies
        for (int i = 0; i < world.GetEnemyArraySize(); i++) {
            if (world.GetEnemy(i) != nullptr) {
                if (world.GetEnemy(i)->IsActive()) {
                    DrawRectangleRec(world.GetEnemy(i)->GetRect(), ORANGE);
                }
            }
        }

       for (int i = 0; i < world.GetProjectileArraySize(); i++) {
                if (world.GetProjectile(i) != nullptr) {    // Check for a null pointer, so it won't get referenced
                    if (world.GetProjectile(i)->IsActive()) {
                        DrawRectangleRec(world.GetProjectile(i)->GetRect(), RED);
                    }
                }
            }
            
        EndMode2D();

        DrawText(TextFormat("%f", GetTime()), 200, 220, 20, BLACK);
        DrawText(TextFormat("%i", world.GetPlayerShip()->GetHealth()), 200, 260, 20, BLACK);

        int pamount = 0;

        DrawText(TextFormat("%i", pamount), 200, 300, 20, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!

    world.PurgeEnemies();

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

