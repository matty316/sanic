#ifndef OBJECT
#define OBJECT

#include "raylib.h"

typedef struct Sensor {
	bool enabled;
	Vector2 position;
} Sensor;

typedef enum SensorId {
	A, B, C, D, E, F
} SensorId;

typedef struct Object {
	Vector2 position;
	Vector2 speed;
	float groundSpeed;
	float groundAngle;
	float widthRadius;
	float heightRadius;
	Rectangle hitbox;
	Rectangle bounds;
	Sensor sensors[6];
} Object;

#endif // !OBJECT
