#include "stm32f10x.h"  

int led = 0; //Off = 0, Red = 1, Yellow = 2, Green = 3
int brightness = 1; //Low = 1, Medium = 2, High = 3, Full = 4, 

GPIO_InitTypeDef GPIO_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;
AFIO_TypeDef AFIO_InitStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
NVIC_InitTypeDef NVIC_InitStructure;




void EXTI1_IRQHandler(void) //Switch Led
{
    if(EXTI_GetITStatus(EXTI_Line1) != RESET)
        led++;
        if(led == 4)
        led  = 0;
        EXTI_ClearITPendingBit(EXTI_Line1);
}

void EXTI2_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line2) != RESET)
        brightness++;
        if(brightness == 5)
        brightness = 4;
        EXTI_ClearITPendingBit(EXTI_Line2);
	
}
void EXTI3_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line3) != RESET)
        brightness--;
        if(brightness == -1)
        brightness = 0;
        EXTI_ClearITPendingBit(EXTI_Line3);
}



int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = 35999;
	TIM_TimeBaseStructure.TIM_Prescaler = 19;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OCInitStructure.TIM_Pulse = 9000; 
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	
  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OCInitStructure.TIM_Pulse = 9000; 
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OCInitStructure.TIM_Pulse = 9000; 
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);

	EXTI_DeInit();
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	EXTI_DeInit();
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	EXTI_DeInit();
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	//Red
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//Yellow
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//Green
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//Button1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//Button2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//Button3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	EXTI1_IRQHandler();
	EXTI2_IRQHandler();
	EXTI3_IRQHandler();
	TIM_Cmd(TIM2, ENABLE);

    while(1)
	{
		switch(led)
		{
			case(1):
				TIM_OCInitStructure.TIM_Pulse = 9000*brightness;
				TIM_OC1Init(TIM2, &TIM_OCInitStructure);
				TIM_OCInitStructure.TIM_Pulse = 0;
				TIM_OC2Init(TIM2, &TIM_OCInitStructure);
				TIM_OCInitStructure.TIM_Pulse = 0;
				TIM_OC3Init(TIM2, &TIM_OCInitStructure);
				break;
			case(2):
				TIM_OCInitStructure.TIM_Pulse = 0;
				TIM_OC1Init(TIM2, &TIM_OCInitStructure);
				TIM_OCInitStructure.TIM_Pulse = 9000*brightness;
				TIM_OC2Init(TIM2, &TIM_OCInitStructure);
				TIM_OCInitStructure.TIM_Pulse = 0;
				TIM_OC3Init(TIM2, &TIM_OCInitStructure);
				break;
			case(3):
				TIM_OCInitStructure.TIM_Pulse = 0;
				TIM_OC1Init(TIM2, &TIM_OCInitStructure);
				TIM_OCInitStructure.TIM_Pulse = 0;
				TIM_OC2Init(TIM2, &TIM_OCInitStructure);
				TIM_OCInitStructure.TIM_Pulse = 9000*brightness;
				TIM_OC3Init(TIM2, &TIM_OCInitStructure);
				break;
			default:
				TIM_OCInitStructure.TIM_Pulse = 0;
				TIM_OC1Init(TIM2, &TIM_OCInitStructure);
				TIM_OCInitStructure.TIM_Pulse = 0;
				TIM_OC2Init(TIM2, &TIM_OCInitStructure);
				TIM_OCInitStructure.TIM_Pulse = 0;
				TIM_OC3Init(TIM2, &TIM_OCInitStructure);
		}
	} 			
}
