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
	while (!WindowShouldClose())	// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		float deltaTime = GetFrameTime();
		updatePlayer(&player, deltaTime, &env);
		updateCamera(&camera, &player, &env);
		
		BeginDrawing();

		ClearBackground(BLACK);
		BeginMode2D(camera);
		drawEnv(&env);
		drawPlayer(&player);
		EndMode2D();
		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
