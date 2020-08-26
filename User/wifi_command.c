#include "wifi_command.h"

void wificommand_BUT(void) {
	int Cmd_len = 0;
	char buf[100];
	USART3_Printf(NET);
	Delayms(50);

	Cmd_len += (unsigned)strlen(HEAD_BUT);
	Cmd_len += 12;
	sprintf((char*)buf, WIFILEN, Cmd_len);
	USART3_Printf(buf);
	Delayms(50);

	USART3_Printf(HEAD_BUT);
	USART3_Printf(CHIP);

	USART3_Printf("&But=1");
	USART3_Printf("\r\n");
	Delayms(500);
}
void wificommand_LEV() {
	int Cmd_len = 0;
	char buf[100];
	USART3_Printf(NET);
	Delayms(50);

	Cmd_len += (unsigned)strlen(HEAD_LEV);
	Cmd_len += 12;
	sprintf((char*)buf, WIFILEN, Cmd_len);
	USART3_Printf(buf);
	Delayms(50);

	USART3_Printf(HEAD_LEV);
	USART3_Printf(CHIP);

	sprintf((char*)buf, "&Lev=1");
	USART3_Printf(buf);
	USART3_Printf("\r\n");
	Delayms(500);
}

void wificommand_10m(int WTem, int Tem, int Hum, int Wet[]) {
	int Cmd_len = 0, i;
	char buf[100];
	USART3_Printf(NET);
	Delayms(50);

	Cmd_len += (unsigned)strlen(HEAD_10m);
	Cmd_len += 84;
	sprintf((char*)buf, WIFILEN, Cmd_len);
	USART3_Printf(buf);
	Delayms(50);

	USART3_Printf(HEAD_10m);
	USART3_Printf(CHIP);

	USART3_Printf("&");
	USART3_Printf("Tem=");
	sprintf((char*)buf, "%2d", Tem);
	USART3_Printf(buf);

	USART3_Printf("&");
	USART3_Printf("Hum=");
	sprintf((char*)buf, "%2d", Hum);
	USART3_Printf(buf);

	USART3_Printf("&");
	USART3_Printf("WTem=");
	sprintf((char*)buf, "%2d", WTem);
	USART3_Printf(buf);

	for (i = 0; i <= 7; i++)
	{
		sprintf((char*)buf, "&Wet%1d=%1d", i, Wet[i]);
		USART3_Printf(buf);
	}



	USART3_Printf("\r\n");
	Delayms(500);
}

void wificommand_1h(float Flw_total) {
	int Cmd_len = 0;
	char buf[100];
	USART3_Printf(NET);
	Delayms(50);

	Cmd_len += (unsigned)strlen(HEAD_1h);
	Cmd_len += 17;
	sprintf((char*)buf, WIFILEN, Cmd_len);
	USART3_Printf(buf);
	Delayms(50);

	USART3_Printf(HEAD_1h);
	USART3_Printf(CHIP);

	sprintf((char*)buf, "&Flw=%6.3f", Flw_total);
	USART3_Printf(buf);
	USART3_Printf("\r\n");
	Delayms(500);
}

void wificommand_checktime() {
	int Cmd_len = 0;
	char buf[300];
	USART3_Printf(NET);
	Delayms(100);

	Cmd_len += (unsigned)strlen(HEAD_CHECKTIME);
	//Cmd_len += 19;
	sprintf((char*)buf, WIFILEN, Cmd_len);
	USART3_Printf(buf);
	Delayms(100);

	USART3_Printf(HEAD_CHECKTIME);
}