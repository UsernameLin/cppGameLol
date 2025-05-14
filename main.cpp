

#include "raylib.h"
#include "ball.h"
#include <iostream>
#include <cmath>

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen
{
    LOGO = 0,
    TITLE,
    GAMEPLAY,
    ENDING
} GameScreen;
bool checkCollision(int screenH, int screenW, int y, int x)
{
    if (y < y + screenH / 20 && y > y - screenH / 20 && screenW - 20 < x && x < screenW - 10) //pc
    {
        return true;
    }
    if (y < GetMouseY() + screenH / 20 && y > GetMouseY() - screenH / 20 && 10 < x && x < 20) //mouse
    {
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 640;
    const int screenHeight = 480;
    int x = screenWidth / 2;
    int y = screenHeight / 2;
    int cy = 1 + 2 * sqrt(sqrt(sqrt(screenHeight)));
    int cx = 1 + 2 * sqrt(sqrt(sqrt(screenWidth)));
    int bounce = 1;
    int userScore = 0;
    int pcScore = 0;
    bool wait = false;
    int time = 0;
    int posNegX = 1;
    int posNegY = 1;


    InitWindow(screenWidth, screenHeight, "BAD PONG");

    GameScreen currentScreen = LOGO;

    // TODO: Initialize all required variables and load all required data here!

    int framesCounter = 0; // Useful to count frames

    SetTargetFPS(60); // Set desired framerate (frames-per-second)
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        switch (currentScreen)
        {
        case LOGO:
        {
            // TODO: Update LOGO screen variables here!

            framesCounter++; // Count frames

            // Wait for 2 seconds (120 frames) before jumping to TITLE screen
            if (framesCounter > 60)
            {
                currentScreen = TITLE;
            }
        }
        break;
        case TITLE:
        {
            // TODO: Update TITLE screen variables here!

            // Press enter to change to GAMEPLAY screen
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            {
                currentScreen = GAMEPLAY;
            }
        }
        break;
        case GAMEPLAY:
        {
            // TODO: Update GAMEPLAY screen variables here!

            // Press enter to change to ENDING screen
            if (IsKeyPressed(KEY_P))
            {
                currentScreen = ENDING;
            }
        }
        break;
        case ENDING:
        {
            // TODO: Update ENDING screen variables here!

            // Press enter to return to TITLE screen
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            {
                currentScreen = GAMEPLAY;
            }
        }
        break;
        default:
            break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (currentScreen)
        {
        case LOGO:
        {
            // TODO: Draw LOGO screen here!
            DrawText("LOGO", 20, 20, 40, LIGHTGRAY);
            DrawText("WAIT for a SECOND...", 290, 220, 20, GRAY);
        }
        break;
        case TITLE:
        {
            // TODO: Draw TITLE screen here!
            DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
            DrawText("BAD PONG", 20, 20, 40, DARKGREEN);
            DrawText("PRESS ENTER or TAP to play", 120, 220, 20, DARKGREEN);
        }
        break;
        case GAMEPLAY:
        {
            if (!wait)
            {
                if (checkCollision(screenHeight, screenWidth, y, x))
                {
                    wait = true;
                    posNegX = -posNegX;
                    cx = -cx;
                    bounce++;
                }
            }
            else if(wait)
            {
                time++;
                if (time > 3)
                {
                    time = 0;
                    wait = false;
                }
            }

            if (y > screenHeight || y < 0)
            {
                posNegY = -posNegY;
                cy = -cy;
            }
            x += cx + (.2 * pow(bounce, 1.5) * posNegX);
            y += cy + (.2 * pow(bounce, 1.5) * posNegY);
            if (x > screenWidth)
            {
                x = screenWidth / 2;
                y = screenHeight / 2;
                bounce = 1;
                userScore++;
                currentScreen = ENDING;
            }
            if (x < 0)
            {
                x = screenWidth / 2;
                y = screenHeight / 2;
                bounce = 1;
                pcScore++;
                currentScreen = ENDING;
            }

            // TODO: Draw GAMEPLAY screen here!
            DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
            DrawRectangle(10, GetMouseY() - screenHeight / 20, 10, screenHeight / 10, BLUE);
            DrawRectangle(screenWidth - 20, y - screenHeight / 20, 10, screenHeight / 10, RED);
            DrawText(TextFormat("User score: %i Pc Score: %i", userScore, pcScore), screenWidth / 3, 20, 20, DARKBLUE);
            DrawText(TextFormat("Bounce Counter: %i", bounce - 1), screenWidth / 3, 50, 10, BLACK);

            DrawCircle(x, y, 3, WHITE);
        }
        break;
        case ENDING:
        {
            DrawText("PRESS ENTER or TAP to RETURN to Play Again", 120, 220, 20, DARKBLUE);
        }
        break;
        default:
            break;
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}