#include "environment.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum LevelCode {
    heightMap = 0x00,
    angle = 0x01,
    flagged = 0x02,
    x = 0x03,
    y = 0x04,
} LevelCode;

void initGreenHill(LevelEnv * env);

void initLevel(Level level, LevelEnv *env) {
    switch (level) {
    case GreenHill: {
        initGreenHill(env);
        break;
    }
    }
}

void initGreenHill(LevelEnv* env) {
    Tile tiles[35];

    for (int i = 0; i < 30; i++) {
        Tile tile = {
            .heightMap = {0},
            .angle = 0,
            .flagged = false,
            .position = { .x = i, .y = 19 }
        };
        for (int j = 0; j < TILE_SIZE; j++) {
            tile.heightMap[j] = 16;
        }

        tiles[i] = tile;
    }

    for (int i = 0; i < 5; i++) {
        Tile tile = {
            .heightMap = {0},
            .angle = 0,
            .flagged = false,
            .position = {.x = i + 5, .y = 15 }
        };
        for (int j = 0; j < TILE_SIZE; j++) {
            tile.heightMap[j] = 16;
        }

        tiles[30 + i] = tile;
    }
    env->size = (Vector2){ .x = 30, .y = 20 };
    env->count = sizeof(tiles) / sizeof(tiles[0]);
    env->minX = 0;
    env->maxX = tileLen() * env->size.x;
    env->minY = 0;
    env->maxY = tileLen() * env->size.y;
    for (int i = 0; i < env->count; i++) {
        env->tiles[i] = tiles[i];
    }
}

void drawEnv(LevelEnv* env) {
    for (int i = 0; i < env->count; i++) {
        Tile tile = env->tiles[i];
        for (int j = 0; j < 16; j++) {
            Vector2 size = { .x = 1 * TILE_SIZE * SCALE, .y = tile.heightMap[j] * SCALE };
            float x = (tile.position.x * TILE_SIZE) * SCALE;
            float y = (tile.position.y * TILE_SIZE + TILE_SIZE - tile.heightMap[j]) * SCALE;
            DrawRectangle(x, y, size.x, size.y, RED);
        }
    }
}

float tileLen(void) {
    return TILE_SIZE * SCALE;
}