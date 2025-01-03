#ifndef OBJECT
#define OBJECT

#include "raylib.h"
#include "environment.h"

typedef struct Sensor {
	bool enabled;
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
} Object;

Vector2 getSensorPos(Object* o, SensorId sensorId);

#endif // !OBJECT
