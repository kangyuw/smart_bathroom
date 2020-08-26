#include "main.h"

int Tem = 0, Hum = 0, But = 0, WTem = 0, Wet[8] = { 0 };
int flag_catch = 0, flag_water = 0, flag_button = 0;
int hrs, min, sec;
float Flw_total, tempWTem;
uint8_t tempHum, tempTem;
char buff[100] = "";
char buff_temp[100] = "";
char time_temp[10] = "";

char test_temp[100] = "";

const uint32_t unix_start = 1483228800;
uint32_t A; //Per 10minutes Alarm
uint32_t B; // Per hour Alarm
uint32_t C; //test

uint32_t temp32;

//structure
TM_PWMIN_t PWMIN_TIM2;
TM_OneWire_t OneWire1;
TM_RTC_Time_t datatime;

char * USART3_ReadLine();

int main(void) {

	//初始化
	TM_DELAY_Init();
	USART3_init();
	ADC1_init();
	TM_OneWire_Init(&OneWire1, GPIOD, GPIO_Pin_0);
	DHT11initTIM5();
	TM_PWMIN_InitTimer(TIM2, &PWMIN_TIM2, TM_PWMIN_Channel_2, TM_PWMIN_PinsPack_2, 1, TIM2_IRQn);
	Button_init();

	//發送初始訊息
	USART3_Printf("AT+CWMODE=3\r\n");
	Delayms(500);
//	USART3_Printf("AT+CWJAP=\"b10232022\",\"12345678\"\r\n");
	USART3_Printf("AT+CWJAP=\"dlink-ccg\",\"ccgccg7716\"\r\n");
	Delayms(5000);
	
	wificommand_checktime();

	while (!strcmp(time_temp, "")) {} //等待接收
		
	USART3_Printf("49\r\n");
	
	UnixTransform(atoi(time_temp), &hrs, &min, &sec); //將unix時間轉換成BCD時間
	
	USART3_Printf("53\r\n");

	if (!TM_RTC_Init(TM_RTC_ClockSource_Internal)) { //開機對時
		datatime.hours = hrs;
		datatime.minutes = min;
		datatime.seconds = sec;
		datatime.year = 17;
		datatime.month = 1;
		datatime.date = 1;
		datatime.day = 1;
		TM_RTC_SetDateTime(&datatime, TM_RTC_Format_BIN);
	}

	//RTC Alarm
	if ((datatime.unix - unix_start) % 600 != 0)
	{
		temp32 = (datatime.unix - unix_start) / 600;
		A = (temp32 + 1) * 600 + unix_start;
	}
	else
		A = datatime.unix;

	if ((datatime.unix - unix_start) % 3600 != 0)
	{
		temp32 = (datatime.unix - unix_start) / 3600;
		B = (temp32 + 1) * 3600 + unix_start;
	}
	else
		B = datatime.unix;
		if ((datatime.unix - unix_start) % 600 != 0)
	{
		temp32 = (datatime.unix - unix_start) / 600;
		A = (temp32 + 1) * 600 + unix_start;
	}
	else
		A = datatime.unix;
	
	if ((datatime.unix - unix_start) % 5 != 0)
	{
		temp32 = (datatime.unix - unix_start) / 5;
		C = (temp32 + 1) * 5 + unix_start;
	}
	else
		C = datatime.unix;

	while (1)
	{
		//RTC目前的時間
		TM_RTC_GetDateTime(&datatime, TM_RTC_Format_BIN);

//		//Button
//		if (flag_button)
//		{
//			wificommand_BUT();
//			flag_button = 0;
//		}
//		//水位
//		if (getWLev(&flag_water) && !flag_water)
//		{
//			wificommand_LEV();
//			flag_water = 1;
//		}
//		//流量
//		TM_PWMIN_Get(&PWMIN_TIM2);
//		if (PWMIN_TIM2.Frequency > 0)
//		{
//			Flw_total += getFlwValue(PWMIN_TIM2.Frequency);
//			sprintf(test_temp, "FLW_total: %f\r\n", Flw_total);
//			USART3_Printf(test_temp);
//		}

		//test
		sprintf(test_temp, "Time: %u\r\n", datatime.unix);
		USART3_Printf(test_temp);

//		if (datatime.unix == A) //every 10min
//		{
//			A = datatime.unix + 600;
//			//DS18b20 水溫
//			TM_DS18B20_StartAll(&OneWire1);
//			while (!TM_DS18B20_AllDone(&OneWire1));

//			if (TM_DS18B20_Read(&OneWire1, 0, &tempWTem) && flag_water) {
//				WTem = tempWTem;
//			}
//			else {
//				WTem = 0;
//			}

//			//DHT11 室溫&濕度
//			DHT11Read(&tempHum, &tempTem);
//			Hum = tempHum;
//			Tem = tempTem;

//			//濕滑
//			getWet(Wet);
//			wificommand_10m(WTem, Tem, Hum, Wet);

//		}

//		if (datatime.unix == B) //every hour
//		{
//			B = datatime.unix + 3600;
//			wificommand_1h(Flw_total);
//			Flw_total = 0;
//		}

		if (datatime.unix == C) //every hour
		{
		C = datatime.unix + 5;
		USART3_Printf("C\r\n");
		}
		
		Delayms(1000);
	}
}

char * USART3_ReadLine() {
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {
		char c = USART_ReceiveData(USART3);
		if (c != '\r' && c != '\n') {
			sprintf(buff, "%s%c", buff, c);
		}
		else {

			memcpy(buff_temp, buff, strlen(buff)); // 將 buff 複製到 buff2
			memset(buff, 0, strlen(buff)); // 清除 buff 字串裡所有內容            
			return buff_temp;
		}
	}
	return "";
}

void USART3_IRQHandler() {
	char* data = USART3_ReadLine();
//	if (flag_catch == 1 && strcmp(data, "")) {
//		flag_catch = 0;
//		sprintf(time_temp, data);
//	}
//	if (!strcmp(data, "<html>")) {
//		flag_catch = 1;
//	}
	if (strlen(data) == 10 && data[0] == '1')
		sprintf(time_temp, "%s", data);
}

void TIM2_IRQHandler(void) {
	TM_PWMIN_InterruptHandler(&PWMIN_TIM2);
}

void EXTI0_IRQHandler() {
	if (EXTI_GetFlagStatus(EXTI_Line0) == SET) {  // 判斷 EXTI_Line0 目前是否被執行
		flag_button = 1;
		EXTI_ClearITPendingBit(EXTI_Line0);    // 清除 EXTI_Line0 外部中斷
	}
}