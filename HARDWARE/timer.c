#include "timer.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

u32 TIM12_OVERFLOW_CNT = 0;

//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!
void TIM12_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  ///使能TIM时钟

	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 

	TIM_TimeBaseInit(TIM12,&TIM_TimeBaseInitStructure);//初始化TIM
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_BRK_TIM12_IRQn; //定时器中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ClearITPendingBit(TIM12,TIM_IT_Update);  //清除中断标志位
	TIM_ITConfig(TIM12,TIM_IT_Update,ENABLE); //允许定时器更新中断
	TIM_Cmd(TIM12,DISABLE);
}

//定时器中断服务函数
void TIM8_BRK_TIM12_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM12,TIM_IT_Update) == SET) //溢出中断
	{
		++TIM12_OVERFLOW_CNT;
		TIM_ClearITPendingBit(TIM12,TIM_IT_Update);  //清除中断标志位
	}
}
