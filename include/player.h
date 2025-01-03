#ifndef PLAYER
#define PLAYER

#include "raylib.h"
#include "environment.h"
#include "object.h"

typedef enum PlayerState {
	Standing, Jumping
} PlayerState;

typedef struct Player {
	Object object;
	PlayerState state;
	bool ascending;
} Player;

void initPlayer(Player* player);
void initCamera(Camera2D* camera, Player* player);
void updatePlayer(Player* player, float deltaTime, LevelEnv* env);
void updateCamera(Camera2D* camera, Player* player, LevelEnv* env);
void drawPlayer(Player* player);
void checkFloorTile(LevelEnv* env, Player* player);

#endif // !PLAYER
