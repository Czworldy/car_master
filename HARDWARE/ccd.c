#include "ccd.h"
#include <math.h>
#include <stdlib.h>
/*
		back 1
right 3			front 0
		left 2
*/
struct CCD_State TSL1401_State[TSL1401_ADC_Channel_Size]  = {
	{-100.0/89.0, 2353, 1450, 3},	//Front
	{-100.0/95.0, 3012, 900, 1},	//Back
	{100.0/86.0, 3037, 881, 0},	//Left
	{100.0/102.0, 2419, 1392, 2},	//Right
//	{140.0/80.0, 1000, 1700, 3},	//Front
//	{100.0/102.0, 950, 1900, 1},	//Back
//	{140.0/80.0, 1400, 2000, 0},	//Left
//	{100.0/102.0, 175*16, 1200, 2},	//Right
};

uint8_t TSL1401_Mode = 0;	//0:线为黑色，1:线为白色
uint8_t TSL1401_Is_Find_ADC_Threshold = 1;	//若为1，则使用结构体中的ADC阈值

uint16_t TSL1401_cnt = 0;
uint8_t TSL1401_Cal_Ready = 0;

__IO uint16_t ADC_ConvertedValue[TSL1401_ADC_Channel_Size] = {0};
__IO uint16_t TSL1401_ADC_Buffer[TSL1401_ADC_Buffer_Size][TSL1401_ADC_Channel_Size] = {0};
uint8_t TSL1401_ADC_Buffer_Idx = 0;

uint8_t TSL1401_Hash_Table[TSL1401_ADC_Channel_Size];	//Channel Index To Direction

void TSL1401_Init(void)
{
	TSL1401_Hash_Table_Init();
	TSL1401_GPIO_Init();
	TSL1401_ADC_Init();
	TSL1401_TIM_Init();
}

void TSL1401_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//上拉
	GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIO
	
	TSL1401_CLK = 0;
	TSL1401_SI = 0;
}

void TSL1401_ADC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ((u32)ADC1+0x4c);	
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC_ConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = TSL1401_ADC_Channel_Size;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);

	DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TC);
	DMA_ClearFlag(DMA2_Stream0, DMA_IT_TCIF0);	
	DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, ENABLE);

	DMA_Cmd(DMA2_Stream0, DISABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles;  
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_StructInit(&ADC_InitStructure);
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; 
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = TSL1401_ADC_Channel_Size;                                    
	ADC_Init(ADC1, &ADC_InitStructure);
	//---------------------------------------------------------------------------

	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_56Cycles);  //PC0
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_56Cycles);  //PC1
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 3, ADC_SampleTime_56Cycles);  //PC2
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 4, ADC_SampleTime_56Cycles);  //PC3

	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TSL1401_TIM_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM时钟
	
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_Period = 1680 - 1;//4200-1;//14700-1;//4200-1;//16800-1;	//1680-1;   //自动重装载值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //允许定时器更新中断
	TIM_Cmd(TIM3, DISABLE); //失能定时器
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //定时器中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00; //子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TSL1401_Hash_Table_Init(void)
{
	u8 i;
	
	for (i = 0; i < TSL1401_ADC_Channel_Size; ++i)
	{
		TSL1401_Hash_Table[TSL1401_State[i].ADC_Channel_Index] = i;
	}
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		if (TSL1401_cnt == 0)
		{
			TSL1401_Cal_Ready = 0;
			TSL1401_CLK = 0;
			TSL1401_SI = 1;
			++TSL1401_cnt;
		}
		else if (TSL1401_cnt == 1)
		{			
			TSL1401_CLK = 1;
			TSL1401_SI = 1;
			++TSL1401_cnt;
		}
		else if (TSL1401_cnt < 258)
		{
			if ((TSL1401_cnt & 1) == 0)
			{
				TSL1401_CLK = 0;
				TSL1401_SI = 0;
				ADC_SoftwareStartConv(ADC1);
			}
			else
			{
				TSL1401_CLK = 1;
				TSL1401_SI = 0;
			}
			++TSL1401_cnt;
		}
		else if (TSL1401_cnt == 258)
		{
			TSL1401_CLK = 0;
			TSL1401_SI = 0;
			++TSL1401_cnt;
		}
		else if (TSL1401_cnt == 259)
		{
			TSL1401_CLK = 0;
			TSL1401_SI = 0;
			++TSL1401_cnt;
		}
		else if (TSL1401_cnt < 310 - 1)
		{
			++TSL1401_cnt;
		}
		else if (TSL1401_cnt == 310 - 1)
		{
			TSL1401_cnt = 0;
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除中断标志位
	}
}

void DMA2_Stream0_IRQHandler(void)
{
	u8 j;
//	u8 k;
//	struct CCD_State *ptr;
	
	if (DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0) == SET)
	{
		//Get Max and Min
		for (j = 0; j < TSL1401_ADC_Channel_Size; ++j)
		{
			TSL1401_ADC_Buffer[TSL1401_ADC_Buffer_Idx][j] = ADC_ConvertedValue[j];
			
//			k = TSL1401_Hash_Table[j];
//			ptr = &TSL1401_State[k];
//			
//			if (TSL1401_ADC_Buffer_Idx == 0+5)
//				ptr->ADC_Max = ptr->ADC_Min = ADC_ConvertedValue[j];
//			else if (TSL1401_ADC_Buffer_Idx < TSL1401_ADC_Buffer_Size - 5)
//			{
//				if (ptr->ADC_Max < ADC_ConvertedValue[j])
//					ptr->ADC_Max = ADC_ConvertedValue[j];
//				if (ptr->ADC_Min > ADC_ConvertedValue[j])
//					ptr->ADC_Min = ADC_ConvertedValue[j];
//			}
		}
		
		if (TSL1401_ADC_Buffer_Idx + 1 >= TSL1401_ADC_Buffer_Size)
		{
			TSL1401_ADC_Buffer_Idx = 0;
			TSL1401_Cal_Ready = 1;
			
//			for (k = 0; k < TSL1401_ADC_Channel_Size; ++k)
//			{
//				ptr = &TSL1401_State[k];
//				ptr->ADC_Median = (ptr->ADC_Max + ptr->ADC_Min) / 2;
//			}
			
//			//Find ADC Threshold If Needed
//			TSL1401_Find_ADC_Threshold();
//			//Edge Detect
//			TSL1401_Edge_Detect();
//			//Find Line Threshold After Edge_Detect If Needed
//			TSL1401_Find_Line_Threshold();
		}
		else
			++TSL1401_ADC_Buffer_Idx;
		
		DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);
	}
}

void TSL1401_Measure(u8 find_adc_threshold_en)
{
	TSL1401_Find_ADC_Max_Min_Threshold(find_adc_threshold_en);
	TSL1401_Edge_Detect();
}

void TSL1401_Find_ADC_Max_Min_Threshold(u8 find_adc_threshold_en)
{
	u8 i, j, k;
	struct CCD_State *ptr;
	
	for (i = 0; i < TSL1401_ADC_Buffer_Size; ++i)
	{
		for (j = 0; j < TSL1401_ADC_Channel_Size; ++j)
		{
			if (i == 0+5)
			{
				k = TSL1401_Hash_Table[j];
				ptr = &TSL1401_State[k];
				ptr->ADC_Max = ptr->ADC_Min = TSL1401_ADC_Buffer[i][j];
			}
			else if (i < TSL1401_ADC_Buffer_Size - 5)
			{
				k = TSL1401_Hash_Table[j];
				ptr = &TSL1401_State[k];
				if (ptr->ADC_Max < TSL1401_ADC_Buffer[i][j])
					ptr->ADC_Max = TSL1401_ADC_Buffer[i][j];
				if (ptr->ADC_Min > TSL1401_ADC_Buffer[i][j])
					ptr->ADC_Min = TSL1401_ADC_Buffer[i][j];
			}
		}
	}
	
	if (find_adc_threshold_en)
	{
		for (k = 0; k < TSL1401_ADC_Channel_Size; ++k)
		{
			ptr = &TSL1401_State[k];
			
			if (TSL1401_Mode)
			{
				ptr->Line_ADC_Threshold = ptr->ADC_Max - (ptr->ADC_Max - ptr->ADC_Min) / 5;
			}
			else
			{
				ptr->Line_ADC_Threshold = ptr->ADC_Min + (ptr->ADC_Max - ptr->ADC_Min) / 5;
			}
			ptr->Difference_ADC_Threshold = (ptr->ADC_Max - ptr->ADC_Min) * 2 / 3;
		}
		TSL1401_Is_Find_ADC_Threshold = 1;
	}
}

void TSL1401_Edge_Detect(void)	//对应方向:0:成功,1:检测到全都为线,2:检测到全都为场地,3:未设定阈值,4:线宽超出
{
	u8 i, j, k;
	struct CCD_State *ptr;
	
	if (!TSL1401_Is_Find_ADC_Threshold)
	{
		for (j = 0; j < TSL1401_ADC_Channel_Size; ++j)
		{
			k = TSL1401_Hash_Table[j];
			ptr = &TSL1401_State[k];
			
			ptr->Line_Edge_Type = 3;
		}
		return;
	}
	
	for (j = 0; j < TSL1401_ADC_Channel_Size; ++j)
	{
		k = TSL1401_Hash_Table[j];
		ptr = &TSL1401_State[k];
		
		if (ptr->ADC_Max - ptr->ADC_Min <= ptr->Difference_ADC_Threshold)
		{
			if (TSL1401_Mode)
			{
				if (ptr->ADC_Max >= ptr->Line_ADC_Threshold)
				{
					ptr->Line_Edge_Left_Pos = 5;
					ptr->Line_Edge_Right_Pos = TSL1401_ADC_Buffer_Size - 5 - 5 + 1;
					ptr->Line_Edge_Median_Pos = 0xFF;
					ptr->Line_Edge_Type = 1;
				}
				else
				{
					ptr->Line_Edge_Left_Pos = ptr->Line_Edge_Right_Pos = ptr->Line_Edge_Median_Pos = 0xFF;
					ptr->Line_Edge_Type = 2;
				}
			}
			else
			{
				if (ptr->ADC_Min <= ptr->Line_ADC_Threshold)
				{
					ptr->Line_Edge_Left_Pos = 5;
					ptr->Line_Edge_Right_Pos = TSL1401_ADC_Buffer_Size - 5 - 5 + 1;
					ptr->Line_Edge_Median_Pos = 0xFF;
					ptr->Line_Edge_Type = 1;
				}
				else
				{
					ptr->Line_Edge_Left_Pos = ptr->Line_Edge_Right_Pos = ptr->Line_Edge_Median_Pos = 0xFF;
					ptr->Line_Edge_Type = 2;
				}
			}
			continue;
		}
		ptr->Line_Edge_Left_Pos = 0;
		ptr->Line_Edge_Right_Pos = 128;
		
		if (TSL1401_Mode)
		{
			for (i = 5; i < TSL1401_ADC_Buffer_Size - 5 - 5; ++i)
			{
				if (TSL1401_ADC_Buffer[i][j] < ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+1][j] < ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+2][j] < ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+3][j] >= ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+4][j] >= ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+5][j] >= ptr->Line_ADC_Threshold)
				{
					ptr->Line_Edge_Left_Pos = i+2;
					break;
				}
			}
			for (i = TSL1401_ADC_Buffer_Size - 5 - 5 - 1; i >= 5; --i)
			{
				if (TSL1401_ADC_Buffer[i][j] >= ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+1][j] >= ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+2][j] >= ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+3][j] < ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+4][j] < ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+5][j] < ptr->Line_ADC_Threshold)
				{
					ptr->Line_Edge_Right_Pos = i+2;
					break;
				}
			}
		}
		else
		{
			for (i = 5; i < TSL1401_ADC_Buffer_Size - 5 - 5; ++i)
			{
				if (TSL1401_ADC_Buffer[i][j] > ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+1][j] > ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+2][j] > ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+3][j] <= ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+4][j] <= ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+5][j] <= ptr->Line_ADC_Threshold)
				{
					ptr->Line_Edge_Left_Pos = i+2;
					break;
				}
			}
			for (i = TSL1401_ADC_Buffer_Size - 5 - 5 - 1; i >= 5; --i)
			{
				if (TSL1401_ADC_Buffer[i][j] <= ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+1][j] <= ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+2][j] <= ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+3][j] > ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+4][j] > ptr->Line_ADC_Threshold && 
					TSL1401_ADC_Buffer[i+5][j] > ptr->Line_ADC_Threshold)
				{
					ptr->Line_Edge_Right_Pos = i+2;
					break;
				}
			}
		}
		ptr->Line_Edge_Distance = abs(ptr->Line_Edge_Left_Pos - ptr->Line_Edge_Right_Pos);
		ptr->Line_Edge_Median_Pos = (ptr->Line_Edge_Left_Pos + ptr->Line_Edge_Right_Pos) / 2;
//		if(ptr->Line_Edge_Distance > 40)
//			ptr->Line_Edge_Type = 4;
//		else
			ptr->Line_Edge_Type = 0;
	}
}

void TSL1401_SetEnabled(u8 enabled)
{
	if (enabled)
	{
		TSL1401_Init();
		
		TIM_Cmd(TIM3, ENABLE);
		DMA_SetCurrDataCounter(DMA2_Stream0, TSL1401_ADC_Channel_Size);
		DMA_Cmd(DMA2_Stream0, ENABLE);
	}
	else
	{
		TIM_Cmd(TIM3, DISABLE);
		DMA_Cmd(DMA2_Stream0, DISABLE);
		
		DMA_DeInit(DMA2_Stream0);
		ADC_DeInit();
		TIM_DeInit(TIM3);
		
		TSL1401_cnt = 0;
		TSL1401_ADC_Buffer_Idx = 0;
	}
}

void TSL1401_Refresh(void)
{
	TSL1401_cnt = 0;
}
