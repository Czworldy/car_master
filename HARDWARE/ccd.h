#ifndef __CCD_H
#define __CCD_H

#include "sys.h"
#include "MyTypeDef.h"

#define TSL1401_CLK PFout(9)
#define TSL1401_SI  PFout(10)

#define TSL1401_ADC_Channel_Size 4
#define TSL1401_ADC_Buffer_Size 128

#define Front 0
#define Back 1
#define Left 2
#define Right 3

extern struct CCD_State TSL1401_State[];

extern uint8_t TSL1401_Mode;
extern uint8_t TSL1401_Is_Find_ADC_Threshold;

extern uint16_t TSL1401_cnt;
extern uint8_t TSL1401_Cal_Ready;

extern volatile uint16_t ADC_ConvertedValue[TSL1401_ADC_Channel_Size];
extern volatile uint16_t TSL1401_ADC_Buffer[TSL1401_ADC_Buffer_Size][TSL1401_ADC_Channel_Size];
extern uint8_t TSL1401_ADC_Buffer_Idx;

extern uint8_t TSL1401_Hash_Table[TSL1401_ADC_Channel_Size];	//Channel Index To Direction

void TSL1401_Init(void);
void TSL1401_GPIO_Init(void);
void TSL1401_ADC_Init(void);
void TSL1401_TIM_Init(void);
void TSL1401_Hash_Table_Init(void);

void TSL1401_Measure(u8 find_adc_threshold_en);
void TSL1401_Find_ADC_Max_Min_Threshold(u8 find_adc_threshold_en);
void TSL1401_Edge_Detect(void);

void TSL1401_SetEnabled(u8 enabled);
void TSL1401_Refresh(void);

#endif
