#include "all.h"

void sys_CCD(void)
{
	u8 i, j, k, tp_last, key_value, is_key = 0;
	struct CCD_State *ptr;
	u8 ccd_plot_idx = 0, ccd_plot_idx_tot = 4;
	u8 ccd_plot_dir = 0;
	char *ccd_plot_idx_ch[] = {"Binary        ","Waveform      ","Edge          ","ADC Threshold   "};
	char *dir_ch[] = {"Front", "Back ", "Left ", "Right"};
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"1.TSL1401 Mode = %u",TSL1401_Mode);
	LCD_printf(0,6+36*1,300,24,24,"2.Display:%s",ccd_plot_idx_ch[ccd_plot_idx]);
	LCD_printf(0,6+36*2,300,24,24,"3.Plot:%s",dir_ch[ccd_plot_dir]);
	LCD_printf(0,6+36*3,300,24,24,"4.Find ADC Threshold:%u",TSL1401_Is_Find_ADC_Threshold);
	switch (ccd_plot_idx)
	{
		case 0:
			for (k = 0; k < TSL1401_ADC_Channel_Size; ++k)
			{
				ptr = &TSL1401_State[k];
				j = ptr->ADC_Channel_Index;
				LCD_printf(0,6+36*(k+6),300,24,24,"%s/CH%u:",dir_ch[k],j);
			}
			break;
		case 1:
			LCD_printf(0,6+36*4,300,12,12,"255");
			LCD_printf(0,6+36*4+55,300,12,12,"200");
			LCD_printf(0,6+36*4+105,300,12,12,"150");
			LCD_printf(0,6+36*4+155,300,12,12,"100");
			LCD_printf(6,6+36*4+205,300,12,12,"50");
			LCD_printf(12,6+36*4+255+6,300,12,12,"0");
			for (i = 1; i <= 13; ++i)
			{
				if (i <= 9)
					LCD_printf(6*3+i*20-6,6+36*4+255+6,300,12,12,"%u",i*10);
				else
					LCD_printf(6*3+i*20-9,6+36*4+255+6,300,12,12,"%u",i*10);
			}
			break;
		case 2:
			LCD_printf(72,6+36*6,320-72,24,24,"Lp  Rp  Mp  Type");
			for (k = 0; k < TSL1401_ADC_Channel_Size; ++k)
				LCD_printf(0,6+36*(k+7),300,24,24,"%s",dir_ch[k]);
			break;
		case 3:
			LCD_printf(72,6+36*6,320-72,24,24,"Max  Min  Line Diff");
			for (k = 0; k < TSL1401_ADC_Channel_Size; ++k)
				LCD_printf(0,6+36*(k+7),300,24,24,"%s",dir_ch[k]);
			break;
		default:
			break;
	}
	TSL1401_SetEnabled(1);
	delay_ms(500);
	
	while (1)
	{
		if (!TSL1401_Cal_Ready)
			continue;
		TSL1401_Measure(!TSL1401_Is_Find_ADC_Threshold);
		switch (ccd_plot_idx)
		{
			case 0:
				for (k = 0; k < TSL1401_ADC_Channel_Size; ++k)
				{
					ptr = &TSL1401_State[k];
					j = ptr->ADC_Channel_Index;
					for (i = 0 ; i < TSL1401_ADC_Buffer_Size; ++i)
					{
						if (TSL1401_Mode)
						{
							if (TSL1401_ADC_Buffer[i][j] >= ptr->Line_ADC_Threshold)
							{
								POINT_COLOR=LGRAY;
								LCD_DrawRectangle(12*15+i,6+36*(k+6),12*15+i+1,6+36*(k+6)+24);
							}
							else
							{
								POINT_COLOR=BLACK;
								LCD_DrawRectangle(12*15+i,6+36*(k+6),12*15+i+1,6+36*(k+6)+24);
							}
						}
						else
						{
							if (TSL1401_ADC_Buffer[i][j] <= ptr->Line_ADC_Threshold)
							{
								POINT_COLOR=BLACK;
								LCD_DrawRectangle(12*15+i,6+36*(k+6),12*15+i+1,6+36*(k+6)+24);
							}
							else
							{
								POINT_COLOR=LGRAY;
								LCD_DrawRectangle(12*15+i,6+36*(k+6),12*15+i+1,6+36*(k+6)+24);
							}
						}
					}
				}
				break;
			case 1:
				LCD_Fill(18,6+36*4+6,18+20*13,6+36*4+6+5+50*5,WHITE);
				POINT_COLOR=LGRAY;
				for (i = 0; i <= 13; ++i)
					LCD_DrawLine(18+20*i, 6+36*4+6, 18+20*i, 6+36*4+255+6);				//画线
				LCD_DrawLine(18, 6+36*4+6, 18+20*13, 6+36*4+6);				//画线
				for (i = 1; i <= 5; ++i)
					LCD_DrawLine(18, 6+36*4+6+5+50*i, 18+20*13, 6+36*4+6+5+50*i);				//画线
				POINT_COLOR=BLACK;
				ptr = &TSL1401_State[ccd_plot_dir];
				j = ptr->ADC_Channel_Index;
				for (i = 0 ; i < TSL1401_ADC_Buffer_Size - 1; ++i)
				{
					POINT_COLOR=BLACK;
					LCD_DrawLine(18+2*i, 6+36*4+6+255-(TSL1401_ADC_Buffer[i][j] >> 4),
								 18+2*(i+1), 6+36*4+6+255-(TSL1401_ADC_Buffer[i+1][j] >> 4));
				}
				break;
			case 2:
				for (k = 0; k < TSL1401_ADC_Channel_Size; ++k)
				{
					ptr = &TSL1401_State[k];
					LCD_printf(72+12*0,6+36*(k+7),200,24,24,"%u    ",ptr->Line_Edge_Left_Pos);
					LCD_printf(72+12*4,6+36*(k+7),200,24,24,"%u    ",ptr->Line_Edge_Right_Pos);
					LCD_printf(72+12*8,6+36*(k+7),200,24,24,"%u    ",ptr->Line_Edge_Median_Pos);
					LCD_printf(72+12*12,6+36*(k+7),200,24,24,"%u    ",ptr->Line_Edge_Type);
				}
				break;
			case 3:
				for (k = 0; k < TSL1401_ADC_Channel_Size; ++k)
				{
					ptr = &TSL1401_State[k];
					LCD_printf(72+12*0,6+36*(k+7),200,24,24,"%u    ",ptr->ADC_Max);
					LCD_printf(72+12*5,6+36*(k+7),200,24,24,"%u    ",ptr->ADC_Min);
					LCD_printf(72+12*10,6+36*(k+7),200,24,24,"%u    ",ptr->Line_ADC_Threshold);
					LCD_printf(72+12*15,6+36*(k+7),200,24,24,"%u    ",ptr->Difference_ADC_Threshold);
				}
				break;
			default:
				break;
		}
		
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
				case key1:
					TSL1401_Mode = !TSL1401_Mode;
					TSL1401_Is_Find_ADC_Threshold = 0;
					break;
				case key2:
					++ccd_plot_idx;
					if (ccd_plot_idx >= ccd_plot_idx_tot)
						ccd_plot_idx = 0;
					Show_Keyboard();
					break;
				case key3:
					++ccd_plot_dir;
					if (ccd_plot_dir >= TSL1401_ADC_Channel_Size)
						ccd_plot_dir = 0;
					Show_Keyboard();
					break;
				case key4:
					TSL1401_Is_Find_ADC_Threshold = 0;
					break;
				case keyback:
					TSL1401_SetEnabled(0);
					return;
				case keyboardtab:
					KeyBoard_State = !KeyBoard_State;
					Show_Keyboard();
					break;
			}
			POINT_COLOR=BLACK;
			LCD_printf(0,6+36*0,300,24,24,"1.TSL1401 Mode = %u",TSL1401_Mode);
			LCD_printf(0,6+36*1,300,24,24,"2.Display:%s",ccd_plot_idx_ch[ccd_plot_idx]);
			LCD_printf(0,6+36*2,300,24,24,"3.Plot:%s",dir_ch[ccd_plot_dir]);
			LCD_printf(0,6+36*3,300,24,24,"4.Find ADC Threshold:%u",TSL1401_Is_Find_ADC_Threshold);
			switch (ccd_plot_idx)
			{
				case 0:
					for (k = 0; k < TSL1401_ADC_Channel_Size; ++k)
					{
						ptr = &TSL1401_State[k];
						j = ptr->ADC_Channel_Index;
						LCD_printf(0,6+36*(k+6),300,24,24,"%s/CH%u:",dir_ch[k],j);
					}
					break;
				case 1:
					LCD_printf(0,6+36*4,300,12,12,"255");
					LCD_printf(0,6+36*4+55,300,12,12,"200");
					LCD_printf(0,6+36*4+105,300,12,12,"150");
					LCD_printf(0,6+36*4+155,300,12,12,"100");
					LCD_printf(6,6+36*4+205,300,12,12,"50");
					LCD_printf(12,6+36*4+255+6,300,12,12,"0");
					for (i = 1; i <= 13; ++i)
					{
						if (i <= 9)
							LCD_printf(6*3+i*20-6,6+36*4+255+6,300,12,12,"%u",i*10);
						else
							LCD_printf(6*3+i*20-9,6+36*4+255+6,300,12,12,"%u",i*10);
					}
					break;
				case 2:
					LCD_printf(72,6+36*6,320-72,24,24,"Lp  Rp  Mp  Type");
					for (k = 0; k < TSL1401_ADC_Channel_Size; ++k)
						LCD_printf(0,6+36*(k+7),300,24,24,"%s",dir_ch[k]);
					break;
				case 3:
					LCD_printf(72,6+36*6,320-72,24,24,"Max  Min  Line Diff");
					for (k = 0; k < TSL1401_ADC_Channel_Size; ++k)
						LCD_printf(0,6+36*(k+7),300,24,24,"%s",dir_ch[k]);
					break;
				default:
					break;
			}
		}
//		TSL1401_Refresh();
	}
}

void sys_Encoder(void)
{
	u8 tp_last, key_value, is_key = 0;
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"1.Init Convert");
	LCD_printf(0,6+36*1,300,24,24,"2.Init Radius");
	
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
				case key1:
					Encoder_Init_Convert();
					break;
				case key2:
					Encoder_Init_Radius();
					break;
				case keyback:
					return;
				case keyboardtab:
					KeyBoard_State = !KeyBoard_State;
					Show_Keyboard();
					break;
			}
			Show_Keyboard();
			POINT_COLOR=BLACK;
			LCD_printf(0,6+36*0,300,24,24,"1.Init Convert");
			LCD_printf(0,6+36*1,300,24,24,"2.Init Radius");
		}
		else
			delay_ms(1);
	}
}

void sys_GPS(void)
{
	u8 tp_last, key_value, is_key = 0;
	double temp;
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"1.Angle = %lf        ",GPS_List[0].angle);
	LCD_printf(0,6+36*1,300,24,24,"2.X = %lf        ",GPS_List[0].position.x);
	LCD_printf(0,6+36*2,300,24,24,"3.Y = %lf        ",GPS_List[0].position.y);
	LCD_printf(0,6+36*3,300,24,24,"4.GPS Clear");
	LCD_printf(0,6+36*4,300,24,24,"5.Set X");
	LCD_printf(0,6+36*5,300,24,24,"6.Set Y");
	LCD_printf(0,6+36*6,300,24,24,"7.Mecanum Disable");
	
	while (1)
	{
		LCD_printf(0,6+36*0,300,24,24,"1.Angle = %lf        ",GPS_List[0].angle);
		LCD_printf(0,6+36*1,300,24,24,"2.X = %lf        ",GPS_List[0].position.x);
		LCD_printf(0,6+36*2,300,24,24,"3.Y = %lf        ",GPS_List[0].position.y);
		
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
				case key1:
					GPS_Gyro_Set_Zero();
					break;
				case key2:
					GPS_Init(0, GPS_List[0].position.y);
					break;
				case key3:
					GPS_Init(GPS_List[0].position.x, 0);
					break;
				case key4:
					GPS_Clear();
					break;
				case key5:
					Input_DoubleValue(&temp, "X");
					GPS_Init(temp, GPS_List[0].position.y);
					break;
				case key6:
					Input_DoubleValue(&temp, "Y");
					GPS_Init(GPS_List[0].position.x, temp);
					break;
				case key7:
					Motor_Set_Enabled(0);
					break;
				case keyback:
					return;
				case keyboardtab:
					KeyBoard_State = !KeyBoard_State;
					Show_Keyboard();
					break;
			}
			Show_Keyboard();
			POINT_COLOR=BLACK;
			LCD_printf(0,6+36*0,300,24,24,"1.Angle = %lf        ",GPS_List[0].angle);
			LCD_printf(0,6+36*1,300,24,24,"2.X = %lf        ",GPS_List[0].position.x);
			LCD_printf(0,6+36*2,300,24,24,"3.Y = %lf        ",GPS_List[0].position.y);
			LCD_printf(0,6+36*3,300,24,24,"4.GPS Clear");
			LCD_printf(0,6+36*4,300,24,24,"5.Set X");
			LCD_printf(0,6+36*5,300,24,24,"6.Set Y");
			LCD_printf(0,6+36*6,300,24,24,"7.Mecanum Disable");
		}
		else
			delay_ms(1);
	}
}

void sys_Mecanum(void)
{
	u8 i, tp_last, key_value, is_key = 0, en = 1;
	double pwm_rpm[4] = {0};
	double temp = 0;
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	for (i = 0; i < 4; ++i)
	{
		LCD_printf(0,6+36*i,300,24,24,"%d.PWM%d RPM = %lf",i+1,i+1,Motor_Get_Rotation_Speed(i+1));
	}
	LCD_printf(0,6+36*4,300,24,24,"5.Speed_X = %lf",Speed_X);
	LCD_printf(0,6+36*5,300,24,24,"6.Speed_Y = %lf",Speed_Y);
	LCD_printf(0,6+36*6,300,24,24,"7.Speed_Rot = %lf",Speed_Rotation);
	LCD_printf(0,6+36*7,300,24,24,"8.Speed_Stop");
	LCD_printf(0,6+36*8,300,24,24,"9.State:%s",en == 1 ? "Enable" : "Disable");
	LCD_printf(0,6+36*9,300,24,24,"10.Angle = %lf        ",GPS_List[0].angle);
	LCD_printf(0,6+36*10,300,24,24,"11.X = %lf        ",GPS_List[0].position.x);
	LCD_printf(0,6+36*11,300,24,24,"12.Y = %lf        ",GPS_List[0].position.y);
	
	while (1)
	{
		for (i = 0; i < 4; ++i)
		{
			LCD_printf(0,6+36*i,300,24,24,"%d.PWM%d RPM = %lf",i+1,i+1,Motor_Get_Rotation_Speed(i+1));
		}
		LCD_printf(0,6+36*9,300,24,24,"10.Angle = %lf        ",GPS_List[0].angle);
		LCD_printf(0,6+36*10,300,24,24,"11.X = %lf        ",GPS_List[0].position.x);
		LCD_printf(0,6+36*11,300,24,24,"12.Y = %lf        ",GPS_List[0].position.y);
		
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
			switch (key_value)
			{
				case key1:
					Input_DoubleValue(&pwm_rpm[0],"PWM1");
					if (fabs(pwm_rpm[0]) <= RPM_Limit)
						Motor_Set_Rotation_Speed(1,pwm_rpm[0]);
					break;
				case key2:
					Input_DoubleValue(&pwm_rpm[1],"PWM2");
					if (fabs(pwm_rpm[1]) <= RPM_Limit)
						Motor_Set_Rotation_Speed(2,pwm_rpm[1]);
					break;
				case key3:
					Input_DoubleValue(&pwm_rpm[2],"PWM3");
					if (fabs(pwm_rpm[2]) <= RPM_Limit)
						Motor_Set_Rotation_Speed(3,pwm_rpm[2]);
					break;
				case key4:
					Input_DoubleValue(&pwm_rpm[3],"PWM4");
					if (fabs(pwm_rpm[3]) <= RPM_Limit)
						Motor_Set_Rotation_Speed(4,pwm_rpm[3]);
					break;
				case key5:
					Input_DoubleValue(&temp,"Speed_X");
					Speed_X = temp;
					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
					break;
				case key6:
					Input_DoubleValue(&temp,"Speed_Y");
					Speed_Y = temp;
					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
					break;
				case key7:
					Input_DoubleValue(&temp,"Speed_Rotation");
					Speed_Rotation = temp;
					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
					break;
				case key8:
					SPEED_STOP;
					pwm_rpm[0] = pwm_rpm[1] = pwm_rpm[2] = pwm_rpm[3] = 0;
					temp = 0;
					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
					break;
				case key9:
					SPEED_STOP;
					pwm_rpm[0] = pwm_rpm[1] = pwm_rpm[2] = pwm_rpm[3] = 0;
					temp = 0;
					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
				
					en = !en;
					Motor_Set_Enabled(en);
					break;
				case keyback:
					SPEED_STOP;
					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
					return;
				case keyboardtab:
					KeyBoard_State = !KeyBoard_State;
					Show_Keyboard();
					break;
				default:
					break;
			}
			Show_Keyboard();
			POINT_COLOR=BLACK;
			for (i = 0; i < 4; ++i)
			{
				LCD_printf(0,6+36*i,300,24,24,"%d.PWM%d RPM = %lf",i+1,i+1,Motor_Get_Rotation_Speed(i+1));
			}
			LCD_printf(0,6+36*4,300,24,24,"5.Speed_X = %lf",Speed_X);
			LCD_printf(0,6+36*5,300,24,24,"6.Speed_Y = %lf",Speed_Y);
			LCD_printf(0,6+36*6,300,24,24,"7.Speed_Rot = %lf",Speed_Rotation);
			LCD_printf(0,6+36*7,300,24,24,"8.Speed_Stop");
			LCD_printf(0,6+36*8,300,24,24,"9.State:%s",en == 1 ? "Enable" : "Disable");
			LCD_printf(0,6+36*9,300,24,24,"10.Angle = %lf        ",GPS_List[0].angle);
			LCD_printf(0,6+36*10,300,24,24,"11.X = %lf        ",GPS_List[0].position.x);
			LCD_printf(0,6+36*11,300,24,24,"12.Y = %lf        ",GPS_List[0].position.y);
		}
		else
			delay_ms(1);
	}
}

void sys_Servo(void)
{
	u8 i, tp_last, key_value, is_key = 0;
	double pwm_duty[4] = {0};
	u16 touch_pos[4] = {0};
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	for (i = 0; i < 4; ++i)
	{
		LCD_printf(0,6+36*2*i,300,24,24,"%d.Servo%d loc = %u",i+1,i+1,set_loc[i]);
	}
	for (i = 0; i < 4; ++i)
	{
		LCD_DrawRectangle(0,6+36*(2*i+1)+12-2,300,6+36*(2*i+1)+12+2);
		LCD_DrawRectangle(touch_pos[i],6+36*(2*i+1),touch_pos[i]+20,6+36*(2*i+1)+24);
	}
	LCD_printf(0,6+36*8,300,24,24,"9.Set Duty");
	
	while (1)
	{
		for (i = 0; i < 4; ++i)
		{
			LCD_printf(0,6+36*2*i,300,24,24,"%d.Servo%d Duty = %u",i+1,i+1,Servo_Duty[i]);
		}
		for (i = 0; i < 4; ++i)
		{
			LCD_DrawRectangle(0,6+36*(2*i+1)+12-2,300,6+36*(2*i+1)+12+2);
			LCD_DrawRectangle(touch_pos[i],6+36*(2*i+1),touch_pos[i]+20,6+36*(2*i+1)+24);
		}
		
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
				case key1:
					Input_DoubleValue(&pwm_duty[0],"Servo1");
					if (pwm_duty[0] <= 400000)
						set_loc[0] = pwm_duty[0];
					break;
				case key2:
					if (tp_dev.x[0] < 300)
					{
						touch_pos[0] = tp_dev.x[0];
						pwm_duty[0] = tp_dev.x[0]*400000.0/300.0;
						if (pwm_duty[0] <= 400000)
							set_loc[0] = pwm_duty[0];
					}
					break;
				case key3:
					Input_DoubleValue(&pwm_duty[1],"Servo2");
					if (pwm_duty[1] <= 50)
						Servo_Duty[1] = pwm_duty[1];
					break;
				case key4:
					if (tp_dev.x[0] < 300)
					{
						touch_pos[1] = tp_dev.x[0];
						pwm_duty[1] = tp_dev.x[0]*(50.0-10.0)/300.0+10.0;
						if (pwm_duty[1] <= 50)
							Servo_Duty[1] = pwm_duty[1];
					}
					break;
				case key5:
					Input_DoubleValue(&pwm_duty[2],"Servo3");
					if (pwm_duty[2] <= 50)
						Servo_Duty[2] = pwm_duty[2];
					break;
				case key6:
					if (tp_dev.x[0] < 300)
					{
						touch_pos[2] = tp_dev.x[0];
						pwm_duty[2] = tp_dev.x[0]*(40.0-15.0)/300.0+15.0;
						if (pwm_duty[2] <= 50)
							Servo_Duty[2] = pwm_duty[2];
					}
					break;
				case key7:
					Input_DoubleValue(&pwm_duty[3],"Servo4");
					if (pwm_duty[3] <= 50)
						Servo_Duty[3] = pwm_duty[3];
					break;
				case key8:
					if (tp_dev.x[0] < 300)
					{
						touch_pos[3] = tp_dev.x[0];
						pwm_duty[3] = tp_dev.x[0]*(40.0-15.0)/300.0+15.0;
						if (pwm_duty[3] <= 50)
							Servo_Duty[3] = pwm_duty[3];
					}
					break;
				case key9:
					Servo_PWM_SetDuty();
					break;
				case keyback:
					return;
				case keyboardtab:
					KeyBoard_State = !KeyBoard_State;
					Show_Keyboard();
					break;
				default:
					break;
			}
			Show_Keyboard();
			POINT_COLOR=BLACK;
			for (i = 0; i < 4; ++i)
			{
				LCD_printf(0,6+36*2*i,300,24,24,"%d.Servo%d loc = %u",i+1,i+1,set_loc[i]);
			}
			for (i = 0; i < 4; ++i)
			{
				LCD_DrawRectangle(0,6+36*(2*i+1)+12-2,300,6+36*(2*i+1)+12+2);
				LCD_DrawRectangle(touch_pos[i],6+36*(2*i+1),touch_pos[i]+20,6+36*(2*i+1)+24);
			}
			LCD_printf(0,6+36*8,300,24,24,"9.Set Duty");
		}
		else
			delay_ms(1);
	}
}

void sys_QR_Code(void)
{
	u8 tp_last, key_value, is_key = 0;
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	
	while (1)
	{
		LCD_printf(0,6+36*0,300,24,24,"1.Send Command");
		LCD_printf(0,6+36*1,300,24,24,"2.Ans:%c %c %c   ",QR_Code_Res[0], QR_Code_Res[1], QR_Code_Res[2]);
		LCD_printf(0,6+36*2,300,24,24,"3.%02X %02X %02X %02X %02X  ",QR_Code_RxBuffer[0], QR_Code_RxBuffer[1], QR_Code_RxBuffer[2], QR_Code_RxBuffer[3], QR_Code_RxBuffer[4]);
		LCD_printf(0,6+36*3,300,24,24,"4.%02X %02X %02X %02X %02X %02X  ",QR_Code_RxBuffer[5], QR_Code_RxBuffer[6], QR_Code_RxBuffer[7], QR_Code_RxBuffer[8], QR_Code_RxBuffer[9], QR_Code_RxBuffer[10]);
		LCD_printf(0,6+36*4,300,24,24,"5.WIFI 1:%c %c %c",WIFI_Res_1[0], WIFI_Res_1[1], WIFI_Res_1[2]);
		LCD_printf(0,6+36*5,300,24,24,"6.WIFI 2:%c %c %c",WIFI_Res_2[0], WIFI_Res_2[1], WIFI_Res_2[2]);
		LCD_printf(0,6+36*6,300,24,24,"7.WIFI Rx:%c  %c  %c  %c  ",WIFI_RxBuffer[0], WIFI_RxBuffer[1], WIFI_RxBuffer[2], WIFI_RxBuffer[3]);
		LCD_printf(0,6+36*7,300,24,24,"8.WIFI Rx:%c  %c  %c  ",WIFI_RxBuffer[4], WIFI_RxBuffer[5], WIFI_RxBuffer[6], WIFI_RxBuffer[7]);
		
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
				case key1:
				#ifdef BSP_USING_USART3
					if (QR_Code_RX_Finish)
					{
						DMA_SetCurrDataCounter(USART3_DMA_TX_STREAM, QR_Code_TxBufferSize);
						DMA_Cmd(USART3_DMA_TX_STREAM, ENABLE);
						QR_Code_RX_Finish = 0;
					}
				#endif
					break;
				case keyback:
					return;
				case keyboardtab:
					KeyBoard_State = !KeyBoard_State;
					Show_Keyboard();
					break;
			}
		}
		else
			delay_ms(1);
	}
}

void sys_Camera(void)
{
	u8 tp_last, key_value, is_key = 0;
	int camera_mode = 0;
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	
	while (1)
	{
		LCD_printf(0,6+36*0,300,24,24,"1.Camera Enable(Be sure they are OK)");
		LCD_printf(0,6+36*1,300,24,24,"2.Camera Disable");
		LCD_printf(0,6+36*2,300,24,24,"3.Mode:%u",Camera_Mode);
		LCD_printf(0,6+36*3,300,24,24,"4.Rx:%u %u %u %u",Camera_RxBuffer[0],Camera_RxBuffer[1],Camera_RxBuffer[2],Camera_RxBuffer[3]);
		LCD_printf(0,6+36*4,300,24,24,"5.Hash:r%u g%u b%u",Color_Hash_Table[0],Color_Hash_Table[1],Color_Hash_Table[2]);
		LCD_printf(0,6+36*5,300,24,24,"6.Color Res:%u %u %u",Color_Res[0],Color_Res[1],Color_Res[2]);
		LCD_printf(0,6+36*6,300,24,24,"7.Power off");
		
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
				case key1:
					Camera_Set_Mode(8);
					break;
				case key2:
					Camera_Set_Mode(0);
					break;
				case key3:
					Input_IntValue(&camera_mode, "Mode");
					Camera_Set_Mode(camera_mode);
					break;
				case key7:
					Camera_Set_Mode(7);
					break;
				case keyback:
					return;
				case keyboardtab:
					KeyBoard_State = !KeyBoard_State;
					Show_Keyboard();
					LCD_printf(0,6+36*0,300,24,24,"1.Camera Enable(Be sure they are OK)");
					LCD_printf(0,6+36*1,300,24,24,"2.Camera Disable");
					LCD_printf(0,6+36*2,300,24,24,"3.Mode:%u",Camera_Mode);
					LCD_printf(0,6+36*3,300,24,24,"4.Rx:%u %u %u %u",Camera_RxBuffer[0],Camera_RxBuffer[1],Camera_RxBuffer[2],Camera_RxBuffer[3]);
					LCD_printf(0,6+36*4,300,24,24,"5.Hash:r%u g%u b%u",Color_Hash_Table[0],Color_Hash_Table[1],Color_Hash_Table[2]);
					LCD_printf(0,6+36*5,300,24,24,"6.Color Res:%u %u %u",Color_Res[0],Color_Res[1],Color_Res[2]);
					LCD_printf(0,6+36*6,300,24,24,"7.Power off");
					break;
				default:
					break;
			}
		}
		else
			delay_ms(1);
	}
}

void sys_PanTilt(void)
{
	u8 tp_last, key_value, is_key = 0;
	int64_t angle = 0;
	int32_t length = 0;

	float DP=1.0, DI=0.003, DD=0.01, SP=30.0, SI=0.0, SD=0.0;
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	
	set_loc[1] = 0;
	
	LCD_printf(0,6+36*0,300,24,24,"1.Set Angle=%lld",angle);
	LCD_printf(0,6+36*1,300,24,24,"2.SetPanT Mode=%d",Mode[1]);
	LCD_printf(0,6+36*2,300,24,24,"3.DP:%f",DP);
	LCD_printf(0,6+36*3,300,24,24,"4.DI:%f",DI);
	LCD_printf(0,6+36*4,300,24,24,"5.DD:%f",DD);
	LCD_printf(0,6+36*5,300,24,24,"6.SP:%f",SP);
	LCD_printf(0,6+36*6,300,24,24,"7.SI:%f",SI);
	LCD_printf(0,6+36*7,300,24,24,"8.SD:%f",SD);
	LCD_printf(0,6+36*8,300,24,24,"9.GO",Mode[1]);
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
				case key1:
					Input_Int64Value(&angle,"Angle");
					set_loc[1] = angle;
					set_spd[1] = angle;
					break;
				case key2:
					set_loc[1] = 0;
					set_spd[1] = 0;
					if(Mode[1] == 1)
						Mode[1] = 0;
					else
						Mode[1] = 1;
					break;
				case key3:
					Input_FloatValue(&DP,"DP");
					break;
				case key4:
					Input_FloatValue(&DI,"DI");
					break;
				case key5:
					Input_FloatValue(&DD,"DD");
					break;
				case key6:
					Input_FloatValue(&SP,"SP");
					break;
				case key7:
					Input_FloatValue(&SI,"SI");
					break;
				case key8:
					Input_FloatValue(&SD,"SD");
					break;
				case keyback:
					set_loc[1] = 0;
					set_spd[1] = 0;
					return;
				case key9:
					Input_IntValue(&length,"length");
					set_loc[0] = length;
					PID_struct_init(&pid_spd[1], POSITION_PID, 30000, 30000,
						 		SP,	SI,	SD	);  //4 motos angular rate closeloop.  0.80f,	0.03f,	0.0015f	(超调)
					PID_struct_init(&pid_loc[1], DELTA_PID, 200, 200,
								DP,	DI,	DD	);  //0.80f,	0.003f,	0.000f	);  //4 motos angular location closeloop.}
					break;
				default:
					break;
			}
			LCD_printf(0,6+36*0,300,24,24,"1.Set Angle=%lld",angle);
			LCD_printf(0,6+36*1,300,24,24,"2.SetPanT Mode=%d",Mode[1]);
			LCD_printf(0,6+36*2,300,24,24,"3.DP:%f",DP);
			LCD_printf(0,6+36*3,300,24,24,"4.DI:%f",DI);
			LCD_printf(0,6+36*4,300,24,24,"5.DD:%f",DD);
			LCD_printf(0,6+36*5,300,24,24,"6.SP:%f",SP);
			LCD_printf(0,6+36*6,300,24,24,"7.SI:%f",SI);
			LCD_printf(0,6+36*7,300,24,24,"8.SD:%f",SD);
			LCD_printf(0,6+36*8,300,24,24,"9.GO");
		}
		else
			delay_ms(1);
	}
}

void sys_Measure(void)
{
	u8 is_key = 0;
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	
	Motor_Set_Enabled(0);
	
	PID_struct_init(&pid_spd[0], DELTA_PID, 8000, 16384,
								0.0f,	0.0f,	0.0f	);  //4 motos angular rate closeloop.  0.80f,	0.03f,	0.0015f	(超调)
	PID_struct_init(&pid_loc[0], DELTA_PID, 9600, 9600,
								0.0f,	0.0f,	0.0f	);  //4 motos angular location closeloop.}
	PID_struct_init(&pid_spd[1], DELTA_PID, 30000, 30000,
								0.0f,	0.0f,	0.0f	);  //4 motos angular rate closeloop.  0.80f,	0.03f,	0.0015f	(超调)
	PID_struct_init(&pid_loc[1], DELTA_PID, 50, 50,
								0.0f,	0.0f,	0.0f	);  //0.80f,	0.003f,	0.000f	);  //4 motos angular location closeloop.}

	while(1)
	{
		LCD_printf(0,6+36*0,300,24,24,"1.loc[0]=lld%		",moto_chassis[0].total_angle);
		LCD_printf(0,6+36*1,300,24,24,"2.loc[1]=lld%		",moto_chassis[1].total_angle);
		LCD_printf(0,6+36*2,300,24,24,"Angle = %lf        ",GPS_List[0].angle);
		LCD_printf(0,6+36*3,300,24,24,"X = %lf        ",GPS_List[0].position.x);
		LCD_printf(0,6+36*4,300,24,24,"Y = %lf        ",GPS_List[0].position.y);
		
		is_key = keyScan(MAINMENU);
		
		switch(keyValue)
		{
			case keyback:
				Motor_Set_Enabled(0);
				
				PID_Init();
				return;
			default:
				break;
		}
			
	}
}
