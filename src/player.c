#include "player.h"
#include "common.h"

#define VERTICAL_SPEED 350
#define AIR_SPEED 100
#define GROUND_SPEED 300
#define GRAVITY 400

void initPlayer(Player* player) {
	player->object.position.x = SCREEN_WIDTH / 2.0f;
	player->object.position.y = SCREEN_HEIGHT / 2.0f;
    player->object.widthRadius = 9;
    player->object.heightRadius = 19;
    player->object.groundAngle = 0;
    player->object.groundSpeed = 0;
    player->object.speed.x = 0;
    player->object.speed.y = 0;
	player->object.hitbox.x = 0;
	player->object.hitbox.y = 0;
	player->object.hitbox.width = 20;
	player->object.hitbox.height = 40;
	player->object.bounds.x = 0;
	player->object.bounds.y = 0;
	player->object.bounds.width = player->object.widthRadius * 2 + 1;
	player->object.bounds.height = player->object.heightRadius * 2 + 1;
	player->state = Jumping;
}

void initCamera(Camera2D *camera, Player *player) {
	camera->target = player->object.position;
	camera->offset = (Vector2){ .x = SCREEN_WIDTH / 2.0f, .y = SCREEN_HEIGHT / 2.0f };
	camera->rotation = 0.0f;
	camera->zoom = 2.0f;
}

void updatePlayer(Player* player, float deltaTime, LevelEnv* env) {
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
		if (player->object.position.x + player->object.widthRadius + 1 <= env->maxX && player->state == Standing) {
			player->object.speed.x += GROUND_SPEED;
		}
		else if (player->object.position.x + player->object.widthRadius - 1 <= env->maxX && player->state == Jumping) {
			player->object.speed.x = AIR_SPEED;
		}
	}

	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        if (player->object.position.x - player->object.widthRadius >= env->minX && player->state == Standing) {
            player->object.speed.x -= GROUND_SPEED;
        }
		else if (player->object.position.x - player->object.widthRadius >= env->minX && player->state == Jumping) {
			player->object.speed.x = -AIR_SPEED;
		}
	}
    
    if (player->state == Standing) {
        player->object.position.x += player->object.speed.x * deltaTime;
    }
    
	if (IsKeyDown(KEY_SPACE) && player->state == Standing) {
		player->object.speed.y = -VERTICAL_SPEED;
		player->state = Jumping;
	}
	
    bool hitObstacle = false;
	for (int i = 0; i < env->count; i++) {
		Tile tile = env->tiles[i];
        float tileY = tile.position.y * tileLen() - 1;
		float tileX = tile.position.x * tileLen();
		if (tileX <= player->object.position.x &&
			tileX + tileLen() >= player->object.position.x &&
			tileY >= player->object.position.y &&
			tileY <= player->object.position.y + player->object.speed.y * deltaTime) {
			hitObstacle = true;
			player->object.speed = (Vector2){ .x = 0.0f, .y = 0.0f };
			player->object.position.y = tileY;
			break;
		}
	}

    if (!hitObstacle)
    {
        player->object.position.y += player->object.speed.y * deltaTime;
		if (player->object.position.x - player->object.widthRadius >= env->minX && player->object.position.x + player->object.widthRadius <= env->maxX) {
			player->object.position.x += player->object.speed.x * deltaTime;
		}
        player->object.speed.y += GRAVITY * deltaTime;
        player->state = Jumping;
    }
    else player->state = Standing;
    
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
