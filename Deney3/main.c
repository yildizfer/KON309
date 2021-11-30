#include "stm32f10x.h"

int led = 1; //Off = 0, Red = 1, Yellow = 2, Green = 3
int brightness = 0; //Low = 0, Medium = 1, High = 2, Full = 3

GPIO_InitTypeDef GPIO_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;

TIM_TimeBaseStructure.TIM_Period = 49999;
TIM_TimeBaseStructure.TIM_Prescaler = 143;
TIM_TimeBaseStructure.TIM_ClockDivision = 0;
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // TIM2_CCMR1
TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // TIM2_CCER
TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // TIM2_CCER
TIM_OCInitStructure.TIM_Pulse = 3600; // TIM2_CCR1
TIM_OC2Init(TIM2, &TIM_OCInitStructure);

EXTI_InitStructure.EXTI_Line = EXTI_Line0;
EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
EXTI_InitStructure.EXTI_LineCmd = ENABLE;
EXTI_Init(&EXTI_InitStructure);

void EXTI4_IRQHandler(void) //Switch Led
{
	led++;
	if(led == 4)
	led  = 0;
	EXTI_ClearITPendingBit(EXTI_Line4);
}

void EXTI6_IRQHandler(void)
{
	brightness++;
	if(brightness = 4)
	brightness = 3;
	EXTI_ClearITPendingBit(EXTI_Line5);
}

void EXTI5_IRQHandler(void)
{
	brightness--;
	if(brightness = -1)
	brightness = 0;
	EXTI_ClearITPendingBit(EXTI_Line6);
}

void TIM2_IRQHandler() 
{
	
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	//PWM'li pinler için:
	//https://os.mbed.com/media/uploads/hudakz/stm32f103c8t6_pinout_voltage01.png

	//Red
	AFIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
	AFIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	AFIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	AFIO_Init(GPIOA, &GPIO_InitStructure);
	//Yellow
	AFIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
	AFIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	AFIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	AFIO_Init(GPIOA, &GPIO_InitStructure);
	//Green
	AFIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
	AFIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	AFIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	AFIO_Init(GPIOA, &GPIO_InitStructure);
	//Button1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);
	//Button2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);
	//Button3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);

	TIM_Cmd(TIM2, ENABLE);

    while(1)
	{
		
	} 			
}