#include "all.h"

void Return_Any_Point(struct Line_Point *aim_line_point, double distance_err, double angle_err)
{
	u8 is_key = 0;
	
	LCD_Clear(WHITE);
	SetLine(aim_line_point);
	while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < distance_err && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < angle_err * DEG2RAD))
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
}
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
	
	switch (TSL1401_State[3].Line_Edge_Type)
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
	switch (TSL1401_State[1].Line_Edge_Type)
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
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 5.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
	aim_line_point.aim_position.x = GPS_List[0].position.x + (ccd_line.Line_Edge_Median_Pos[ccdx] - TSL1401_State[ccdx].Line_Edge_Median_Pos) * TSL1401_State[ccdx].Pixel_To_Distance;;
	aim_line_point.aim_position.y = GPS_List[0].position.y - (ccd_line.Line_Edge_Median_Pos[ccdy] - TSL1401_State[ccdy].Line_Edge_Median_Pos) * TSL1401_State[ccdy].Pixel_To_Distance;;
	
	Return_Any_Point(&aim_line_point,10.0,1.0);
}
