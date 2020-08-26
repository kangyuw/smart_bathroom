/* Include core modules */
#include "stm32f4xx.h"
#include "string.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_gpio.h"
#include "tm_stm32f4_adc.h"


void USART3_Printf(char *string);
void USART3_init();
void Button_init();
void ADC1_init();
void UnixTransform(int timestamp, int *hrs, int *min, int *sec);
