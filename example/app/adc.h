#ifndef ADC_H
#define ADC_H

typedef enum {
    ADC_OK,
    ADC_ERROR
} ADC_Status;

typedef struct {
    unsigned int nbChannels;
    unsigned int nbBits;
} ADC_Config;

void ADC_init();
int ADC_getRawValue(int ch);
ADC_Status ADC_getStatus();
void ADC_getConfig(ADC_Config * config);

#endif