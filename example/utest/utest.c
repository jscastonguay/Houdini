#include "../../src/houdini.h"
#include "../../example/app/application.c"


/******************************************************************************/

TEST(application_reset)
	temperature = 100;
	Application_reset();
	ASSERT(temperature == -1);
END_TEST

/******************************************************************************/

CREATE_MOCK_V0(ADC_init);
CREATE_MOCK_0(ADC_Status, ADC_getStatus);

void ADC_init_1() {}
ADC_Status ADC_getStatus_OK() { return ADC_OK; }

TEST(application_init_ADCStatusOK)

	SUB(ADC_init, ADC_init_1, 1);
	SUB(ADC_getStatus, ADC_getStatus_OK, 1);

	int result = Application_init();

	ASSERT(result == 0);

END_TEST

/******************************************************************************/

ADC_Status ADC_getStatus_ERROR() { return ADC_ERROR; }

TEST(application_init_ADCStatusERROR)

	SUB(ADC_init, ADC_init_1, 1);
	SUB(ADC_getStatus, ADC_getStatus_ERROR, 1);

	int result = Application_init();

	ASSERT(result == 1);

END_TEST

/******************************************************************************/

CREATE_MOCK_1(int, ADC_getRawValue, int);

int ADC_getRawValue_1(int ch) {
  int retValues[] = {100, 200, 300, 400, 500};
  ASSERT(ch == 2);
  unsigned int i = CALLING_INDEX(ADC_getRawValue);
  return retValues[i];
}

TEST(application_computeTemperature)
	SUB(ADC_getRawValue, ADC_getRawValue_1, 5);
	Application_computeTemperature();
	ASSERT(temperature == 30);
END_TEST

/******************************************************************************/

CREATE_MOCK_V1(ADC_getConfig, ADC_Config *);

void ADC_getConfig_givenValues(ADC_Config *config) {
  config->nbChannels = 4;
  config->nbBits = 10;
}

TEST(verifyConfig_returnTrue)
	SUB(ADC_getConfig, ADC_getConfig_givenValues, 1);
	ASSERT(verifyConfig() == true);
END_TEST

/******************************************************************************/

int main() {
  RUN_TEST(application_reset);
  RUN_TEST(application_init_ADCStatusOK);
  RUN_TEST(application_init_ADCStatusERROR);
  RUN_TEST(application_computeTemperature);
  RUN_TEST(verifyConfig_returnTrue);

  return 0;
}