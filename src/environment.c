#include "environment.h"
#include "common.h"

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

    Tile tiles[] = {
        {
            .heightMap = {0, 0, 1, 2, 2, 3, 4, 5, 5, 6, 6, 7, 8, 9, 9, 9},
            .angle = 33.75,
            .flagged = false,
            .position = {.x = 0, .y = 0},
        },
        {
            .heightMap = {0, 0, 1, 2, 2, 3, 4, 5, 5, 6, 6, 7, 8, 9, 9, 9},
            .angle = 33.75,
            .flagged = false,
            .position = {.x = 1, .y = 1},
        },
        {
            .heightMap = {0, 0, 1, 2, 2, 3, 4, 5, 5, 6, 6, 7, 8, 9, 9, 9},
            .angle = 33.75,
            .flagged = false,
            .position = {.x = 2, .y = 0},
        },
        {
            .heightMap = {0, 0, 1, 2, 2, 3, 4, 5, 5, 6, 6, 7, 8, 9, 9, 9},
            .angle = 33.75,
            .flagged = false,
            .position = {.x = 3, .y = 0},
        },
        {
            .heightMap = {0, 0, 1, 2, 2, 3, 4, 5, 5, 6, 6, 7, 8, 9, 9, 9},
            .angle = 33.75,
            .flagged = false,
            .position = {.x = 4, .y = 0},
        },
    };

    env->count = sizeof(tiles) / sizeof(Tile);

    for (int i = 0; i < env->count; i++) {
        env->tiles[i] = tiles[i];
    }
}

void drawEnv(LevelEnv* env) {
    for (int i = 0; i < 100; i++) {
        Tile tile = env->tiles[i];
        for (int j = 0; j < 16; j++) {
            Vector2 size = { .x = 1, .y = tile.heightMap[j] };
            DrawRectangle(tile.position.x * 16 + j, tile.position.y * 16 + 16 - tile.heightMap[j], size.x, size.y, RED);
        }
    }
}
