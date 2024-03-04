#include "raylib.h"
#define MAZE_WIDTH 64
#define MAZE_HEIGHT 64
#define MAZE_DRAW_SCALE 6.0f

typedef struct Point {
    int x;
    int y;
} Point;

int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Delivery 4");

    //SetRandomSeed(74218);
    Image mazeImage = GenImageColor(MAZE_WIDTH, MAZE_HEIGHT, BLACK);
    Point mazePoints[MAZE_WIDTH * MAZE_HEIGHT] = {0};
    int mazePointsCounter = 0;

    for (int y = 0; y < mazeImage.height; y++) {
        for (int x = 0; x < mazeImage.width; x++) {
            if (x == 0 || x == mazeImage.width - 1 || y == 0 || y == mazeImage.height - 1) {
                ImageDrawPixel(&mazeImage, x, y, WHITE);
            }
            else if (x % 4 == 0 && y % 4 == 0) {
                int chance = GetRandomValue(0, 3);
                if (chance == 2) {
                    ImageDrawPixel(&mazeImage, x, y, WHITE);
                    mazePoints[mazePointsCounter] = (Point) { x, y };
                    mazePointsCounter++;
                }
            }
        }
    }

    Point directions[4] = {
        {0, -1},    // Up
        {0, 1},     // Down
        {-1, 0},    // Left
        {1, 0}      // Right
    };

    for (int i = 0; i < mazePointsCounter; i++) {
        Point currentPoint = mazePoints[i];
        Point currentDir = directions[GetRandomValue(0, 3)];
        currentPoint.x += currentDir.x;
        currentPoint.y += currentDir.y;

        while (GetImageColor(mazeImage, currentPoint.x, currentPoint.y).r != 255) {
            ImageDrawPixel(&mazeImage, currentPoint.x, currentPoint.y, WHITE);
            currentPoint.x += currentDir.x;
            currentPoint.y += currentDir.y;
        }
    }

    Texture mazeTexture = LoadTextureFromImage(mazeImage);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTextureEx(mazeTexture, (Vector2) {
            GetScreenWidth()/2.0 - mazeTexture.width*MAZE_DRAW_SCALE/2,
            GetScreenHeight()/2.0 - mazeTexture.height*MAZE_DRAW_SCALE/2
        }, 0.0f, MAZE_DRAW_SCALE, WHITE);
        DrawRectangleLines(
            GetScreenWidth()/2.0 - mazeTexture.width*MAZE_DRAW_SCALE/2,
            GetScreenHeight()/2.0 - mazeTexture.height*MAZE_DRAW_SCALE/2,
            MAZE_WIDTH*MAZE_DRAW_SCALE, MAZE_HEIGHT*MAZE_DRAW_SCALE, RED);

        for (int i = 0; i < mazePointsCounter; i++) {
            DrawRectangle(
                GetScreenWidth()/2.0 - mazeTexture.width*MAZE_DRAW_SCALE/2 + mazePoints[i].x*MAZE_DRAW_SCALE,
                GetScreenHeight()/2.0 - mazeTexture.height*MAZE_DRAW_SCALE/2 + mazePoints[i].y*MAZE_DRAW_SCALE,
                MAZE_DRAW_SCALE, MAZE_DRAW_SCALE, SKYBLUE);
        }
        DrawFPS(10, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}