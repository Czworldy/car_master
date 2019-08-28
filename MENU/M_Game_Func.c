#include "all.h"

void Return_Any_Point(struct Line_Point *aim_line_point, double distance_err, double angle_err,u8 goLine_timeout)
{
	u8 is_key = 0;
	
	//LCD_Clear(WHITE);
	SetLine(aim_line_point);
	TIM12_OVERFLOW_CNT = 0;
	TIM12->CNT = 0;
	TIM_Cmd(TIM12, ENABLE);
	
	while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < distance_err && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < angle_err * DEG2RAD) && TIM12_OVERFLOW_CNT < goLine_timeout)
	{
		GoLine();
		
//		LCD_printf(0,6+36*0,300,24,24,"1.Angle =%lf     	   ",GPS_List[0].angle);
//		LCD_printf(0,6+36*1,300,24,24,"2.X =%lf     	   ",GPS_List[0].position.x);
//		LCD_printf(0,6+36*2,300,24,24,"3.Y =%lf 	       ",GPS_List[0].position.y);
//		
//		LCD_printf(0,6+36*3,300,24,24,"1.Angle =%lf        `",Aim_Line_Point.aim_radian);
//		LCD_printf(0,6+36*4,300,24,24,"2.Aim X =%lf        `",Aim_Line_Point.aim_position.x);
//		LCD_printf(0,6+36*5,300,24,24,"3.Aim Y =%lf        `",Aim_Line_Point.aim_position.y);
		
		is_key = keyScan(1);
		if (is_key)
		{
			is_key = 0;
			switch(keyValue)
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
	
	TIM_Cmd(TIM12,DISABLE);
}

struct Line_Point Corner_Point[4] = {
	{{0, 750}, 0, 40, 300, 40, -1, 2},
	{{1350, 750}, 0, 40, 300, 40, -1, 2},
	{{1350, -750}, 0, 40, 300, 40, -1, 2},
	{{0, -750}, 0, 40, 300, 40, -1, 2},
};
void CCD_Adjust(struct CCD_Line ccd_line, uint8_t ccdx, uint8_t ccdy)
{
	struct Line_Point aim_line_point;
	u8 is_key = 0;
	u8 ccd_adjustment_sign;
	
	TSL1401_SetEnabled(1);
	
	delay_ms(500);
	while (!TSL1401_Cal_Ready);
	TSL1401_Measure(!TSL1401_Is_Find_ADC_Threshold);
	
	while (1)
	{
		LCD_printf(0,6+36*1,300,24,24,"Press any key to start 1");
		LCD_printf(0,6+36*2,300,24,24,"Edge Type:%u %u %u %u",TSL1401_State[0].Line_Edge_Type,TSL1401_State[1].Line_Edge_Type,TSL1401_State[2].Line_Edge_Type,TSL1401_State[3].Line_Edge_Type);
		LCD_printf(0,6+36*3,300,24,24,"Mpos:%u %u %u %u",TSL1401_State[0].Line_Edge_Median_Pos,TSL1401_State[1].Line_Edge_Median_Pos,TSL1401_State[2].Line_Edge_Median_Pos,TSL1401_State[3].Line_Edge_Median_Pos);
		
		is_key = keyScan(1);

		if (is_key)
		{
			is_key = 0;
			if (keyValue == keyback)
			{
				TSL1401_SetEnabled(0);
				return;
			}
			else
				break;
		}
		else
			delay_ms(1);
	}
		
	ccd_adjustment_sign = 0;
	aim_line_point = CCD_Adjustment;
	aim_line_point.aim_position.x = GPS_List[0].position.x; 
	aim_line_point.aim_position.y = GPS_List[0].position.y;
	SetLine(&aim_line_point);
	
	switch (TSL1401_State[ccdx].Line_Edge_Type)
	{
		case 0:
			ccd_adjustment_sign &= ~(2 << 2);
			ccd_adjustment_sign |= (0 << 2);
			break;
		case 1:
			ccd_adjustment_sign &= ~(2 << 2);
			ccd_adjustment_sign |= (1 << 2);
			aim_line_point.aim_position.y = GPS_List[0].position.y + Product_Point_CCD_Line[1].Line_Move_Offset[1].y;
			SetLine(&aim_line_point);
			break;
		case 2:
			ccd_adjustment_sign &= ~(2 << 2);
			ccd_adjustment_sign |= (2 << 2);
			aim_line_point.aim_position.x = GPS_List[0].position.x + Product_Point_CCD_Line[1].Line_Move_Offset[1].x;
			SetLine(&aim_line_point);
			break;
		case 4:
			break;
	}
	switch (TSL1401_State[ccdy].Line_Edge_Type)
	{
		case 0:
			ccd_adjustment_sign &= ~(2 << 4);
			ccd_adjustment_sign |= (0 << 4);
			break;
		case 1:
			ccd_adjustment_sign &= ~(2 << 4);
			ccd_adjustment_sign |= (1 << 4);
			if ((ccd_adjustment_sign & 2) != 2)
			{
				aim_line_point.aim_position.x = GPS_List[0].position.x + Product_Point_CCD_Line[1].Line_Move_Offset[2].x;
				SetLine(&aim_line_point);
			}
			break; 
		case 2:
			ccd_adjustment_sign &= ~(2 << 4);
			ccd_adjustment_sign |= (1 << 4);
			if ((ccd_adjustment_sign & 2) != 1)
			{
				aim_line_point.aim_position.y = GPS_List[0].position.y + Product_Point_CCD_Line[1].Line_Move_Offset[2].y;
				SetLine(&aim_line_point);
			}
			break;
		case 4:
			break;
	}

	if (ccd_adjustment_sign)
	{
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
		{
			GoLine();
					
			LCD_printf(0,6+36*0,300,24,24,"1.Angle = %lf        ",GPS_List[0].angle);
			LCD_printf(0,6+36*1,300,24,24,"2.X = %lf        ",GPS_List[0].position.x);
			LCD_printf(0,6+36*2,300,24,24,"3.Y = %lf        ",GPS_List[0].position.y);
			
			LCD_printf(0,6+36*3,300,24,24,"1.Angle = %lf        ",Aim_Line_Point.aim_radian);
			LCD_printf(0,6+36*4,300,24,24,"2.Aim X = %lf        ",Aim_Line_Point.aim_position.x);
			LCD_printf(0,6+36*5,300,24,24,"3.Aim Y = %lf        ",Aim_Line_Point.aim_position.y);
			
			is_key = keyScan(1);
			if (is_key)
			{
				is_key = 0;
				switch(keyValue)
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
		
		delay_ms(500);
		while (!TSL1401_Cal_Ready);
		TSL1401_Measure(!TSL1401_Is_Find_ADC_Threshold);
	}
		
	while (1)
	{
		LCD_printf(0,6+36*1,300,24,24,"Press any key to start 2");
		LCD_printf(0,6+36*2,300,24,24,"Edge Type:%u %u %u %u",TSL1401_State[0].Line_Edge_Type,TSL1401_State[1].Line_Edge_Type,TSL1401_State[2].Line_Edge_Type,TSL1401_State[3].Line_Edge_Type);
		LCD_printf(0,6+36*3,300,24,24,"Mpos:%u %u %u %u",TSL1401_State[0].Line_Edge_Median_Pos,TSL1401_State[1].Line_Edge_Median_Pos,TSL1401_State[2].Line_Edge_Median_Pos,TSL1401_State[3].Line_Edge_Median_Pos);
		
		is_key = keyScan(1);
		if (is_key)
		{
			is_key = 0;
			if (keyValue == keyback)
			{
				TSL1401_SetEnabled(0);
				return;
			}
			else
				break;
		}
		else
			delay_ms(1);
	}
	TSL1401_SetEnabled(0);
	
	aim_line_point = CCD_Adjustment;
	aim_line_point.aim_position.x = GPS_List[0].position.x + (ccd_line.Line_Edge_Median_Pos[ccdx] - TSL1401_State[ccdx].Line_Edge_Median_Pos) * TSL1401_State[ccdx].Pixel_To_Distance;
	aim_line_point.aim_position.y = GPS_List[0].position.y + (ccd_line.Line_Edge_Median_Pos[ccdy] - TSL1401_State[ccdy].Line_Edge_Median_Pos) * TSL1401_State[ccdy].Pixel_To_Distance;
	
	Return_Any_Point(&aim_line_point,10.0,1.0,3);
}

void CCD_Adjust_to_GPS(struct CCD_Line ccd_line, uint8_t ccdx, uint8_t ccdy, struct Point std_point)
{
	struct Line_Point aim_line_point;
	u8 is_key = 0;
	u8 ccd_adjustment_sign;
	
	//LCD_Clear(WHITE);
	
	TSL1401_SetEnabled(1);
	
	delay_ms(500);
	while (!TSL1401_Cal_Ready);
	TSL1401_Measure(!TSL1401_Is_Find_ADC_Threshold);
	
	while (1)
	{
		LCD_printf(0,6+36*1,300,24,24,"Press any key to start 1");
		LCD_printf(0,6+36*2,300,24,24,"Edge Type:%u %u %u %u",TSL1401_State[0].Line_Edge_Type,TSL1401_State[1].Line_Edge_Type,TSL1401_State[2].Line_Edge_Type,TSL1401_State[3].Line_Edge_Type);
		LCD_printf(0,6+36*3,300,24,24,"Mpos:%u %u %u %u",TSL1401_State[0].Line_Edge_Median_Pos,TSL1401_State[1].Line_Edge_Median_Pos,TSL1401_State[2].Line_Edge_Median_Pos,TSL1401_State[3].Line_Edge_Median_Pos);
		
		//is_key = keyScan(1);

		is_key = 1;
		
		if (is_key)
		{
			is_key = 0;
			
			if (keyValue == keyback)
			{
				TSL1401_SetEnabled(0);
				return;
			}
			else
				break;
		}
		else
			delay_ms(1);
	}
		
	ccd_adjustment_sign = 0;
	aim_line_point = CCD_Adjustment;
	aim_line_point.aim_position.x = GPS_List[0].position.x; 
	aim_line_point.aim_position.y = GPS_List[0].position.y;
	SetLine(&aim_line_point);
	
	switch (TSL1401_State[ccdx].Line_Edge_Type)
	{
		case 0:
			ccd_adjustment_sign &= ~(2 << 2);
			ccd_adjustment_sign |= (0 << 2);
			break;
		case 1:
			ccd_adjustment_sign &= ~(2 << 2);
			ccd_adjustment_sign |= (1 << 2);
			aim_line_point.aim_position.y = GPS_List[0].position.y + ccd_line.Line_Move_Offset[1].y;
			SetLine(&aim_line_point);
			break;
		case 2:
			ccd_adjustment_sign &= ~(2 << 2);
			ccd_adjustment_sign |= (2 << 2);
			aim_line_point.aim_position.x = GPS_List[0].position.x + ccd_line.Line_Move_Offset[1].x;
			SetLine(&aim_line_point);
			break;
		case 4:
			break;
	}
	switch (TSL1401_State[ccdy].Line_Edge_Type)
	{
		case 0:
			ccd_adjustment_sign &= ~(2 << 4);
			ccd_adjustment_sign |= (0 << 4);
			break;
		case 1:
			ccd_adjustment_sign &= ~(2 << 4);
			ccd_adjustment_sign |= (1 << 4);
			if ((ccd_adjustment_sign & 2) != 2)
			{
				aim_line_point.aim_position.x = GPS_List[0].position.x + ccd_line.Line_Move_Offset[2].x;
				SetLine(&aim_line_point);
			}
			break; 
		case 2:
			ccd_adjustment_sign &= ~(2 << 4);
			ccd_adjustment_sign |= (1 << 4);
			if ((ccd_adjustment_sign & 2) != 1)
			{
				aim_line_point.aim_position.y = GPS_List[0].position.y + ccd_line.Line_Move_Offset[2].y;
				SetLine(&aim_line_point);
			}
			break;
		case 4:
			break;
	}

	if (ccd_adjustment_sign)
	{
		Return_Any_Point(&aim_line_point,10.0,1.0,3);
//		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
//		{
//			GoLine();
//					
//			LCD_printf(0,6+36*0,300,24,24,"1.Angle = %lf        ",GPS_List[0].angle);
//			LCD_printf(0,6+36*1,300,24,24,"2.X = %lf        ",GPS_List[0].position.x);
//			LCD_printf(0,6+36*2,300,24,24,"3.Y = %lf        ",GPS_List[0].position.y);
//			
//			LCD_printf(0,6+36*3,300,24,24,"1.Angle = %lf        ",Aim_Line_Point.aim_radian);
//			LCD_printf(0,6+36*4,300,24,24,"2.Aim X = %lf        ",Aim_Line_Point.aim_position.x);
//			LCD_printf(0,6+36*5,300,24,24,"3.Aim Y = %lf        ",Aim_Line_Point.aim_position.y);
//			
//			is_key = keyScan(1);
//			if (is_key)
//			{
//				is_key = 0;
//				switch(keyValue)
//				{
//					case keyback:
//						SPEED_STOP;
//						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
//						return;	
//					default:
//						break;
//				}
//			}
//		}
//		SPEED_STOP;
//		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		delay_ms(500);
		while (!TSL1401_Cal_Ready);
		TSL1401_Measure(!TSL1401_Is_Find_ADC_Threshold);
	}
		
	while (1)
	{
		LCD_printf(0,6+36*1,300,24,24,"Press any key to start 2");
		LCD_printf(0,6+36*2,300,24,24,"Edge Type:%u %u %u %u",TSL1401_State[0].Line_Edge_Type,TSL1401_State[1].Line_Edge_Type,TSL1401_State[2].Line_Edge_Type,TSL1401_State[3].Line_Edge_Type);
		LCD_printf(0,6+36*3,300,24,24,"Mpos:%u %u %u %u",TSL1401_State[0].Line_Edge_Median_Pos,TSL1401_State[1].Line_Edge_Median_Pos,TSL1401_State[2].Line_Edge_Median_Pos,TSL1401_State[3].Line_Edge_Median_Pos);
		
		//is_key = keyScan(1);
		
		is_key = 1;
		
		if (is_key)
		{
			is_key = 0;
			if (keyValue == keyback)
			{
				TSL1401_SetEnabled(0);
				return;
			}
			else
				break;
		}
		else
			delay_ms(1);
	}
	TSL1401_SetEnabled(0);
	if((TSL1401_State[ccdx].Line_Edge_Type != 0) || (TSL1401_State[ccdy].Line_Edge_Type != 0))
	{	
		LCD_printf(0,6+36*8,300,24,24,"CCD_Failed %u %u",TSL1401_State[ccdx].Line_Edge_Type,TSL1401_State[ccdy].Line_Edge_Type);
		return;
	}			
	aim_line_point = CCD_Adjustment;
	aim_line_point.aim_position.x = GPS_List[0].position.x + (ccd_line.Line_Edge_Median_Pos[ccdx] - TSL1401_State[ccdx].Line_Edge_Median_Pos) * TSL1401_State[ccdx].Pixel_To_Distance;
	aim_line_point.aim_position.y = GPS_List[0].position.y + (ccd_line.Line_Edge_Median_Pos[ccdy] - TSL1401_State[ccdy].Line_Edge_Median_Pos) * TSL1401_State[ccdy].Pixel_To_Distance;
	
	Return_Any_Point(&aim_line_point,5.0,0.7,3);
	
	GPS_Init(std_point.x, std_point.y);
//	LCD_printf(0,6+36*8,300,24,24,"				");
	delay_ms(200);
}

void CCD_Adjust_to_GPS_X(struct CCD_Line ccd_line, uint8_t ccdx, struct Point std_start_pos)
{
	struct Line_Point aim_line_point;
	u8 is_key = 0;
	u8 ccd_adjustment_sign = 0;
	
	
	ccd_adjustment_sign = 0;
	aim_line_point = CCD_Adjustment;

	TSL1401_SetEnabled(1);
	
	delay_ms(500);
	while (!TSL1401_Cal_Ready);
	TSL1401_Measure(!TSL1401_Is_Find_ADC_Threshold);
	LCD_Clear(WHITE);
	while(1)
	{
		LCD_printf(0,6+36*1,300,24,24,"Press any key to start 1");
		LCD_printf(0,6+36*2,300,24,24,"Edge Type:%u			",TSL1401_State[ccdx].Line_Edge_Type);
		LCD_printf(0,6+36*3,300,24,24,"Mpos:%u			",TSL1401_State[ccdx].Line_Edge_Median_Pos);
		LCD_printf(0,6+36*4,300,24,24,"Left pos:%u			",TSL1401_State[ccdx].Line_Edge_Left_Pos);
		LCD_printf(0,6+36*5,300,24,24,"Right pos:%u			",TSL1401_State[ccdx].Line_Edge_Right_Pos);
		
		//is_key = keyScan(1);
		
		is_key = 1;
		if (is_key)
		{
			is_key = 0;
			if (keyValue == keyback)
			{
				TSL1401_SetEnabled(0);
				return;
			}
			else
				break;
		}
		else
			delay_ms(1);
	}
	
	switch (TSL1401_State[ccdx].Line_Edge_Type)
	{
		case 0:
			ccd_adjustment_sign &= ~(2 << 2);
			ccd_adjustment_sign |= (0 << 2);
			break;
		case 1:
			ccd_adjustment_sign &= ~(2 << 2);
			ccd_adjustment_sign |= (1 << 2);
			aim_line_point.aim_position.y = GPS_List[0].position.y + ccd_line.Line_Move_Offset[1].y;
			SetLine(&aim_line_point);
			break;
		case 2:
			ccd_adjustment_sign &= ~(2 << 2);
			ccd_adjustment_sign |= (2 << 2);
			aim_line_point.aim_position.x = GPS_List[0].position.x + ccd_line.Line_Move_Offset[1].x;
			SetLine(&aim_line_point);
			break;
		case 4:
			ccd_adjustment_sign &= ~(2 << 2);
			ccd_adjustment_sign |= (2 << 2);
			aim_line_point.aim_position.y = GPS_List[0].position.y + ccd_line.Line_Move_Offset[2].y;
			break;
	}
	if (ccd_adjustment_sign)
	{
		Return_Any_Point(&aim_line_point,5.0,1.0,3);
		
		delay_ms(500);
		while (!TSL1401_Cal_Ready);
		TSL1401_Measure(!TSL1401_Is_Find_ADC_Threshold);
	}
	
	while(1)
	{
		LCD_printf(0,6+36*1,300,24,24,"Press any key to start 2");
		LCD_printf(0,6+36*2,300,24,24,"Edge Type:%u			",TSL1401_State[ccdx].Line_Edge_Type);
		LCD_printf(0,6+36*3,300,24,24,"Mpos:%u			",TSL1401_State[ccdx].Line_Edge_Median_Pos);
		LCD_printf(0,6+36*4,300,24,24,"Left pos:%u			",TSL1401_State[ccdx].Line_Edge_Left_Pos);
		LCD_printf(0,6+36*5,300,24,24,"Right pos:%u			",TSL1401_State[ccdx].Line_Edge_Right_Pos);
		
		//is_key = keyScan(1);
		is_key = 1;
		if (is_key)
		{
			is_key = 0;
			if (keyValue == keyback)
			{
				TSL1401_SetEnabled(0);
				return;
			}
			else
				break;
		}
		else
			delay_ms(1);
	}
	TSL1401_SetEnabled(0);
	if(TSL1401_State[ccdx].Line_Edge_Type != 0)
	{	
		LCD_printf(0,6+36*7,300,24,24,"CCD_Failed");
		return;
	}			
	aim_line_point = CCD_Adjustment;
	aim_line_point.aim_position.x = GPS_List[0].position.x + (ccd_line.Line_Edge_Median_Pos[ccdx] - TSL1401_State[ccdx].Line_Edge_Median_Pos) * TSL1401_State[ccdx].Pixel_To_Distance;
	aim_line_point.aim_position.y = GPS_List[0].position.y;//+ (ccd_line.Line_Edge_Median_Pos[ccdy] - TSL1401_State[ccdy].Line_Edge_Median_Pos) * TSL1401_State[ccdy].Pixel_To_Distance;
	
	Return_Any_Point(&aim_line_point,5.0,1.0,3);
	
	delay_ms(50);
	GPS_Init(std_start_pos.x,GPS_List[0].position.y);
	
	delay_ms(200);
	
//	aim_line_point.aim_position = std_start_pos;
//	
//	Return_Any_Point(&aim_line_point,10.0,1.0);
}

void CCD_Adjust_to_GPS_Y(struct CCD_Line ccd_line, uint8_t ccdy, struct Point std_start_pos)
{
	struct Line_Point aim_line_point;
	u8 is_key = 0;
	u8 ccd_adjustment_sign = 0;
	

	ccd_adjustment_sign = 0;
	aim_line_point = CCD_Adjustment;
	

	TSL1401_SetEnabled(1);
	
	delay_ms(500);
	while (!TSL1401_Cal_Ready);
	TSL1401_Measure(!TSL1401_Is_Find_ADC_Threshold);
	LCD_Clear(WHITE);
	while(1)
	{
		LCD_printf(0,6+36*1,300,24,24,"Press any key to start 1");
		LCD_printf(0,6+36*2,300,24,24,"Edge Type:%u			",TSL1401_State[ccdy].Line_Edge_Type);
		LCD_printf(0,6+36*3,300,24,24,"Mpos:%u			",TSL1401_State[ccdy].Line_Edge_Median_Pos);
		LCD_printf(0,6+36*4,300,24,24,"Left pos:%u			",TSL1401_State[ccdy].Line_Edge_Left_Pos);
		LCD_printf(0,6+36*5,300,24,24,"Right pos:%u			",TSL1401_State[ccdy].Line_Edge_Right_Pos);
		
		//is_key = keyScan(1);
		is_key = 1;
		if (is_key)
		{
			is_key = 0;
			if (keyValue == keyback)
			{
				TSL1401_SetEnabled(0);
				return;
			}
			else
				break;
		}
		else
			delay_ms(1);
	}
	
	switch (TSL1401_State[ccdy].Line_Edge_Type)
	{
		case 0:
			ccd_adjustment_sign &= ~(2 << 2);
			ccd_adjustment_sign |= (0 << 2);
			break;
		case 1:
			ccd_adjustment_sign &= ~(2 << 2);
			ccd_adjustment_sign |= (1 << 2);
			aim_line_point.aim_position.x = GPS_List[0].position.x + ccd_line.Line_Move_Offset[1].x;
			SetLine(&aim_line_point);
			break;
		case 2:
			ccd_adjustment_sign &= ~(2 << 2);
			ccd_adjustment_sign |= (2 << 2);
			aim_line_point.aim_position.y = GPS_List[0].position.y + ccd_line.Line_Move_Offset[1].y;
			SetLine(&aim_line_point);
			break;
//		case 4:
//			ccd_adjustment_sign &= ~(2 << 2);
//			ccd_adjustment_sign |= (2 << 2);
//			aim_line_point.aim_position.x = GPS_List[0].position.x + ccd_line.Line_Move_Offset[2].x;
//			break;
	}
	if (ccd_adjustment_sign)
	{
		Return_Any_Point(&aim_line_point,5.0,1.0,3);
		
		delay_ms(500);
		while (!TSL1401_Cal_Ready);
		TSL1401_Measure(!TSL1401_Is_Find_ADC_Threshold);
	}
	
	while(1)
	{
		LCD_printf(0,6+36*1,300,24,24,"Press any key to start 2");
		LCD_printf(0,6+36*2,300,24,24,"Edge Type:%u			",TSL1401_State[ccdy].Line_Edge_Type);
		LCD_printf(0,6+36*3,300,24,24,"Mpos:%u			",TSL1401_State[ccdy].Line_Edge_Median_Pos);
		LCD_printf(0,6+36*4,300,24,24,"Left pos:%u			",TSL1401_State[ccdy].Line_Edge_Left_Pos);
		LCD_printf(0,6+36*5,300,24,24,"Right pos:%u			",TSL1401_State[ccdy].Line_Edge_Right_Pos);
		
		//is_key = keyScan(1);
		
		is_key = 1;
		if (is_key)
		{
			is_key = 0;
			if (keyValue == keyback)
			{
				TSL1401_SetEnabled(0);
				return;
			}
			else
				break;
		}
		else
			delay_ms(1);
	}
	TSL1401_SetEnabled(0);
	if(TSL1401_State[ccdy].Line_Edge_Type != 0)
	{	
		LCD_printf(0,6+36*7,300,24,24,"CCD_Failed");
		return;
	}			
	aim_line_point = CCD_Adjustment;
	aim_line_point.aim_position.x = GPS_List[0].position.x;//+ (ccd_line.Line_Edge_Median_Pos[ccdx] - TSL1401_State[ccdx].Line_Edge_Median_Pos) * TSL1401_State[ccdx].Pixel_To_Distance;
	aim_line_point.aim_position.y = GPS_List[0].position.y + (ccd_line.Line_Edge_Median_Pos[ccdy] - TSL1401_State[ccdy].Line_Edge_Median_Pos) * TSL1401_State[ccdy].Pixel_To_Distance;
	
	Return_Any_Point(&aim_line_point,5.0,1.0,3);
	
	delay_ms(50);
	GPS_Init(GPS_List[0].position.x,std_start_pos.y);
	delay_ms(200);
	
//	aim_line_point.aim_position = std_start_pos;
//	 
//	Return_Any_Point(&aim_line_point,5.0,1.0);
}


u8 pos_Grab_cnt = 1;
u8 black_Mask = 0;
u8 is_This_Black_Noput = 0;
u8 last_Black = 0;

struct Line_Point Color_Judge(void)
{
	struct Line_Point aim_line_point;
	Camera_Set_Mode(2);
	
	aim_line_point = Task_1_Put_Point_Offset[0];
	while(!Is_Color_Finished);
	
	switch(Color_Res[color_Detect_Cnt - 1])
	{
		case 'b':
			aim_line_point = Task_1_Put_Point_Offset[1 - 1];
			aim_line_point.aim_position.x = Center_Point.aim_position.x + Task_1_Put_Point_Offset[1 - 1].aim_position.x;
			aim_line_point.aim_position.y = Center_Point.aim_position.y + Task_1_Put_Point_Offset[1 - 1].aim_position.y;
			set_loc[1] = PanTilt_Zero + 1024*2 +25;//+ 20; 
			pos_Grab_cnt++;
			Is_Color_Finished = 0;
			Color_Res[0] = 0;
			LCD_printf(0,6+36*7,300,24,24,"Blue Blue		");
			break;
		case 'g':
			aim_line_point = Task_1_Put_Point_Offset[2 - 1];
			aim_line_point.aim_position.x = Center_Point.aim_position.x + Task_1_Put_Point_Offset[2 - 1].aim_position.x;
			aim_line_point.aim_position.y = Center_Point.aim_position.y + Task_1_Put_Point_Offset[2 - 1].aim_position.y;
			set_loc[1] = PanTilt_Zero + 1024*4 -65;// - 55;  
			pos_Grab_cnt++;
			Is_Color_Finished = 0;
			Color_Res[0] = 0;
			LCD_printf(0,6+36*7,300,24,24,"Green Green		");
			break;
		case 'r':
			aim_line_point = Task_1_Put_Point_Offset[3 - 1];
			aim_line_point.aim_position.x = Center_Point.aim_position.x + Task_1_Put_Point_Offset[3 - 1].aim_position.x;
			aim_line_point.aim_position.y = Center_Point.aim_position.y + Task_1_Put_Point_Offset[3 - 1].aim_position.y;
			set_loc[1] = PanTilt_Zero + 1024*6 +20; 
			pos_Grab_cnt++;
			Is_Color_Finished = 0;
			Color_Res[0] = 0;
			LCD_printf(0,6+36*7,300,24,24,"Red Red			");
			break;
		case 'w':
			aim_line_point = Task_1_Put_Point_Offset[4 - 1];
			aim_line_point.aim_position.x = Center_Point.aim_position.x + Task_1_Put_Point_Offset[4 - 1].aim_position.x;
			aim_line_point.aim_position.y = Center_Point.aim_position.y + Task_1_Put_Point_Offset[4 - 1].aim_position.y;
			set_loc[1] = PanTilt_Zero + 25 + 25; //+25; 
			pos_Grab_cnt++;
			Is_Color_Finished = 0;
			Color_Res[0] = 0;
			LCD_printf(0,6+36*7,300,24,24,"White White		");
			break;
		case 'k':
			if(pos_Grab_cnt != 4)
			{	
				pos_Put();
				black_Mask = pos_Grab_cnt;
				Is_Color_Finished = 0;
				is_This_Black_Noput = 1;
				pos_Grab_cnt++;
				Color_Res[0] = 0;
				LCD_printf(0,6+36*7,300,24,24,"Black Black		");
				return Center_Point;
			}
			else if(pos_Grab_cnt == 4)
			{
				aim_line_point = Task_1_Put_Point_Offset[5 - 1];
				aim_line_point.aim_position.x = Center_Point.aim_position.x + Task_1_Put_Point_Offset[5 - 1].aim_position.x;
				aim_line_point.aim_position.y = Center_Point.aim_position.y + Task_1_Put_Point_Offset[5 - 1].aim_position.y;
				pos_Grab_cnt++; 
				set_loc[1] = PanTilt_Zero + 1024*5 + 20; 
				set_loc[0] = 500000;
				last_Black = 1;
				Is_Color_Finished = 0;
				Color_Res[0] = 0;
				LCD_printf(0,6+36*7,300,24,24,"Black Black		");
			}
			break;
		default:
			break;
	}
	return aim_line_point;
}

void goDirection(u8 direction, double initAxis,double set_radian,double maxSpeed)//1:+x,2:-x,3:+y,4:-y无论车身角度是否变化
{
	struct Point pos = {0};						//理论坐标
	struct Point cur_pos = {0};
	double cur_radian = 0;
	
	double speed_x = 0;							//世界坐标里的速度与分速度
	double speed_y = 0;
	double speed = 70;
	double speed_robot_x = 0;
	double speed_robot_y = 0;					//转换到机器人坐标的分速度
	
	double error_angle = 0, error_dis = 0;			//角度误差与距离误差
	double Vout_A = 0;						//PID调整后角度输出值
	double Vout_D = 0;						//PID调整后距离输出值
	double v_err_x = 0, v_err_y = 0;					//PID调整速度的分量
	
	double sin_temp = 0, cos_temp = 0;
	
	speed = maxSpeed;
	cur_pos.x = GPS_List[0].position.x;
	cur_pos.y = GPS_List[0].position.y;
	cur_radian = GPS_List[0].radian;
	
	switch(direction)
	{
		case 1:
			pos.x = GPS_List[0].position.x + 50;
			pos.y = initAxis;
			Line_Angle = 0;
		break;
		case 2:
			pos.x = GPS_List[0].position.x - 50;
			pos.y = initAxis;
			Line_Angle = pi;
		break;
		case 3:
			pos.x = initAxis;
			pos.y = GPS_List[0].position.y + 50;
			Line_Angle = pi/2;
		break;
		case 4:
			pos.x = initAxis;
			pos.y = GPS_List[0].position.y - 50;
			Line_Angle = -pi/2;
		break;
	}
	
	
	cos_temp = cos(Line_Angle);
	sin_temp = sin(Line_Angle);
	
	//求速度在x,y方向上的分量
	speed_x = speed * cos_temp;
	speed_y = speed * sin_temp;
	
	//角度误差和距离误差
	error_angle = set_radian - cur_radian;
	if (fabs(fabs(error_angle) - pi) < 5 * DEG2RAD)
	{
		if (Rotation_Dir == 1)
		{
			while (error_angle < 0)
				error_angle += 2 * pi;
		}
		else if (Rotation_Dir == -1)
		{
			while (error_angle > 0)
				error_angle -= 2 * pi;
		}
	}
	else
	{
		if (error_angle > pi)
			error_angle -= 2 * pi;
		if (error_angle < -pi)
			error_angle += 2 * pi;
	}
	
	//error_dis为垂直路径方向上偏离路径的距离，无误！
	error_dis = (cur_pos.x - pos.x) * sin_temp -(cur_pos.y - pos.y) * cos_temp;
	
	//PID调整
	//if(GetLength(GPS.position,Sta_Point) >= Acc_Dis)
	Vout_A = 1000*AnglePID(error_angle, &Pid_List[6 << 1]);
	Vout_D = DistancePID(error_dis, &Pid_List[(6 << 1) | 1]);
	
	if (Vout_A >= 150)
		Vout_A = 150;
	if (Vout_A <= -150)
		Vout_A = -150;
	
	//PID调整速度的分量
	v_err_x = -Vout_D * sin_temp;
	v_err_y =  Vout_D * cos_temp;
	
	//加上调整增量
	speed_x += v_err_x;
	speed_y += v_err_y;
	
	speed = sqrt(speed_x * speed_x + speed_y * speed_y);
	if (speed > 100)
	{
		speed_x *= 100 / speed;
		speed_y *= 100 / speed;
	}
	
	cos_temp = cos(GPS_List[0].radian);
	sin_temp = sin(GPS_List[0].radian);
	
	//将世界坐标的速度转换为机器人局部坐标的速度
	speed_robot_x =  speed_x * cos_temp + speed_y * sin_temp;
	speed_robot_y = -speed_x * sin_temp + speed_y * cos_temp;
	
	//为四轮赋速度
	Speed_X = speed_robot_x;
	Speed_Y = speed_robot_y;
	Speed_Rotation = Vout_A;
	
	SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
	
}
//0.70711
float cof = 0.9;
void Camera_Cvt_GPS(u8 point, int8_t cam_x, int8_t cam_y)
{
	struct Point Cam_Offset = {0};
	struct Line_Point aim_line_point;
	
	switch(point)
	{
		case 1:
			Cam_Offset.x = 0.70711*cam_x - 0.70711*cam_y;
			Cam_Offset.y = -0.70711*cam_x - 0.70711*cam_y;
			break;
		case 2:
			Cam_Offset.x = 0.70711*cam_x + 0.70711*cam_y;
			Cam_Offset.y = 0.70711*cam_x - 0.70711*cam_y;
			break;
		case 3:
			Cam_Offset.x = -0.70711*cam_x + 0.70711*cam_y;
			Cam_Offset.y = 0.70711*cam_x + 0.70711*cam_y;
			break;
		case 4:
			Cam_Offset.x = -0.70711*cam_x - 0.70711*cam_y;
			Cam_Offset.y = -0.70711*cam_x + 0.70711*cam_y;
			break;
		default:
			break;
	}
	LCD_Clear(WHITE);
	LCD_printf(0,6+36*4,300,24,24,"O_x:%d		",cam_x);
	LCD_printf(0,6+36*5,300,24,24,"O_y:%d		",cam_y);
	LCD_printf(0,6+36*6,300,24,24,"X:%lf		",-Cam_Offset.x);
	LCD_printf(0,6+36*7,300,24,24,"Y:%lf		",-Cam_Offset.y);
	LCD_printf(0,6+36*8,300,24,24,"Point:%d		",point);
	aim_line_point = Task_1_Put_Point_Offset[1 - 1];
	aim_line_point.speed_max = 50;
	aim_line_point.aim_position.x = GPS_List[0].position.x - cof*Cam_Offset.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y - cof*Cam_Offset.y;
	if(sqrt(Cam_Offset.x*Cam_Offset.x + Cam_Offset.y*Cam_Offset.y) > 50)
	{
		LCD_printf(0,6+36*9,300,24,24,"!!!Camera Failed!!!");
		return;
	}
	Return_Any_Point(&aim_line_point,10.0,1.0,3);
	
}

void Put_Camera_Cvt_GPS(u8 dir, int8_t cam_x, int8_t cam_y)
{
	struct Point Cam_Offset = {0};
	struct Line_Point aim_line_point;
	
	switch(dir)
	{
		case 'w':
			Cam_Offset.x = -cam_y;
			Cam_Offset.y = -cam_x;
			break;
		case 'b':
			Cam_Offset.x = cam_x;
			Cam_Offset.y = -cam_y;
			break;
		case 'g':
			Cam_Offset.x = cam_y;
			Cam_Offset.y = cam_x;
			break;
		case 'r':
			Cam_Offset.x = -cam_x;
			Cam_Offset.y = cam_y;
			break;
		case 'k':
			Cam_Offset.x = -0.70711*cam_x + 0.70711*cam_y;
			Cam_Offset.y = 0.70711*cam_x + 0.70711*cam_y;
			break;
		default:
			break;
	}
	LCD_Clear(WHITE);
	
	LCD_printf(0,6+36*8,300,24,24,"dir:%c  %u		",dir,dir);
	LCD_printf(0,6+36*4,300,24,24,"O_x:%d		",cam_x);
	LCD_printf(0,6+36*5,300,24,24,"O_y:%d		",cam_y);
	LCD_printf(0,6+36*6,300,24,24,"X:%lf		",-Cam_Offset.x);
	LCD_printf(0,6+36*7,300,24,24,"Y:%lf		",-Cam_Offset.y);
	
	aim_line_point = Task_1_Put_Point_Offset[1 - 1];
	aim_line_point.speed_max = 50;
	aim_line_point.aim_position.x = GPS_List[0].position.x - cof*Cam_Offset.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y - cof*Cam_Offset.y;
	if(sqrt(Cam_Offset.x*Cam_Offset.x + Cam_Offset.y*Cam_Offset.y) > 50)
	{
		LCD_printf(0,6+36*9,300,24,24,"!!!Camera Failed!!!");
		return;
	}
	Return_Any_Point(&aim_line_point,5.0,1.0,3);
}	

void pos_Grab(void)
{
	//USART_SendByte(USART2, 0x31)
	delay_ms(500);
	Cylinder = Cylin_Down;
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1500);
	Grab = Grab_Open;
	delay_ms(300);
	Grab = Grab_Close;
	delay_ms(300);
	Grab = Grab_Open;
	delay_ms(300);
	Cylinder = Cylin_Up;
	//USART_SendByte(USART2, 0x31);
	delay_ms(200);
	//set_loc[0] = 300000;
}

u8 is_put_balck = 0;

void pos_Put(void)
{
	u8 temp = 0;
	
	temp = Color_Res[color_Detect_Cnt - 1];
	if(temp != 'k')
	{
		if(is_task_2 == 1)
		{
			if(temp == 'w')
				temp = 'b';
			else if(temp == 'g' || temp == 'b')
				temp = 'g';
		}
		if(is_put_balck != 1)
		{
			delay_ms(1000);
			Camera_Set_Mode(4);
			delay_ms(1000);
			Put_Camera_Cvt_GPS(temp,Put_Circle_X,Put_Circle_Y);
		}
		else
		{
			is_put_balck = 0;
			delay_ms(500);
		}
	}
	else
	{
		delay_ms(500);
	}
	delay_ms(500);
	Cylinder = Cylin_Down;
	delay_ms(1500);
	delay_ms(1500);
	delay_ms(500); 
	Grab = Grab_Close;
	delay_ms(1000);
	Cylinder = Cylin_Up;
	delay_ms(1500);
	//delay_ms(500);
	USART_SendByte(USART2, 0x31);
	delay_ms(200);
}

