#include <stdbool.h>
#include "adc.h"

static int temperature = -1;

void Application_reset() {
  temperature = -1;
}

int Application_init() {
  int status;

  ADC_init();
  if (ADC_getStatus() == ADC_OK) {
    status = 0;
  } else {
    status = 1;
  }

  return status;
}

void Application_computeTemperature() {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += ADC_getRawValue(2);
  }

  int average = sum / 5;
  temperature = average / 10;
}

static bool verifyConfig() {
  ADC_Config config;
  ADC_getConfig(&config);
  return (config.nbBits == 10) && (config.nbChannels == 4);
}