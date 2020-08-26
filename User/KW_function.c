#include "KW_function.h"

void Button_init() {
	//�ŧi

	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	// �ҥ� GPIOA ����
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	// �ҥ� SYSCFG ����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	// �]�w����J�Ҧ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	// �]�w�B�ſ�J
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	// �]�w�w�} 0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	// ��l�� GPIOA
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// �s�� PA0 �� EXTI0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	// �]�w EXTI_Line0 �~�����_
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	// �]�w���_�Ҧ�
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	// �ϥΤW�ɽtĲ�o
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	// �ҥΥ~�����_
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	// ��l�ƥ~�����_
	EXTI_Init(&EXTI_InitStructure);

	// �]�w EXTI0_IRQn ���_
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	// �]�w�m�e���u����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	// �]�w�T�����u����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	// �ҥΤ��_
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// ��l�Ƥ��_
	NVIC_Init(&NVIC_InitStructure);

}
void USART3_Printf(char *string) {
	while (*string) {
		/*�ǰT����USART3*/
		USART_SendData(USART3, (unsigned short int) *string++);
		/*���ݰT���ǰe����*/
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
	}
}

void USART3_init(void) {
	/*�ŧi*/
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/**�ҥ�GPIOC��USART3��RCC*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/*�N PC10�BPC11 �s���� USART3*/
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

	/*PC10��TX*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // �ϥα�������X
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // �ϥΤW�Թq��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // �]�m���Х�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // �]�w�� 10 �}
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // �]�w GPIO �t�׬� 50 MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOC

										   /*PC11��RX*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // �]�m���Х�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; // �]�w�� 11 �}
	GPIO_Init(GPIOC, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOC

										   /*USART�򥻳]�w*/
	USART_InitStructure.USART_BaudRate = 115200; // �]�w USART �]�v (�C��줸��) �� 115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; // �]�w USART �ǿ骺��Ʀ줸�� 8
	USART_InitStructure.USART_StopBits = USART_StopBits_1; // �]�w USART ����줸�� 1
	USART_InitStructure.USART_Parity = USART_Parity_No; // ���ϥΦP�줸�ˬd
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ���ϥάy�q����
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // �]�w USART �Ҧ��� Rx (����) �B Tx (�ǰe)
	USART_Init(USART3, &USART_InitStructure); // �M�ΥH�W USART �]�m�A�ê�l��UART3
											  /* �ҥ� USART3 ���_ */
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ClearFlag(USART3, USART_FLAG_TC);
	/*�ҥ�USART3*/
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