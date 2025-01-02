#include "raylib.h"
#include "player.h"
#include "environment.h"
#include "common.h"

int main ()
{
	Player player;
	LevelEnv env;
	Camera2D camera;

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Raylib");
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	initPlayer(&player);
	initCamera(&camera, &player);
	initLevel(GreenHill, &env);

    SetTargetFPS(60);
	
	// game loop
	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();
		updatePlayer(&player, deltaTime, &env);
		updateCamera(&camera, &player, &env);
		
		BeginDrawing();

        ClearBackground(SKYBLUE);
		BeginMode2D(camera);
		drawEnv(&env);
		drawPlayer(&player);
		EndMode2D();
		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
