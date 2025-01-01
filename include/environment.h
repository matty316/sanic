#ifndef ENVIRONMENT
#define ENVIRONMENT

#include "raylib.h"
#include <stdint.h>

typedef enum Level {
    GreenHill
} Level;

typedef struct Tile {
    uint8_t heightMap[16];
    float angle;
    bool flagged;
    Vector2 position;
} Tile;

typedef struct LevelEnv {
    Level level;
    Tile tiles[100];
    int count;
    Vector2 size;
    float minX;
    float maxX;
    float minY;
    float maxY;
} LevelEnv;

void initLevel(Level level, LevelEnv *env);
void drawEnv(LevelEnv* env);
float tileLen(void);

#endif 
