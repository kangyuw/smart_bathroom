#include "wifi_command.h"
#include "KW_function.h"

#include "tm_stm32f4_delay.h"

#include "tm_stm32f4_rtc.h"

int getWLev(int *flag_water);
void getWet(int *Wet);
float getFlwValue(float Frequency);

#define Wet1 ADC1, ADC_Channel_1 //PA1
#define Wet2 ADC1, ADC_Channel_2 //PA2
#define Wet3 ADC1, ADC_Channel_3 //PA3
#define Wet4 ADC1, ADC_Channel_4 //PA4
#define Wet5 ADC1, ADC_Channel_5 //PA5
#define Wet6 ADC1, ADC_Channel_6 //PA6
#define Wet7 ADC1, ADC_Channel_7 //PA7
#define Wet8 ADC1, ADC_Channel_8 //PB0
#define WLev ADC1, ADC_Channel_9 //PB1