#include "player.h"

#define SPEED 350
#define GRAVITY 400

void initPlayer(Player* player) {
	player->object.position.x = 0;
	player->object.position.y = 0;
    player->object.widthRadius = 9;
    player->object.heightRadius = 19;
    player->object.groundAngle = 0;
    player->object.groundSpeed = 0;
    player->object.speed.x = 0;
    player->object.speed.y = 0;
	player->state = Jumping;
}

void updatePlayer(Player* player, float deltaTime, LevelEnv *env) {
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) player->object.position.x += SPEED * deltaTime;
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) player->object.position.x -= SPEED * deltaTime;
	if (IsKeyDown(KEY_SPACE) && player->state == Standing) {
		player->object.speed.y = -SPEED;
		player->state = Jumping;
	}

}

void drawPlayer(Player* player) {
    float x = player->object.position.x - player->object.widthRadius;
    float y = player->object.position.y - player->object.heightRadius * 2;
    float width = player->object.widthRadius * 2 + 1;
    float height = player->object.heightRadius * 2 + 1;
	DrawRectangle(x, y, width, height, BLUE);
}
