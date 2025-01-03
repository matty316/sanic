#include "player.h"
#include "common.h"
#include "raymath.h"
#include <stdio.h>

#define acceleration_speed	0.046875f * SCALE
#define deceleration_speed	0.5f * SCALE
#define friction_speed	0.046875f * SCALE
#define air_acceleration_speed	0.09375f * SCALE
#define gravity_force	0.21875f * SCALE
#define jump_force 6.5f * SCALE
#define top_speed	6.f * SCALE

float lastY = 0;

void initPlayer(Player* player) {
	player->object.position.x = SCREEN_WIDTH / 2.0f;
	player->object.position.y = SCREEN_HEIGHT / 2.0f;
    player->object.widthRadius = 9;
    player->object.heightRadius = 19;
    player->object.groundAngle = 0;
    player->object.groundSpeed = 0;
    player->object.speed.x = 0;
    player->object.speed.y = 0;
	player->ascending = false;
	player->state = Jumping;
}

void initCamera(Camera2D *camera, Player *player) {
	camera->target = player->object.position;
	camera->offset = (Vector2){ .x = SCREEN_WIDTH / 2.0f, .y = SCREEN_HEIGHT / 2.0f };
	camera->rotation = 0.0f;
	camera->zoom = 2.0f;
}

void updatePlayer(Player* player, float deltaTime, LevelEnv* env) {
	switch (player->state) {
	case Jumping: {
		player->ascending = player->object.position.y <= lastY;
		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
			player->object.speed.x -= air_acceleration_speed;
			if (player->object.speed.x <= -top_speed) {
				player->object.speed.x = -top_speed;
			}
		}
		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
			player->object.speed.x += air_acceleration_speed;
			if (player->object.speed.x >= top_speed) {
				player->object.speed.x = top_speed;
			}
		}
		player->object.position.y += player->object.speed.y * deltaTime * GetFPS();
		player->object.position.x += player->object.speed.x * deltaTime * GetFPS();
		player->object.speed.y += gravity_force;
		if (player->object.speed.y > 16.f) {
			player->object.speed.y = 16.f;
		}

		break;
	}
	case Standing: {
		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
			if (player->object.groundSpeed > 0) {
				player->object.groundSpeed -= deceleration_speed;
				if (player->object.groundSpeed <= 0) {
					player->object.groundSpeed = -0.5;
				}
			}
			else if (player->object.groundSpeed > -top_speed) {
				player->object.groundSpeed -= acceleration_speed;
				if (player->object.groundSpeed <= -top_speed) {
					player->object.groundSpeed = -top_speed;
				}
			}
		}
		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
			if (player->object.groundSpeed < 0) {
				player->object.groundSpeed += deceleration_speed;
				if (player->object.groundSpeed >= 0) {
					player->object.groundSpeed = 0.5;
				}
			}
			else if (player->object.groundSpeed < top_speed) {
				player->object.groundSpeed += acceleration_speed;
				if (player->object.groundSpeed >= top_speed) {
					player->object.groundSpeed = top_speed;
				}
			}
		}

		player->object.speed.x = player->object.groundSpeed;
		player->object.position.x += player->object.speed.x * deltaTime * GetFPS();

		if (IsKeyUp(KEY_D) && IsKeyUp(KEY_RIGHT) && IsKeyUp(KEY_A) && IsKeyUp(KEY_LEFT)) {
			float min = fminf(abs(player->object.groundSpeed), friction_speed);
			int sign;

			if (player->object.groundSpeed == 0) {
				sign = 0;
			}
			else if (player->object.groundSpeed > 0) {
				sign = 1;
			}
			else {
				sign = -1;
			}

			player->object.groundSpeed -= min * sign;
		}

		if (IsKeyDown(KEY_SPACE)) {
			player->object.speed.y -= jump_force;
			player->state = Jumping;
			player->ascending = true;
		}
		break;
	}
	}
	
	checkFloorTile(env, player);
	lastY = player->object.position.y;
}

void updateCamera(Camera2D* camera, Player* player, LevelEnv* env) {
	float width = SCREEN_WIDTH;
	float height = SCREEN_HEIGHT;
	
	camera->target = player->object.position;
	camera->offset = (Vector2){ width / 2.0f, height / 2.0f };
	float minX = env->minX, minY = env->minY, maxX = env->maxX, maxY = env->maxY;

	Vector2 max = GetWorldToScreen2D((Vector2) { maxX, maxY }, * camera);
	Vector2 min = GetWorldToScreen2D((Vector2) { minX, minY }, * camera);

	if (max.x < width) camera->offset.x = width - (max.x - width / 2);
	if (max.y < height) camera->offset.y = height - (max.y - height / 2);
	if (min.x > 0) camera->offset.x = width / 2 - min.x;
	if (min.y > 0) camera->offset.y = height / 2 - min.y;
}

void drawPlayer(Player* player) {
    float x = player->object.position.x - player->object.widthRadius;
    float y = player->object.position.y - player->object.heightRadius * 2;
    float width = player->object.widthRadius * 2 + 1;
    float height = player->object.heightRadius * 2 + 1;
	DrawRectangle(x, y, width, height, BLUE);
}

void checkFloorTile(LevelEnv* env, Player* player) {
	if (player->ascending) return;

	Vector2 aAnchor = getSensorPos(&player->object, A);
	Vector2 bAnchor = getSensorPos(&player->object, B);

	float snappingDistance = fminf(abs(player->object.speed.x) + 4, 14);
	float minDistance = 33.f;
	for (int i = 0; i < env->count; i++) {
		Tile tile = env->tiles[i];
		float tileY = tile.position.y * tileLen();
		float tileX = tile.position.x * tileLen();

		float aDist = 33.f;
		if (tileX <= aAnchor.x && tileX + tileLen() >= aAnchor.x) {
			aDist = tileY - aAnchor.y;
		}
		float bDist = 33.f;
		if (tileX <= bAnchor.x && tileX + tileLen() >= bAnchor.x) {
			bDist = tileY - bAnchor.y;
		}
		float winningDist = fminf(aDist, bDist);
		if (abs(winningDist) < 14) {
			player->object.speed.y = 0.f;
			player->object.position.y = player->object.position.y + floor(winningDist) + player->object.heightRadius;
			player->state = Standing;
			player->ascending = false;
			break;
		}
	}
}
