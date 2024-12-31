#include "raylib.h"
#include "player.h"
#include "environment.h"
#include "common.h"

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	// Load a texture from the resources directory
	Player player;
	LevelEnv env;
	initPlayer(&player);
	initLevel(GreenHill, &env);

  SetTargetFPS(60);
	
	// game loop
	while (!WindowShouldClose())	// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		float deltaTime = GetFrameTime();
		updatePlayer(&player, deltaTime, &env);
		
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw our texture to the screen
		drawEnv(&env);
		drawPlayer(&player);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
