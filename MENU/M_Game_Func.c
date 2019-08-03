#include "all.h"

void Return_Any_Point(struct Line_Point *aim_line_point, double distance_err, double angle_err)
{
	u8 is_key = 0;
	
	//LCD_Clear(WHITE);
	SetLine(aim_line_point);
	while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < distance_err && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < angle_err * DEG2RAD))
	{
		GoLine();
		
		LCD_printf(0,6+36*0,300,24,24,"1.Angle =%lf     	   ",GPS_List[0].angle);
		LCD_printf(0,6+36*1,300,24,24,"2.X =%lf     	   ",GPS_List[0].position.x);
		LCD_printf(0,6+36*2,300,24,24,"3.Y =%lf 	       ",GPS_List[0].position.y);
		
		LCD_printf(0,6+36*3,300,24,24,"1.Angle =%lf        `",Aim_Line_Point.aim_radian);
		LCD_printf(0,6+36*4,300,24,24,"2.Aim X =%lf        `",Aim_Line_Point.aim_position.x);
		LCD_printf(0,6+36*5,300,24,24,"3.Aim Y =%lf        `",Aim_Line_Point.aim_position.y);
		
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
struct CCD_Line Corner_Point_CCD_Line[6] ={
	{{60, 58, 0, 0}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},//F//B//L//R
	{{110, 0, 68, 0}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
	{{0, 0, 70, 19}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
	{{0, 57, 0, 58}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
	{{64, 0, 0, 0}, {{0, 100}, {30, 30}, {0, 30}, {0, 0}}},
	{{0, 0, 0, 64}, {{100, 0}, {30, 30}, {30, 0}, {0, 0}}},
};
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
	
	Return_Any_Point(&aim_line_point,10.0,1.0);
}

void CCD_Adjust_to_GPS(struct CCD_Line ccd_line, uint8_t ccdx, uint8_t ccdy, struct Point std_point)
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
		LCD_printf(0,6+36*7,300,24,24,"CCD_Failed");
		return;
	}			
	aim_line_point = CCD_Adjustment;
	aim_line_point.aim_position.x = GPS_List[0].position.x + (ccd_line.Line_Edge_Median_Pos[ccdx] - TSL1401_State[ccdx].Line_Edge_Median_Pos) * TSL1401_State[ccdx].Pixel_To_Distance;
	aim_line_point.aim_position.y = GPS_List[0].position.y + (ccd_line.Line_Edge_Median_Pos[ccdy] - TSL1401_State[ccdy].Line_Edge_Median_Pos) * TSL1401_State[ccdy].Pixel_To_Distance;
	
	Return_Any_Point(&aim_line_point,5.0,1.0);
	
	GPS_Init(std_point.x, std_point.y);
}

void CCD_Adjust_to_GPS_X(struct CCD_Line ccd_line, uint8_t ccdx, struct Point std_start_pos)
{
	struct Line_Point aim_line_point;
	u8 is_key = 0;
	u8 ccd_adjustment_sign = 0;
	
	
	ccd_adjustment_sign = 0;
	aim_line_point = CCD_Adjustment;
	aim_line_point.aim_position.x = GPS_List[0].position.x; 
	aim_line_point.aim_position.y = GPS_List[0].position.y + ccd_line.Line_Move_Offset[0].y;
	SetLine(&aim_line_point);
	
	Return_Any_Point(&aim_line_point,10.0,1.0);
	
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
		Return_Any_Point(&aim_line_point,5.0,1.0);
		
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
	if(TSL1401_State[ccdx].Line_Edge_Type != 0)
	{	
		LCD_printf(0,6+36*7,300,24,24,"CCD_Failed");
		return;
	}			
	aim_line_point = CCD_Adjustment;
	aim_line_point.aim_position.x = GPS_List[0].position.x + (ccd_line.Line_Edge_Median_Pos[ccdx] - TSL1401_State[ccdx].Line_Edge_Median_Pos) * TSL1401_State[ccdx].Pixel_To_Distance;
	aim_line_point.aim_position.y = GPS_List[0].position.y;//+ (ccd_line.Line_Edge_Median_Pos[ccdy] - TSL1401_State[ccdy].Line_Edge_Median_Pos) * TSL1401_State[ccdy].Pixel_To_Distance;
	
	Return_Any_Point(&aim_line_point,5.0,1.0);
	
	delay_ms(50);
	GPS_Init(std_start_pos.x,GPS_List[0].position.y);
	
	aim_line_point.aim_position = std_start_pos;
	
	Return_Any_Point(&aim_line_point,10.0,1.0);
}

void CCD_Adjust_to_GPS_Y(struct CCD_Line ccd_line, uint8_t ccdy, struct Point std_start_pos)
{
	struct Line_Point aim_line_point;
	u8 is_key = 0;
	u8 ccd_adjustment_sign = 0;
	

	ccd_adjustment_sign = 0;
	aim_line_point = CCD_Adjustment;
	aim_line_point.aim_position.x = GPS_List[0].position.x + ccd_line.Line_Move_Offset[0].x; 
	aim_line_point.aim_position.y = GPS_List[0].position.y;
	SetLine(&aim_line_point);
	
	Return_Any_Point(&aim_line_point,5.0,1.0);

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
		case 4:
			ccd_adjustment_sign &= ~(2 << 2);
			ccd_adjustment_sign |= (2 << 2);
			aim_line_point.aim_position.x = GPS_List[0].position.x + ccd_line.Line_Move_Offset[2].x;
			break;
	}
	if (ccd_adjustment_sign)
	{
		Return_Any_Point(&aim_line_point,5.0,1.0);
		
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
	if(TSL1401_State[ccdy].Line_Edge_Type != 0)
	{	
		LCD_printf(0,6+36*7,300,24,24,"CCD_Failed");
		return;
	}			
	aim_line_point = CCD_Adjustment;
	aim_line_point.aim_position.x = GPS_List[0].position.x;//+ (ccd_line.Line_Edge_Median_Pos[ccdx] - TSL1401_State[ccdx].Line_Edge_Median_Pos) * TSL1401_State[ccdx].Pixel_To_Distance;
	aim_line_point.aim_position.y = GPS_List[0].position.y + (ccd_line.Line_Edge_Median_Pos[ccdy] - TSL1401_State[ccdy].Line_Edge_Median_Pos) * TSL1401_State[ccdy].Pixel_To_Distance;
	
	Return_Any_Point(&aim_line_point,5.0,1.0);
	
	delay_ms(50);
	GPS_Init(GPS_List[0].position.x,std_start_pos.y);
	
	aim_line_point.aim_position = std_start_pos;
	 
	Return_Any_Point(&aim_line_point,5.0,1.0);
}

u8 pos_Grab_cnt = 1;
u8 black_Mask = 0;
u8 is_This_Black = 0;
struct Line_Point Color_Judge(void)
{
	struct Line_Point aim_line_point;
	USART_SendByte(USART2,0x73);
	
	aim_line_point = Task_1_Put_Point_Offset[0];
	while(!Is_Color_Finished);
	
	switch(Color_Res[0])
	{
		case 'b':
			aim_line_point = Task_1_Put_Point_Offset[1 - 1];
			aim_line_point.aim_position.x = Center_Point.aim_position.x + Task_1_Put_Point_Offset[1 - 1].aim_position.x;
			aim_line_point.aim_position.y = Center_Point.aim_position.y + Task_1_Put_Point_Offset[1 - 1].aim_position.y;
			set_loc[1] = PanTilt_Zero + 1024*2; 
			pos_Grab_cnt++;
			Is_Color_Finished = 0;
			Color_Res[0] = 0;
			LCD_printf(0,6+36*7,300,24,24,"Blue Blue		");
			break;
		case 'g':
			aim_line_point = Task_1_Put_Point_Offset[2 - 1];
			aim_line_point.aim_position.x = Center_Point.aim_position.x + Task_1_Put_Point_Offset[2 - 1].aim_position.x;
			aim_line_point.aim_position.y = Center_Point.aim_position.y + Task_1_Put_Point_Offset[2 - 1].aim_position.y;
			set_loc[1] = PanTilt_Zero + 1024*4;  
			pos_Grab_cnt++;
			Is_Color_Finished = 0;
			Color_Res[0] = 0;
			LCD_printf(0,6+36*7,300,24,24,"Green Green		");
			break;
		case 'r':
			aim_line_point = Task_1_Put_Point_Offset[3 - 1];
			aim_line_point.aim_position.x = Center_Point.aim_position.x + Task_1_Put_Point_Offset[3 - 1].aim_position.x;
			aim_line_point.aim_position.y = Center_Point.aim_position.y + Task_1_Put_Point_Offset[3 - 1].aim_position.y;
			set_loc[1] = PanTilt_Zero - 1024*2; 
			pos_Grab_cnt++;
			Is_Color_Finished = 0;
			Color_Res[0] = 0;
			LCD_printf(0,6+36*7,300,24,24,"Red Red			");
			break;
		case 'w':
			aim_line_point = Task_1_Put_Point_Offset[4 - 1];
			aim_line_point.aim_position.x = Center_Point.aim_position.x + Task_1_Put_Point_Offset[4 - 1].aim_position.x;
			aim_line_point.aim_position.y = Center_Point.aim_position.y + Task_1_Put_Point_Offset[4 - 1].aim_position.y;
			set_loc[1] = PanTilt_Zero; 
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
				is_This_Black = 1;
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
				set_loc[1] = PanTilt_Zero - 1024*3 - 50; 
				set_loc[0] = 500000;
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

void pos_Grab(void)
{
	delay_ms(1000);
	Cylinder = Cylin_Down;
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1500);
	Grab = Grab_Open;
	delay_ms(500);
	Cylinder = Cylin_Up;
	delay_ms(1000);
}

void pos_Put(void)
{
	Cylinder = Cylin_Down;
	delay_ms(1500);
	delay_ms(1500);
	delay_ms(500); 
	Grab = Grab_Close;
	delay_ms(1000);
	Cylinder = Cylin_Up;
	delay_ms(1000);
}

