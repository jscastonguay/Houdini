#include "sensors.h"

#define NB_MEASURENETS_MAX  10

typedef enum {
	IDLE,
	RUNNING,
	ERROR
} State;

int measures[NB_MEASURENETS_MAX];
int currentTemp;
State state = IDLE;

int application_init() {
	for (unsigned int i = 0; i < NB_MEASURENETS_MAX; i++) {
		measures[i] = 0;
	}
	currentTemp = 0;
	state = IDLE;
	
	return 0;
}


static int getTemperature() {
	int voltage = getVoltage();
	return voltage / 100;
}

void configureSensors() {
	if (setGain(5) == 0) {
		state = RUNNING;
	} else {
		state = ERROR;
	}
}

void initAllSensors() {
	initSensor();
}