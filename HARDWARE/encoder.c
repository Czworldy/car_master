#include "encoder.h"
#include "lcd.h"
#include "M_Func.h"
#include "usart.h"
#include "touch.h"
#include "delay.h"
#include "MyTypeDef.h"
#include "motor.h"
#include "mecanum.h"

void Encoder_Init_Convert(void)
{
	u8 tp_last, key_value, is_key = 0;
	
	Motor_Set_Enabled(0);
	
#ifdef BSP_USING_UART4_DMA
	GPS_TxBuffer[0] = 0xFF;
	GPS_TxBuffer[1] = 0xAC;
	GPS_TxBuffer[2] = 0x00;
	GPS_TxBuffer[3] = 0xAC;
	GPS_TxBuffer[8] = 0x00;
	DMA_SetCurrDataCounter(UART4_DMA_TX_STREAM, GPS_TxBufferSize);
	DMA_Cmd(UART4_DMA_TX_STREAM, ENABLE);
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"Now Init Convert");
	
	while (1)
	{
		#ifdef BSP_USING_TOUCH_SCREEN
		tp_last = tp_dev.sta&TP_PRES_DOWN;
		tp_dev.scan(0);
		if ((tp_dev.sta&TP_PRES_DOWN) && !tp_last)
		{
			key_value = TP_Row_Judge(tp_dev.x[0], tp_dev.y[0]);
			if (key_value != keyempty1)
				is_key = 1;
		}
		#endif
		#ifdef BSP_USING_USART_KEY
		#ifdef BSP_USING_TOUCH_SCREEN
		else if (Is_USART_Key_Receive)
		#else
		if (Is_USART_Key_Receive)
		#endif
		{
			Is_USART_Key_Receive = 0;
			key_value = Key_RxBuffer[0];
			if (key_value != keyempty1)
				is_key = 1;
		}
		#endif
		if (is_key)
		{
			is_key = 0;
			switch(key_value)
			{
				case keyback:
					return;
				case keyboardtab:
					KeyBoard_State = !KeyBoard_State;
					Show_Keyboard();
					break;
			}
			Show_Keyboard();
			POINT_COLOR=BLACK;
			LCD_printf(0,6+36*0,300,24,24,"Now Init Convert");
		}
		else
			delay_ms(1);
	}
#endif
}

void Encoder_Init_Radius(void)
{
	u8 tp_last, key_value, is_key = 0;
	
#ifdef BSP_USING_UART4_DMA
	GPS_TxBuffer[0] = 0xFF;
	GPS_TxBuffer[1] = 0xAC;
	GPS_TxBuffer[2] = 0x01;
	GPS_TxBuffer[3] = 0xAC;
	GPS_TxBuffer[8] = 0x00;
	DMA_SetCurrDataCounter(UART4_DMA_TX_STREAM, GPS_TxBufferSize);
	DMA_Cmd(UART4_DMA_TX_STREAM, ENABLE);
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"Now Init Radius");
	LCD_printf(0,6+36*1,300,24,24,"Press any key to start");
	
	while (1)
	{
		#ifdef BSP_USING_TOUCH_SCREEN
		tp_last = tp_dev.sta&TP_PRES_DOWN;
		tp_dev.scan(0);
		if ((tp_dev.sta&TP_PRES_DOWN) && !tp_last)
		{
			key_value = TP_Row_Judge(tp_dev.x[0], tp_dev.y[0]);
			if (key_value != keyempty1)
				is_key = 1;
		}
		#endif
		#ifdef BSP_USING_USART_KEY
		#ifdef BSP_USING_TOUCH_SCREEN
		else if (Is_USART_Key_Receive)
		#else
		if (Is_USART_Key_Receive)
		#endif
		{
			Is_USART_Key_Receive = 0;
			key_value = Key_RxBuffer[0];
			if (key_value != keyempty1)
				is_key = 1;
		}
		#endif
		if (is_key)
		{
			is_key = 0;
			if (key_value == keyback)
				return;
			else if (key_value == keyboardtab)
			{
				KeyBoard_State = !KeyBoard_State;
				Show_Keyboard();
			}
			else
				break;
			Show_Keyboard();
			POINT_COLOR=BLACK;
			LCD_printf(0,6+36*0,300,24,24,"Now Init Radius");
			LCD_printf(0,6+36*1,300,24,24,"Press any key to start");
		}
		else
			delay_ms(1);
	}
	
	Speed_X = Speed_Y = 0;
	Speed_Rotation = 200;
	SetSpeed(Speed_X,Speed_Y,Speed_Rotation);
	
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"Press any key to stop");
	
	while (1)
	{
		#ifdef BSP_USING_TOUCH_SCREEN
		tp_last = tp_dev.sta&TP_PRES_DOWN;
		tp_dev.scan(0);
		if ((tp_dev.sta&TP_PRES_DOWN) && !tp_last)
		{
			key_value = TP_Row_Judge(tp_dev.x[0], tp_dev.y[0]);
			if (key_value != keyempty1)
				is_key = 1;
		}
		#endif
		#ifdef BSP_USING_USART_KEY
		#ifdef BSP_USING_TOUCH_SCREEN
		else if (Is_USART_Key_Receive)
		#else
		if (Is_USART_Key_Receive)
		#endif
		{
			Is_USART_Key_Receive = 0;
			key_value = Key_RxBuffer[0];
			if (key_value != keyempty1)
				is_key = 1;
		}
		#endif
		if (is_key)
		{
			is_key = 0;
			if (key_value == keyback)
				return;
			else if (key_value == keyboardtab)
			{
				KeyBoard_State = !KeyBoard_State;
				Show_Keyboard();
			}
			else
			{
				Speed_X = Speed_Y = 0;
				Speed_Rotation = 0;
				SetSpeed(Speed_X,Speed_Y,Speed_Rotation);
				break;
			}
			Show_Keyboard();
			POINT_COLOR=BLACK;
			LCD_printf(0,6+36*0,300,24,24,"Press any key to stop");
		}
		else
			delay_ms(1);
	}
#endif
}
