#include "all.h"

void route_Line(void)
{
	u8 tp_last, key_value, is_key = 0;
	u8 goline = 0;
	double temp;
	struct Line_Point aim_point = {{3000, 0}, pi/2, 300, 800, 300, 1, 2};
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"1.aim_point_x = %.6lf", aim_point.aim_position.x);
	LCD_printf(0,6+36*1,300,24,24,"2.aim_point_y = %.6lf", aim_point.aim_position.y);
	LCD_printf(0,6+36*2,300,24,24,"3.aim_angle/deg = %.6lf",aim_point.aim_radian*RAD2DEG);
	LCD_printf(0,6+36*3,300,24,24,"4.speed_sta = %.6lf",aim_point.speed_sta);
	LCD_printf(0,6+36*4,300,24,24,"5.speed_max = %.6lf",aim_point.speed_max);
	LCD_printf(0,6+36*5,300,24,24,"6.speed_end = %.6lf",aim_point.speed_end);
	LCD_printf(0,6+36*6,300,24,24,"7.GPS Clear");
	LCD_printf(0,6+36*7,300,24,24,"8.Set line and go");
	
	while (!goline)
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
					Input_DoubleValue(&temp,"aim_point_x");
					aim_point.aim_position.x = temp;
					break;
				case key2:
					Input_DoubleValue(&temp,"aim_point_y");
					aim_point.aim_position.y = temp;
					break;
				case key3:
					Input_DoubleValue(&temp,"aim_angle");
					while (temp > 180)
						temp -= 180;
					while (temp < -180)
						temp += 180;
					aim_point.aim_radian = temp * DEG2RAD;
					break;
				case key4:
					Input_DoubleValue(&temp,"speed_sta");
					aim_point.speed_sta = temp;
					break;
				case key5:
					Input_DoubleValue(&temp,"speed_max");
					aim_point.speed_max = temp;
					break;
				case key6:
					Input_DoubleValue(&temp,"speed_end");
					aim_point.speed_end = temp;
					break;
				case key7:
					GPS_Clear();
					break;
				case key8:
					SetLine(&aim_point);
					goline = 1;
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
			LCD_printf(0,6+36*0,300,24,24,"1.aim_point_x = %.6lf", aim_point.aim_position.x);
			LCD_printf(0,6+36*1,300,24,24,"2.aim_point_y = %.6lf", aim_point.aim_position.y);
			LCD_printf(0,6+36*2,300,24,24,"3.aim_angle/deg = %.6lf",aim_point.aim_radian*RAD2DEG);
			LCD_printf(0,6+36*3,300,24,24,"4.speed_sta = %.6lf",aim_point.speed_sta);
			LCD_printf(0,6+36*4,300,24,24,"5.speed_max = %.6lf",aim_point.speed_max);
			LCD_printf(0,6+36*5,300,24,24,"6.speed_end = %.6lf",aim_point.speed_end);
			LCD_printf(0,6+36*6,300,24,24,"7.GPS Clear");
			LCD_printf(0,6+36*7,300,24,24,"8.Set line and go");
		}
		else
			delay_ms(1);
	}
	
	LCD_Clear(WHITE);
	LCD_printf(0,6+36*0,300,24,24,"GoLine");
	while (!(GetLength(&(GPS_List[0].position), &aim_point.aim_position) < 20.0 && fabs(GPS_List[0].radian - aim_point.aim_radian) < 2.0*DEG2RAD))
	{
		GoLine();
		
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
					SPEED_STOP;
					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
					return;
				default:
					break;
			}
		}
	}
	
	SPEED_STOP;
	SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
}

void route_Keep(void)
{
	u8 tp_last, key_value, is_key = 0;
	u8 keep = 0;
	double aim_point_x = 1000, aim_point_y = 0, aim_angle = 90, aim_radian = pi/2;
	double speed_max = 1000;		//mm/s
	struct Point end_point;
	
	end_point.x = aim_point_x;
	end_point.y = aim_point_y;
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"1.aim_point_x = %.6lf", aim_point_x);
	LCD_printf(0,6+36*1,300,24,24,"2.aim_point_y = %.6lf", aim_point_y);
	LCD_printf(0,6+36*2,300,24,24,"3.aim_angle/deg = %.6lf",aim_angle);
	LCD_printf(0,6+36*3,300,24,24,"4.speed_max = %.6lf",speed_max);
	LCD_printf(0,6+36*4,300,24,24,"5.GPS Clear");
	LCD_printf(0,6+36*5,300,24,24,"6.Set Keep and go");
	
	while (!keep)
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
					Input_DoubleValue(&aim_point_x,"aim_point_x");
					end_point.x = aim_point_x;
					break;
				case key2:
					Input_DoubleValue(&aim_point_y,"aim_point_y");
					end_point.y = aim_point_y;
					break;
				case key3:
					Input_DoubleValue(&aim_angle,"aim_angle");
					while (aim_angle > 180)
						aim_angle -= 180;
					while (aim_angle < -180)
						aim_angle += 180;
					aim_radian = aim_angle * DEG2RAD;
					break;
				case key4:
					Input_DoubleValue(&speed_max,"speed_max");
					break;
				case key5:
					GPS_Clear();
					break;
				case key6:
					SetKeep(&end_point, aim_radian, speed_max);
					keep = 1;
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
			LCD_printf(0,6+36*0,300,24,24,"1.aim_point_x = %.6lf", aim_point_x);
			LCD_printf(0,6+36*1,300,24,24,"2.aim_point_y = %.6lf", aim_point_y);
			LCD_printf(0,6+36*2,300,24,24,"3.aim_angle/deg = %.6lf",aim_angle);
			LCD_printf(0,6+36*3,300,24,24,"4.speed_max = %.6lf",speed_max);
			LCD_printf(0,6+36*4,300,24,24,"5.GPS Clear");
			LCD_printf(0,6+36*5,300,24,24,"6.Set Keep and go");
		}
		else
			delay_ms(1);
	}
	
	Show_Keyboard();
	
	while (!(GetLength(&(GPS_List[0].position), &end_point) < 20.0 && fabs(GPS_List[0].angle - aim_angle) < 1))
	{
		Keep(&Pid_List[2],&Pid_List[3]);
		
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
					SPEED_STOP;
					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
					return;
				default:
					break;
			}
		}
	}
	SPEED_STOP;
	SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
}

void route_Handle(void)
{
	u8 tp_last, key_value, is_key = 0;
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"%02X, %02X, %02X, %02X, %02X, %02X  ", Handle_RxBuffer[0],Handle_RxBuffer[1],Handle_RxBuffer[2],Handle_RxBuffer[3],Handle_RxBuffer[4],Handle_RxBuffer[5]);
	LCD_printf(0,6+36*1,300,24,24,"%02X, %02X, %02X, %02X, %02X, %02X  ", Handle_RxBuffer[6],Handle_RxBuffer[7],Handle_RxBuffer[8],Handle_RxBuffer[9],Handle_RxBuffer[10],Handle_RxBuffer[11]);
	LCD_printf(0,6+36*2,300,24,24,"Key 0x%02X    ", Handle_Key_Value);
	
	while (1)
	{
		LCD_printf(0,6+36*0,300,24,24,"%02X, %02X, %02X, %02X, %02X, %02X  ", Handle_RxBuffer[0],Handle_RxBuffer[1],Handle_RxBuffer[2],Handle_RxBuffer[3],Handle_RxBuffer[4],Handle_RxBuffer[5]);
		LCD_printf(0,6+36*1,300,24,24,"%02X, %02X, %02X, %02X, %02X, %02X  ", Handle_RxBuffer[6],Handle_RxBuffer[7],Handle_RxBuffer[8],Handle_RxBuffer[9],Handle_RxBuffer[10],Handle_RxBuffer[11]);
		LCD_printf(0,6+36*2,300,24,24,"Key 0x%02X    ", Handle_Key_Value);
		
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
				default:
					break;
			}
			Show_Keyboard();
			LCD_printf(0,6+36*0,300,24,24,"%02X, %02X, %02X, %02X, %02X, %02X  ", Handle_RxBuffer[0],Handle_RxBuffer[1],Handle_RxBuffer[2],Handle_RxBuffer[3],Handle_RxBuffer[4],Handle_RxBuffer[5]);
			LCD_printf(0,6+36*1,300,24,24,"%02X, %02X, %02X, %02X, %02X, %02X  ", Handle_RxBuffer[6],Handle_RxBuffer[7],Handle_RxBuffer[8],Handle_RxBuffer[9],Handle_RxBuffer[10],Handle_RxBuffer[11]);
			LCD_printf(0,6+36*2,300,24,24,"Key 0x%02X    ", Handle_Key_Value);
		}
		else
			delay_ms(1);
	}
}
