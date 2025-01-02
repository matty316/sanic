#include "raylib.h"
#include "player.h"
#include "environment.h"
#include "common.h"

typedef enum GameState {
	Title, Gameplay
} GameState;

int main ()
{
	Player player;
	LevelEnv env;
	Camera2D camera;
	GameState state = Title;

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Raylib");
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	initPlayer(&player);
	initCamera(&camera, &player);
	initLevel(GreenHill, &env);

    SetTargetFPS(60);
	
	// game loop
	while (!WindowShouldClose())
	{
		switch (state)
		{
		case Title: {
			if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
			{
				state = Gameplay;
			}
			BeginDrawing();
			// TODO: Draw TITLE screen here!
			DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SKYBLUE);
			DrawText("SANIC", 20, 20, 40, DARKBLUE);
			const char text[] = "PRESS ENTER";
			int fontSize = 40;
			int textWidth = MeasureText(text, fontSize);
			DrawText(text, (SCREEN_WIDTH - textWidth) / 2.0f, SCREEN_HEIGHT / 2.0f, fontSize, DARKBLUE);
			EndDrawing();
			break;
		}
		case Gameplay: {
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
			break;
		}
		}
		
	}

	CloseWindow();
	return 0;
}
