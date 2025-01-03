#include "object.h"
#include "common.h"
#include <math.h>
#include <stdio.h>

Vector2 getSensorPos(Object* o, SensorId sensorId) {
	switch (sensorId) {
	case A:
		return (Vector2) { .x = o->position.x - o->widthRadius, .y = o->position.y + o->heightRadius };
		break;
	case B:
		return (Vector2) { .x = o->position.x + o->widthRadius, .y = o->position.y + o->heightRadius };
		break;
	case C:
		break;
	case D:
		break;
	case E:
		break;
	case F:
		break;
	}
}