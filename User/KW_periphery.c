#include "KW_periphery.h"
#include "stdlib.h"

int getWLev(int *flag_water) {
	if (TM_ADC_Read(WLev)>100) //¦³¤ô ADC­È>100
		return 1;
	*flag_water = 0;
	return 0;
}

void getWet(int *Wet) {
	int i = 0;
	if (TM_ADC_Read(Wet1)>100)
		Wet[i] = 1;
	else
		Wet[i] = 0;
	i++;
	if (TM_ADC_Read(Wet2)>100)
		Wet[i] = 1;
	else
		Wet[i] = 0;
	i++;
	if (TM_ADC_Read(Wet3)>100)
		Wet[i] = 1;
	else
		Wet[i] = 0;
	i++;
	if (TM_ADC_Read(Wet4)>100)
		Wet[i] = 1;
	else
		Wet[i] = 0;
	i++;
	if (TM_ADC_Read(Wet5)>100)
		Wet[i] = 1;
	else
		Wet[i] = 0;
	i++;
	if (TM_ADC_Read(Wet6)>100)
		Wet[i] = 1;
	else
		Wet[i] = 0;
	i++;
	if (TM_ADC_Read(Wet7)>100)
		Wet[i] = 1;
	else
		Wet[i] = 0;
	i++;
	if (TM_ADC_Read(Wet8)>100)
		Wet[i] = 1;
	else
		Wet[i] = 0;
}

float getFlwValue(float Frequency) {
	Frequency /= 7.5;
	Frequency /= 3600;
	return Frequency;
}