#include "main.h"
#include "string.h"
/*save date data*/
TM_RTC_Time_t datatime;
char timebuf[50];
//char sec[10];
char * USART3_ReadLine();

const uint32_t unix_start=1483228800; 
uint32_t A;//Per 10minutes send
uint32_t B;// Per hour send
uint32_t C;//for test
uint32_t tmp;//for temp
uint32_t chektime;

int main(void) {
	
		/*初始化*/
		TM_Delay_Init();
		USART3_init();
		
		/*發送初始訊息*/
		USART3_Printf("AT+CWMODE=3\r\n");
		Delayms(500);
//		USART3_Printf("AT+CWJAP=\"b10232022\",\"12345678\"\r\n");
		USART3_Printf("AT+CWJAP=\"dlink-ccg\",\"ccgccg7716\"\r\n");
		Delayms(500);
	
		if (!TM_RTC_Init(TM_RTC_ClockSource_Internal)) {
				 wificommand_checktime();
			/*
					datatime.hours=00;
					datatime.minutes=59;
					datatime.seconds=55;
					datatime.year = 17;
					datatime.month = 1;
					datatime.date = 17;
					datatime.day = 1;
			*/
					TM_RTC_SetDateTime(&datatime, TM_RTC_Format_BIN);
		}
		
		
		
		TM_RTC_GetDateTime(&datatime, TM_RTC_Format_BIN);
		sprintf(timebuf, "Unix: %u\n",datatime.unix);
		USART3_Printf(timebuf);
		
		if((datatime.unix-unix_start)%600 != 0)
		{
			tmp=(datatime.unix-unix_start)/600;
			A=(tmp+1)*600+unix_start;
		}
		else
			A=datatime.unix;
		
		if((datatime.unix-unix_start)% 3600 != 0)
		{
			tmp=(datatime.unix-unix_start)/3600;
			B=(tmp+1)*3600+unix_start;
		}
		else
			B=datatime.unix;
		
		if((datatime.unix-unix_start)% 30 != 0)
		{
			tmp=(datatime.unix-unix_start)/30;
			C=(tmp+1)*30+unix_start;
		}
		else
			C=datatime.unix;
		
			TM_RTC_RequestHandler();
			USART3_Printf(timebuf);
		
		while(1)
		{
					TM_RTC_GetDateTime(&datatime, TM_RTC_Format_BIN);
					//sprintf(timebuf, "Unix: %u\n",datatime.unix);
					//USART3_Printf(timebuf);
			
					if(datatime.unix == A)
					{
						A=datatime.unix+600;
						sprintf(timebuf, "%02d:%02d:%02d  \n",datatime.hours,datatime.minutes,datatime.seconds);
						USART3_Printf(timebuf);
					}
					if(datatime.unix == B)
					{
						B=datatime.unix+3600;
						sprintf(timebuf, "%02d:%02d:%02d  \n",datatime.hours,datatime.minutes,datatime.seconds);
						USART3_Printf(timebuf);
					}
					
					if(datatime.unix == C)
					{
						C=datatime.unix+30;
						sprintf(timebuf, "%02d:%02d:%02d  \n",datatime.hours,datatime.minutes,datatime.seconds);
						USART3_Printf(timebuf);
					}
		}
}
	
char * USART3_ReadLine(){
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET){
        char c = USART_ReceiveData(USART3);         
        if(c != '\r' && c != '\n'){
            sprintf (buff, "%s%c", buff, c);
        }else{

            memcpy(buff2,buff, strlen(buff)); // 將 buff 複製到 buff2
            memset(buff, 0, strlen(buff)); // 清除 buff 字串裡所有內容            
            return buff2;
        }
    }
    return "";
}

void USART3_IRQHandler(){
		char* data =  USART3_ReadLine();
		if(flag_catch==1 && strcmp(data, "")){
			flag_catch=0;
			//USART3_Printf("time recieved");
			//setRTC(data);
			datatime.unix = atoi(data);
		}
		if(!strcmp(data, "<html>")){
			flag_catch=1;
		}
}

	
	void TIM2_IRQHandler(void) {
	/* Interrupt request, don't forget! */
	TM_PWMIN_InterruptHandler(&PWMIN_TIM3);
}
	
/*void TM_RTC_AlarmAHandler(void) {
		wificommand_checktime();
}*/
/*
void EXTI0_IRQHandler(){
    if(EXTI_GetFlagStatus(EXTI_Line0)==SET){  // 判斷 EXTI_Line0 目前是否被執行
				flag_button=1;
        EXTI_ClearITPendingBit(EXTI_Line0);    // 清除 EXTI_Line0 外部中斷
    }
}*/

