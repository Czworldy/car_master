#include "all.h"

int main(void)
{
	u8 tp_last, key_value, is_key = 0;
//	u8 is_raspberry_pi_ok = 0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);
	LED_Init();
	EXTIX_Init();
	PWM_Init();
	//TIM12_Int_Init(10000-1, 8400-1);
	USART_Config();
	
	
	//Handle_USART_DMA_EN();
	GPS_USART_DMA_EN();
	//Color_USART_DMA_EN();
	
	//TSL1401_Init();
	
	LCD_Init();           //初始化LCD FSMC接口
	LCD_Scan_Dir(R2L_D2U);
	
	use_touch_adj_data = 1;
	tp_dev.init();				//触摸屏初始化
	
	Show_Menu_List();
	
	PID_Init();
	
	CANx_Init();
	//Servo_Original_Point_Bend();
	
	while(1)
	{
		
//		if (Camera_RxBuffer[0] == 0xFF)
//		{
//			is_raspberry_pi_ok = 1;
//			Camera_RxBuffer[0] = 0;
//		}
//		if (is_raspberry_pi_ok)
//		{
//			LCD_printf(0,6+36*4,300,24,24,"Raspberry Pi OK");
//		}
		#ifdef BSP_USING_TOUCH_SCREEN
		tp_last = tp_dev.sta&TP_PRES_DOWN;
		tp_dev.scan(0);
		if ((tp_dev.sta&TP_PRES_DOWN) && !tp_last)
		{
			key_value = TP_MainMenu_Judge(tp_dev.x[0], tp_dev.y[0]);
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
			KeyNumOperate(key_value);
		}
		else
			delay_ms(1);	//没有按键按下的时候
	}
}
