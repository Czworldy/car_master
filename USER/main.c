#include "all.h"


int main(void)
{
	static u8 is_key = 0;
	u8 is_raspberry_pi_ok = 0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);
	LED_Init();
//	EXTIX_Init();
	PWM_Init();  //wheels
	TIM12_Int_Init(10000-1, 8400-1);
	USART_Config();
	
	
	//Handle_USART_DMA_EN();
	GPS_USART_DMA_EN();
	//Color_USART_DMA_EN();
	
	TSL1401_Init();
	
	LCD_Init();           //初始化LCD FSMC接口
	LCD_Scan_Dir(R2L_D2U);
	
	use_touch_adj_data = 1;
	tp_dev.init();				//触摸屏初始化
	
	Show_Menu_List();
	
	PID_Init();
	
	CANx_Init();
	
	set_loc[1] = PanTilt_Zero;
	//Servo_Original_Point_Bend();
	USART_SendByte(USART2 , 'a');
	while(1)
	{
		
		if (Camera_RxBuffer[0] == 0xFF)
		{
			is_raspberry_pi_ok = 1;
			Camera_RxBuffer[0] = 0;
		}
		if (is_raspberry_pi_ok)
		{
			LCD_printf(0,6+36*4,300,24,24,"Raspberry Pi OK");
		}
		is_key =keyScan(MAINMENU);
		if (is_key)
		{
			is_key = 0;
			KeyNumOperate(keyValue);
		}
		else
			delay_ms(1);	//没有按键按下的时候
	}
}
