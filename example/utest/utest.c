#include <stdio.h>
#include <stdlib.h>

#include "../../src/mock.h"
#include "../../example/app/application.c"

/******************************************************************************/

TEST(application_init)

	for (unsigned int i = 0; i < NB_MEASURENETS_MAX; i++) {
		measures[i] = -1;
	}
	currentTemp = -1;
	
	application_init();
	
	ASSERT(currentTemp == 0);
	ASSERT(state == IDLE);
	
END_TEST

/******************************************************************************/

CREATE_MOCK_0(int, getVoltage);

int getVoltage_return_2500() {
	return 2500;
}

TEST(getTemperature_with_temp_25_C)

	SUB(getVoltage, getVoltage_return_2500, 1);
	ASSERT(getTemperature() == 25);
	
END_TEST

/******************************************************************************/

CREATE_MOCK_1(int, setGain, int);

int setGain_sub1(int x) {
	ASSERT(x == 5);
	return 0;
}

TEST(configureSensors_withGoodGain)
	SUB(setGain, setGain_sub1, 1);
	configureSensors();
	ASSERT(state == RUNNING);
END_TEST

/******************************************************************************/

int setGain_sub2(int x) {
	ASSERT(x == 5);
	return 1;
}

TEST(configureSensors_withWrongGain)
	SUB(setGain, setGain_sub2, 1);
	configureSensors();
	ASSERT(state == ERROR);
END_TEST

/******************************************************************************/

CREATE_MOCK_V0(initSensor);

TEST(initAllSensors_without_function_sub)
	SUB(initSensor, NULL, 1);
	initAllSensors();
END_TEST

/******************************************************************************/

int main() {
	
	RUN_TEST(application_init);
	RUN_TEST(getTemperature_with_temp_25_C);
	RUN_TEST(configureSensors_withGoodGain);
	RUN_TEST(configureSensors_withWrongGain);
	RUN_TEST(initAllSensors_without_function_sub);
	
	return 0;
}