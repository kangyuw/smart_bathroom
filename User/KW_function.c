#include "KW_function.h"

void Button_init() {
	//宣告

	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	// 啟用 GPIOA 時鐘
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	// 啟用 SYSCFG 時鐘
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	// 設定為輸入模式
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	// 設定浮空輸入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	// 設定針腳 0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	// 初始化 GPIOA
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// 連接 PA0 到 EXTI0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	// 設定 EXTI_Line0 外部中斷
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	// 設定中斷模式
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	// 使用上升緣觸發
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	// 啟用外部中斷
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	// 初始化外部中斷
	EXTI_Init(&EXTI_InitStructure);

	// 設定 EXTI0_IRQn 中斷
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	// 設定搶占式優先級
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	// 設定響應式優先級
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	// 啟用中斷
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// 初始化中斷
	NVIC_Init(&NVIC_InitStructure);

}
void USART3_Printf(char *string) {
	while (*string) {
		/*傳訊息至USART3*/
		USART_SendData(USART3, (unsigned short int) *string++);
		/*等待訊息傳送完畢*/
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
	}
}

void USART3_init(void) {
	/*宣告*/
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/**啟用GPIOC跟USART3的RCC*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/*將 PC10、PC11 連接至 USART3*/
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

	/*PC10為TX*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 使用推挽式輸出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 使用上拉電阻
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 設置為覆用
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // 設定第 10 腳
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 設定 GPIO 速度為 50 MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOC

										   /*PC11為RX*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 設置為覆用
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; // 設定第 11 腳
	GPIO_Init(GPIOC, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOC

										   /*USART基本設定*/
	USART_InitStructure.USART_BaudRate = 115200; // 設定 USART 包率 (每秒位元數) 為 115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 設定 USART 傳輸的資料位元為 8
	USART_InitStructure.USART_StopBits = USART_StopBits_1; // 設定 USART 停止位元為 1
	USART_InitStructure.USART_Parity = USART_Parity_No; // 不使用同位元檢查
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用流量控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // 設定 USART 模式為 Rx (接收) 、 Tx (傳送)
	USART_Init(USART3, &USART_InitStructure); // 套用以上 USART 設置，並初始化UART3
											  /* 啟用 USART3 中斷 */
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ClearFlag(USART3, USART_FLAG_TC);
	/*啟用USART3*/
	USART_Cmd(USART3, ENABLE);
	NVIC_EnableIRQ(USART3_IRQn);
}

void ADC1_init() {
	TM_ADC_Init(ADC1, ADC_Channel_1); //PA1
	TM_ADC_Init(ADC1, ADC_Channel_2); //PA2
	TM_ADC_Init(ADC1, ADC_Channel_3); //PA3
	TM_ADC_Init(ADC1, ADC_Channel_4); //PA4
	TM_ADC_Init(ADC1, ADC_Channel_5); //PA5
	TM_ADC_Init(ADC1, ADC_Channel_6); //PA6
	TM_ADC_Init(ADC1, ADC_Channel_7); //PA7
	TM_ADC_Init(ADC1, ADC_Channel_8); //PB0
	TM_ADC_Init(ADC1, ADC_Channel_9); //PB1
}

void UnixTransform(int timestamp, int *hrs, int *min, int *sec){
	int temp;
	timestamp-=1483228800; // 2017/01/01 0:00:00
	*sec = timestamp%60;
	temp = timestamp % 3600;
	*min = temp/60;
	temp = timestamp % 86400;
	*hrs = temp/3600;
}