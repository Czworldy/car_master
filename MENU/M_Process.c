#include "all.h"

struct Line_Point QR_Code_Point[2] = {
	{{1730, 580}, 0, 100, 400, 100, -1, 2},
	{{1730, 580}, 0, 100, 1400, 100, -1, 2},
};

struct Line_Point Original_Point = {{190, 165}, 0, 100, 1400, 100, -1, 2};
struct Line_Point Color_Check_Point = {{1410, 2520}, 0, 100, 1000, 100, -1, 2};

u8 Product_Point_Camera[2] = {110, 120};
double Camera_Pixel_To_Distance[2] = {75.0/288.0, 80.0/288.0};

u8 Working_Point_Index[3] = {3, 2, 1};//r:Working_Point[0],g:Working_Point[1],b:Working_Point[2]
u8 Product_Point_Index[3] = {1, 2, 3};//r:Product_Point[0],g:Product_Point[1],b:Product_Point[2]

struct GPS_State process_GPS_Offset[2] = {
	{{100.0, 140.0}, 0.0, 0.0},
	{{125.0, 115.0}, 0.0, 0.0},
};

struct Line_Point Stock_Point_Middle = {{1140, 410}, 0, 0, 0, 0, 0, 0};
struct Line_Point Stock_Point_Grab_Offset = {{0, -110}, 0, 100, 100, 100, -1, 2};
struct Line_Point Stock_Point_Leave_Offset = {{0, 180}, 0, 100, 200, 100, -1, 2};

struct Line_Point Working_Point_Drop_Middle = {{1080, 2020}, 0, 0, 0, 0, 0, 0};
struct Line_Point Working_Point_Drop_Leave_Offset = {{0, -100}, 0, 100, 200, 100, -1, 2};

struct Line_Point Working_Point_Take_Middle = {{1090, 1950}, 0, 0, 0, 0, 0, 0};
struct Line_Point Working_Point_Take_Grab_Offset = {{0, 160}, 0, 100, 200, 100, -1, 2};

struct Line_Point Product_Point_Middle = {{1990, 1190}, 0, 0, 0, 0, 0, 0};
struct Line_Point Product_Point_Leave_Offset = {{-100, 0}, 0, 100, 200, 100, -1, 2};

struct Line_Point Stock_Point_Offset_Slow[3] = {
	{{-150, 0}, 0, 50, 600, 50, -1, 2},
	{{   0, 0}, 0, 50, 600, 50, -1, 2},
	{{ 150, 0}, 0, 50, 600, 50, -1, 2},
};//L M R
struct Line_Point Stock_Point_Offset_Fast[3] = {
	{{-150, 0}, 0, 50, 1000, 50, -1, 2},
	{{   0, 0}, 0, 50, 1000, 50, -1, 2},
	{{ 150, 0}, 0, 50, 1000, 50, -1, 2},
};//L M R

struct Line_Point Working_Point_Drop_Offset_Slow[3] = {
	{{-300, 0}, 0, 50, 600, 50, 1, 2},
	{{   0, 0}, 0, 50, 600, 50, 1, 2},
	{{ 300, 0}, 0, 50, 600, 50, 1, 2},
};//R G B
struct Line_Point Working_Point_Drop_Offset_Fast[3] = {
	{{-300, 0}, 0, 50, 1000, 50, 1, 2},
	{{   0, 0}, 0, 50, 1000, 50, 1, 2},
	{{ 300, 0}, 0, 50, 1000, 50, 1, 2},
};//R G B

struct Line_Point Working_Point_Take_Offset_Slow[3] = {
	{{-300, 0}, 0, 50, 600, 50, 1, 2},
	{{   0, 0}, 0, 50, 600, 50, 1, 2},
	{{ 300, 0}, 0, 50, 600, 50, 1, 2},
};//R G B
struct Line_Point Working_Point_Take_Offset_Fast[3] = {
	{{-300, 0}, 0, 50, 800, 50, 1, 2},
	{{   0, 0}, 0, 50, 800, 50, 1, 2},
	{{ 300, 0}, 0, 50, 800, 50, 1, 2},
};//R G B

struct Line_Point Product_Point_Offset_Slow[3] = {
	{{0, -300}, 0, 50, 600, 50, -1, 2},
	{{0,    0}, 0, 50, 600, 50, -1, 2},
	{{0,  300}, 0, 50, 600, 50, -1, 2},
};//R G B
struct Line_Point Product_Point_Offset_Fast[3] = {
	{{0, -300}, 0, 50, 1000, 50, -1, 2},
	{{0,    0}, 0, 50, 1000, 50, -1, 2},
	{{0,  300}, 0, 50, 1000, 50, -1, 2},
};//R G B

struct Line_Point CCD_Adjustment = {{0, 0}, 0, 30, 50, 10, -1, 4};//{{0, 0}, 0, 30, 50, 30, -1, 4};

struct Line_Point Stock_Point_CCD_Middle_Slow = {{1430, 2320}, 0, 50, 200, 50, 1, 2};
struct Line_Point Stock_Point_CCD_Middle_Fast = {{1430, 2320}, 0, 50, 1200, 50, 1, 2};
struct Line_Point Stock_Point_CCD_Middle_Offset[3] = {
	{{0, -150}, 0, 30, 200, 30, -1, 2},
	{{0, 0}, 0, 30, 50, 30, -1, 2},
	{{0, 150}, 0, 30, 200, 30, -1, 2},
};//L M R
struct Line_Point Stock_Point_CCD_Grab_Offset = {{130, 0}, 0, 100, 200, 100, -1, 2};
struct Line_Point Stock_Point_CCD_Leave_Offset = {{-130, 0}, 0, 200, 200, 200, -1, 2};
struct CCD_Line Stock_Point_CCD_Line[3] = {
	{{0, 0, 0, 0}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
	{{0, 0, 0, 93}, {{0, 0}, {0, 0}, {0, 0}, {-50, 50}}},
	{{0, 0, 0, 0}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
};

//struct Line_Point Working_Point_Drop_CCD_Middle_Slow = {{1080, 2020}, 0, 50, 600, 50, 1, 2};
//struct Line_Point Working_Point_Drop_CCD_Middle_Fast = {{1080, 2020}, 0, 50, 1000, 50, 1, 2};
//struct Line_Point Working_Point_Drop_CCD_Middle_Offset[3] = {
//	{{-300, 0}, 0, 25, 100, 25, 1, 2},
//	{{   0, 0}, 0, 25, 50, 25, 1, 2},
//	{{ 300, 0}, 0, 25, 100, 25, 1, 2},
//};//R G B
struct Line_Point Working_Point_Drop_CCD_Middle_Slow = {{1200, 4230}, 0, 50, 600, 50, 1, 2};
struct Line_Point Working_Point_Drop_CCD_Middle_Fast = {{1200, 4230}, 0, 50, 1200, 50, 1, 2};
struct Line_Point Working_Point_Drop_CCD_Middle_Offset[3] = {
	{{-300, 140}, 0, 30, 300, 30, 1, 2},
	{{   0, 140}, 0, 30, 300, 30, 1, 2},
	{{ 300, 140}, 0, 30, 300, 30, 1, 2},
};//R G B
struct Line_Point Working_Point_Drop_CCD_Leave_Offset = {{0, -200}, 0, 200, 200, 200, -1, 2};
struct CCD_Line Working_Point_Drop_CCD_Line[3] = {
	{{0, 0, 0, 0}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
	{{0, 64, 83, 0}, {{0, 0}, {50, 50}, {50, -50}, {0, 0}}},
	{{0, 0, 0, 0}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
};

struct Line_Point Working_Point_Take_CCD_Slow[3] = {
	{{0, 0}, 0, 50, 200, 50, 1, 2},
	{{0, 0}, 0, 50, 200, 50, 1, 2},
	{{0, 0}, 0, 50, 200, 50, 1, 2},
};//R G B
struct Line_Point Working_Point_Take_CCD_Fast[3] = {
	{{0, 0}, 0, 50, 800, 50, 1, 2},
	{{0, 0}, 0, 50, 800, 50, 1, 2},
	{{0, 0}, 0, 50, 800, 50, 1, 2},
};//R G B
struct Line_Point Working_Point_Take_CCD_Grab_Offset = {{0, 130}, 0, 100, 200, 100, -1, 2};

struct Line_Point Product_Point_CCD_Middle_Slow = {{1850, 1220}, 0, 50, 600, 50, 1, 2};
struct Line_Point Product_Point_CCD_Middle_Fast = {{1850, 1220}, 0, 50, 1000, 50, 1, 2};
struct Line_Point Product_Point_CCD_Middle_Offset[3] = {
	{{150, -380}, 0, 25, 300, 25, -1, 2},
	{{150, -80}, 0, 25, 300, 25, -1, 2},
	{{150,  220}, 0, 25, 300, 25, -1, 2},
};//R G B
struct Line_Point Product_Point_CCD_Leave_Offset = {{-100, 0}, 0, 200, 200, 200, -1, 2};
struct CCD_Line Product_Point_CCD_Line[3] = {
	{{0, 0, 0, 0}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
	{{0, 21, 87, 0}, {{0, 0}, {50, 50}, {-50, 50}, {0, 0}}},
	{{0, 0, 0, 0}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
};
struct Line_Point Trans = {
	{1430, 2320}, 0, 50, 800, 50, 1, 2
};

void process_Show_QR_Code(u16 x,u16 y,u8 num)
{
	u8 temp,t1,t;
	u16 y0=y;
	u8 size = 48;
	u8 mode = 0;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数	
// 	num=num-' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num-' '][t]; 	 	//调用1206字体
		else if(size==16)temp=asc2_1608[num-' '][t];	//调用1608字体
		else if(size==24)temp=asc2_2412[num-' '][t];	//调用2412字体
		else if(size==48)temp=asc2_4824[num-'1'][t];	//调用4824字体
		else return;								//没有的字库
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_Fast_DrawPoint(x,y,POINT_COLOR);
			else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=lcddev.height)return;		//超区域了
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=lcddev.width)return;	//超区域了
				break;
			}
		}  	 
	}  	    	   	 	 
}
void process_Line_Point(struct Line_Point *aim_line_point)
{
	u8 tp_last, key_value, is_key = 0;
	double temp;
	u8 goline = 0;
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"1.aim_point_x = %.6lf", aim_line_point->aim_position.x);
	LCD_printf(0,6+36*1,300,24,24,"2.aim_point_y = %.6lf", aim_line_point->aim_position.y);
	LCD_printf(0,6+36*2,300,24,24,"3.aim_angle/deg = %.6lf",aim_line_point->aim_radian * RAD2DEG);
	LCD_printf(0,6+36*3,300,24,24,"4.speed_sta = %.6lf",aim_line_point->speed_sta);
	LCD_printf(0,6+36*4,300,24,24,"5.speed_max = %.6lf",aim_line_point->speed_max);
	LCD_printf(0,6+36*5,300,24,24,"6.speed_end = %.6lf",aim_line_point->speed_end);
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
					aim_line_point->aim_position.x = temp;
					break;
				case key2:
					Input_DoubleValue(&temp,"aim_point_y");
					aim_line_point->aim_position.y = temp;
					break;
				case key3:
					Input_DoubleValue(&temp,"aim_angle");
					while (temp > 180)
						temp -= 180;
					while (temp < -180)
						temp += 180;
					aim_line_point->aim_radian = temp * DEG2RAD;
					break;
				case key4:
					Input_DoubleValue(&temp,"speed_sta");
					aim_line_point->speed_sta = temp;
					break;
				case key5:
					Input_DoubleValue(&temp,"speed_max");
					aim_line_point->speed_max = temp;
					break;
				case key6:
					Input_DoubleValue(&temp,"speed_end");
					aim_line_point->speed_end = temp;
					break;
				case key7:
					GPS_Clear();
					break;
				case key8:
					SetLine(aim_line_point);
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
			LCD_printf(0,6+36*0,300,24,24,"1.aim_point_x = %.6lf", aim_line_point->aim_position.x);
			LCD_printf(0,6+36*1,300,24,24,"2.aim_point_y = %.6lf", aim_line_point->aim_position.y);
			LCD_printf(0,6+36*2,300,24,24,"3.aim_angle/deg = %.6lf",aim_line_point->aim_radian * RAD2DEG);
			LCD_printf(0,6+36*3,300,24,24,"4.speed_sta = %.6lf",aim_line_point->speed_sta);
			LCD_printf(0,6+36*4,300,24,24,"5.speed_max = %.6lf",aim_line_point->speed_max);
			LCD_printf(0,6+36*5,300,24,24,"6.speed_end = %.6lf",aim_line_point->speed_end);
			LCD_printf(0,6+36*6,300,24,24,"7.GPS Clear");
			LCD_printf(0,6+36*7,300,24,24,"8.Set line and go");
		}
		else
			delay_ms(1);
	}
	
	LCD_Clear(WHITE);
	LCD_printf(0,6+36*0,300,24,24,"GoLine");
	while (!(GetLength(&(GPS_List[0].position), &aim_line_point->aim_position) < 20.0 && fabs(GPS_List[0].radian - aim_line_point->aim_radian) < 1.0 * DEG2RAD))
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
//				case keyback:
//					SPEED_STOP;
//					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
//					return;
				default:
					break;
			}
		}
	}
	
	SPEED_STOP;
	SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
}

void process_Line(void)
{
	u8 tp_last, key_value, is_key = 0;
	int temp = 0;
	struct Line_Point aim_line_point = {0};
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"1.Color Check  2.Stock[0]   ");
	LCD_printf(0,6+36*1,300,24,24,"3.Stock[1]     4.Stock[2]   ");
	LCD_printf(0,6+36*2,300,24,24,"5.Working[0]   6.Working[1] ");
	LCD_printf(0,6+36*3,300,24,24,"7.Working[2]   8.Product[0] ");
	LCD_printf(0,6+36*4,300,24,24,"9.Product[1]   10.Product[2]");
	LCD_printf(0,6+36*5,300,24,24,"11.Original");
	LCD_printf(0,6+36*6,300,24,24,"Press OK to input index");
	
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
			if (key_value == keyOK)
				break;
			else if (key_value == keyback)
				return;
			else if (key_value == keyboardtab)
			{
				KeyBoard_State = !KeyBoard_State;
				Show_Keyboard();
				LCD_printf(0,6+36*0,300,24,24,"1.Color Check  2.Stock[0]   ");
				LCD_printf(0,6+36*1,300,24,24,"3.Stock[1]     4.Stock[2]   ");
				LCD_printf(0,6+36*2,300,24,24,"5.Working[0]   6.Working[1] ");
				LCD_printf(0,6+36*3,300,24,24,"7.Working[2]   8.Product[0] ");
				LCD_printf(0,6+36*4,300,24,24,"9.Product[1]   10.Product[2]");
				LCD_printf(0,6+36*5,300,24,24,"11.Original");
				LCD_printf(0,6+36*6,300,24,24,"Press OK to input index");
			}
		}
		else
			delay_ms(1);
	}
	
	Input_IntValue(&temp, "index");
	
	switch (temp)
	{
		case 1:
			aim_line_point = Color_Check_Point;
			process_Line_Point(&aim_line_point);
			break;
		case 2:
			aim_line_point = Stock_Point_Offset_Slow[0];
			aim_line_point.aim_position.x = Stock_Point_Middle.aim_position.x + Stock_Point_Offset_Slow[0].aim_position.x;
			aim_line_point.aim_position.y = Stock_Point_Middle.aim_position.y + Stock_Point_Offset_Slow[0].aim_position.y;
			process_Line_Point(&aim_line_point);
			break;
		case 3:
			aim_line_point = Stock_Point_Offset_Slow[1];
			aim_line_point.aim_position.x = Stock_Point_Middle.aim_position.x + Stock_Point_Offset_Slow[1].aim_position.x;
			aim_line_point.aim_position.y = Stock_Point_Middle.aim_position.y + Stock_Point_Offset_Slow[1].aim_position.y;
			process_Line_Point(&aim_line_point);
			break;
		case 4:
			aim_line_point = Stock_Point_Offset_Slow[2];
			aim_line_point.aim_position.x = Stock_Point_Middle.aim_position.x + Stock_Point_Offset_Slow[2].aim_position.x;
			aim_line_point.aim_position.y = Stock_Point_Middle.aim_position.y + Stock_Point_Offset_Slow[2].aim_position.y;
			process_Line_Point(&aim_line_point);
			break;
		case 5:
			aim_line_point = Working_Point_Drop_Offset_Slow[0];
			aim_line_point.aim_position.x = Working_Point_Drop_Middle.aim_position.x + Working_Point_Drop_Offset_Slow[0].aim_position.x;
			aim_line_point.aim_position.y = Working_Point_Drop_Middle.aim_position.y + Working_Point_Drop_Offset_Slow[0].aim_position.y;
			process_Line_Point(&aim_line_point);
			break;
		case 6:
			aim_line_point = Working_Point_Drop_Offset_Slow[1];
			aim_line_point.aim_position.x = Working_Point_Drop_Middle.aim_position.x + Working_Point_Drop_Offset_Slow[1].aim_position.x;
			aim_line_point.aim_position.y = Working_Point_Drop_Middle.aim_position.y + Working_Point_Drop_Offset_Slow[1].aim_position.y;
			process_Line_Point(&aim_line_point);
			break;
		case 7:
			aim_line_point = Working_Point_Drop_Offset_Slow[2];
			aim_line_point.aim_position.x = Working_Point_Drop_Middle.aim_position.x + Working_Point_Drop_Offset_Slow[2].aim_position.x;
			aim_line_point.aim_position.y = Working_Point_Drop_Middle.aim_position.y + Working_Point_Drop_Offset_Slow[2].aim_position.y;
			process_Line_Point(&aim_line_point);
			break;
		case 8:
			aim_line_point = Product_Point_Offset_Slow[0];
			aim_line_point.aim_position.x = Product_Point_Middle.aim_position.x + Product_Point_Offset_Slow[0].aim_position.x;
			aim_line_point.aim_position.y = Product_Point_Middle.aim_position.y + Product_Point_Offset_Slow[0].aim_position.y;
			process_Line_Point(&aim_line_point);
			break;
		case 9:
			aim_line_point = Product_Point_Offset_Slow[1];
			aim_line_point.aim_position.x = Product_Point_Middle.aim_position.x + Product_Point_Offset_Slow[1].aim_position.x;
			aim_line_point.aim_position.y = Product_Point_Middle.aim_position.y + Product_Point_Offset_Slow[1].aim_position.y;
			process_Line_Point(&aim_line_point);
			break;
		case 10:
			aim_line_point = Product_Point_Offset_Slow[2];
			aim_line_point.aim_position.x = Product_Point_Middle.aim_position.x + Product_Point_Offset_Slow[2].aim_position.x;
			aim_line_point.aim_position.y = Product_Point_Middle.aim_position.y + Product_Point_Offset_Slow[2].aim_position.y;
			process_Line_Point(&aim_line_point);
			break;
		case 11:
			aim_line_point = Original_Point;
			process_Line_Point(&aim_line_point);
			break;
		default:
			break;
	}
}

void process_Servo(void)
{
	u8 i, tp_last, key_value, is_key = 0;
	double pwm_duty[4] = {0};
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	for (i = 0; i < 4; ++i)
	{
		LCD_printf(0,6+36*i,300,24,24,"%d.Servo%d Duty = %u",i+1,i+1,Servo_Duty[i]);
	}
	LCD_printf(0,6+36*4,300,24,24,"5.Set Duty");
	
	while (1)
	{
		for (i = 0; i < 4; ++i)
		{
			LCD_printf(0,6+36*i,300,24,24,"%d.Servo%d Duty = %u",i+1,i+1,Servo_Duty[i]);
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
					if (pwm_duty[0] <= 50)
						Servo_Duty[0] = pwm_duty[0];
					break;
				case key2:
					Input_DoubleValue(&pwm_duty[1],"Servo2");
					if (pwm_duty[1] <= 50)
						Servo_Duty[1] = pwm_duty[1];
					break;
				case key3:
					Input_DoubleValue(&pwm_duty[2],"Servo3");
					if (pwm_duty[2] <= 50)
						Servo_Duty[2] = pwm_duty[2];
					break;
				case key4:
					Input_DoubleValue(&pwm_duty[3],"Servo4");
					if (pwm_duty[3] <= 50)
						Servo_Duty[3] = pwm_duty[3];
					break;
				case key5:
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
				LCD_printf(0,6+36*i,300,24,24,"%d.Servo%d Duty = %u",i+1,i+1,Servo_Duty[i]);
			}
			LCD_printf(0,6+36*4,300,24,24,"5.Set Duty");
		}
		else
			delay_ms(1);
	}
}

void process_QR_Code(void)
{
	u8 tp_last, key_value, is_key = 0;
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	
	#ifdef BSP_USING_USART3
	if (QR_Code_RX_Finish)
	{
		DMA_SetCurrDataCounter(USART3_DMA_TX_STREAM, QR_Code_TxBufferSize);
		DMA_Cmd(USART3_DMA_TX_STREAM, ENABLE);
		QR_Code_RX_Finish = 0;
	}
	#endif
	
	while (1)
	{
		LCD_printf(0,6+36*0,300,24,24,"1.Send Command");
		LCD_printf(0,6+36*1,300,24,24,"2.Ans:%c %c %c   ",QR_Code_Res[0], QR_Code_Res[1], QR_Code_Res[2]);
		LCD_printf(0,6+36*2,300,24,24,"3.%02X %02X %02X %02X %02X  ",QR_Code_RxBuffer[0], QR_Code_RxBuffer[1], QR_Code_RxBuffer[2], QR_Code_RxBuffer[3], QR_Code_RxBuffer[4]);
		LCD_printf(0,6+36*3,300,24,24,"4.%02X %02X %02X %02X %02X %02X  ",QR_Code_RxBuffer[5], QR_Code_RxBuffer[6], QR_Code_RxBuffer[7], QR_Code_RxBuffer[8], QR_Code_RxBuffer[9], QR_Code_RxBuffer[10]);
		LCD_printf(0,6+36*4,300,24,24,"5.WIFI 1:%c %c %c",WIFI_Res_1[0], WIFI_Res_1[1], WIFI_Res_1[2]);
		LCD_printf(0,6+36*5,300,24,24,"6.WIFI 2:%c %c %c",WIFI_Res_2[0], WIFI_Res_2[1], WIFI_Res_2[2]);
		
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

void process_Camera(void)
{
	u8 tp_last, key_value, is_key = 0;
	int camera_mode = 0;
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	
	while (1)
	{
		LCD_printf(0,6+36*0,300,24,24,"1.Camera Enable(Be sure they are OK)");
//		LCD_printf(0,6+36*1,300,24,24,"2.Camera Disable");
		LCD_printf(0,6+36*2,300,24,24,"3.Mode:%u",Camera_Mode);
		LCD_printf(0,6+36*3,300,24,24,"4.Rx:%u 		",Camera_RxBuffer[0]);
//		LCD_printf(0,6+36*4,300,24,24,"5.Hash:r%u g%u b%u",Color_Hash_Table[0],Color_Hash_Table[1],Color_Hash_Table[2]);
		LCD_printf(0,6+36*5,300,24,24,"6.Color Res:%s 	",Color_Res[0]);
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
					//Camera_Set_Mode(8);
					USART_SendByte(USART2,0x73);
					break;
				case key2:
					//Camera_Set_Mode(0);
					break;
				case key3:
					Input_IntValue(&camera_mode, "Mode");
					Camera_Set_Mode(camera_mode);
					break;
				case key7:
					USART_SendByte(USART2,0x6F);//o
					//Camera_Set_Mode(7);
					break;
				case keyback:
					return;
				case keyboardtab:
					KeyBoard_State = !KeyBoard_State;
					Show_Keyboard();
					LCD_printf(0,6+36*0,300,24,24,"1.Camera Enable(Be sure they are OK)");
					//LCD_printf(0,6+36*1,300,24,24,"2.Camera Disable");
					LCD_printf(0,6+36*2,300,24,24,"3.Mode:%u",Camera_Mode);
					LCD_printf(0,6+36*3,300,24,24,"4.Rx:%u 		",Camera_RxBuffer[0]);
					//LCD_printf(0,6+36*4,300,24,24,"5.Hash:r%u g%u b%u",Color_Hash_Table[0],Color_Hash_Table[1],Color_Hash_Table[2]);
					LCD_printf(0,6+36*5,300,24,24,"6.Color Res:%s 	",Color_Res[0]);
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

void process_Test(void)
{
	u8 tp_last, key_value, is_key = 0;
	
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"1.Line");
	LCD_printf(0,6+36*1,300,24,24,"2.Servo");
	LCD_printf(0,6+36*2,300,24,24,"3.QR Code");
	LCD_printf(0,6+36*3,300,24,24,"4.Camera");
	LCD_printf(0,6+36*4,300,24,24,"5.Angle = %lf        ",GPS_List[0].angle);
	LCD_printf(0,6+36*5,300,24,24,"6.X = %lf        ",GPS_List[0].position.x);
	LCD_printf(0,6+36*6,300,24,24,"7.Y = %lf        ",GPS_List[0].position.y);
	LCD_printf(0,6+36*7,300,24,24,"8.GPS Clear");
	LCD_printf(0,6+36*8,300,24,24,"9.Mecanum Disable");
	
	while (1)
	{
		LCD_printf(0,6+36*4,300,24,24,"5.Angle = %lf        ",GPS_List[0].angle);
		LCD_printf(0,6+36*5,300,24,24,"6.X = %lf        ",GPS_List[0].position.x);
		LCD_printf(0,6+36*6,300,24,24,"7.Y = %lf        ",GPS_List[0].position.y);
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
					process_Line();
					break;
				case key2:
					process_Servo();
					break;
				case key3:
					process_QR_Code();
					break;
				case key4:
					process_Camera();
					break;
				case key8:
					GPS_Clear();
					break;
				case key9:
					Motor_Set_Enabled(0);
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
			LCD_printf(0,6+36*0,300,24,24,"1.Line");
			LCD_printf(0,6+36*1,300,24,24,"2.Servo");
			LCD_printf(0,6+36*2,300,24,24,"3.QR Code");
			LCD_printf(0,6+36*3,300,24,24,"4.Camera");
			LCD_printf(0,6+36*4,300,24,24,"5.Angle = %lf        ",GPS_List[0].angle);
			LCD_printf(0,6+36*5,300,24,24,"6.X = %lf        ",GPS_List[0].position.x);
			LCD_printf(0,6+36*6,300,24,24,"7.Y = %lf        ",GPS_List[0].position.y);
			LCD_printf(0,6+36*7,300,24,24,"8.GPS Clear");
			LCD_printf(0,6+36*8,300,24,24,"9.Mecanum Disable");
		}
		else
			delay_ms(1);
	}
}

void process_All(void)
{
	struct Line_Point aim_line_point;
	u8 tp_last, key_value, is_key = 0;
	u8 process_step = 0;
	u16 t;
	u8 check_cnt_no_zero = 0, check_cnt_zero = 0;
	struct Point check_point_offset;
	
	GPS_Offset = process_GPS_Offset[0];
	GPS_Clear();
	
	Show_Keyboard();
	LCD_printf(0,6+36*0,300,24,24,"Be sure Raspberry Pi is OK");
	LCD_printf(0,6+36*1,300,24,24,"Be sure Cameras are OK");
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
			else
				break;
		}
		else
			delay_ms(1);
	}
	
	Camera_Set_Mode(8);
	
/*	//Waiting for Working Index
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"1.R G B: Working L->R");
	LCD_printf(0,6+36*1,300,24,24,"2.R B G: Working L->R");
	LCD_printf(0,6+36*2,300,24,24,"3.G R B: Working L->R");
	LCD_printf(0,6+36*3,300,24,24,"4.G B R: Working L->R");
	LCD_printf(0,6+36*4,300,24,24,"5.B R G: Working L->R");
	LCD_printf(0,6+36*5,300,24,24,"6.B G R: Working L->R");
	LCD_printf(0,6+36*6,300,24,24,"Press key to choose index");
	
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
			if (key_value == key1)
			{
				Working_Point_Index[0] = 1;
				Working_Point_Index[1] = 2;
				Working_Point_Index[2] = 3;
				break;
			}
			else if (key_value == key2)
			{
				Working_Point_Index[0] = 1;
				Working_Point_Index[1] = 3;
				Working_Point_Index[2] = 2;
				break;
			}
			else if (key_value == key3)
			{
				Working_Point_Index[0] = 2;
				Working_Point_Index[1] = 1;
				Working_Point_Index[2] = 3;
				break;
			}
			else if (key_value == key4)
			{
				Working_Point_Index[0] = 3;
				Working_Point_Index[1] = 1;
				Working_Point_Index[2] = 2;
				break;
			}
			else if (key_value == key5)
			{
				Working_Point_Index[0] = 2;
				Working_Point_Index[1] = 3;
				Working_Point_Index[2] = 1;
				break;
			}
			else if (key_value == key6)
			{
				Working_Point_Index[0] = 3;
				Working_Point_Index[1] = 2;
				Working_Point_Index[2] = 1;
				break;
			}
			else if (key_value == keyback)
				return;
		}
		else
			delay_ms(1);
	}
	
	//Waiting for Working Index
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"1.R G B: Product D->U");
	LCD_printf(0,6+36*1,300,24,24,"2.R B G: Product D->U");
	LCD_printf(0,6+36*2,300,24,24,"3.G R B: Product D->U");
	LCD_printf(0,6+36*3,300,24,24,"4.G B R: Product D->U");
	LCD_printf(0,6+36*4,300,24,24,"5.B R G: Product D->U");
	LCD_printf(0,6+36*5,300,24,24,"6.B G R: Product D->U");
	LCD_printf(0,6+36*6,300,24,24,"Press key to choose index");
	
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
			if (key_value == key1)
			{
				Product_Point_Index[0] = 1;
				Product_Point_Index[1] = 2;
				Product_Point_Index[2] = 3;
				break;
			}
			else if (key_value == key2)
			{
				Product_Point_Index[0] = 1;
				Product_Point_Index[1] = 3;
				Product_Point_Index[2] = 2;
				break;
			}
			else if (key_value == key3)
			{
				Product_Point_Index[0] = 2;
				Product_Point_Index[1] = 1;
				Product_Point_Index[2] = 3;
				break;
			}
			else if (key_value == key4)
			{
				Product_Point_Index[0] = 3;
				Product_Point_Index[1] = 1;
				Product_Point_Index[2] = 2;
				break;
			}
			else if (key_value == key5)
			{
				Product_Point_Index[0] = 2;
				Product_Point_Index[1] = 3;
				Product_Point_Index[2] = 1;
				break;
			}
			else if (key_value == key6)
			{
				Product_Point_Index[0] = 3;
				Product_Point_Index[1] = 2;
				Product_Point_Index[2] = 1;
				break;
			}
			else if (key_value == keyback)
				return;
		}
		else
			delay_ms(1);
	}*/
	
	//Waiting for beginning signal
	Camera_Set_Mode(0);
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
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
			else
				break;
		}
		else
			delay_ms(1);
	}
	
	//Color Check Point
	Show_Keyboard();
	POINT_COLOR=BLACK;
	aim_line_point = Color_Check_Point;
	SetLine(&aim_line_point);
	while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
			/*	case keyback:
					SPEED_STOP;
					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
					return;	*/
				default:
					break;
			}
		}
	}
	SPEED_STOP;
	SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
	
	Camera_Set_Mode(128);
	Camera_Set_Mode(1);
	t = 0;
	Show_Keyboard();
	while (1)
	{
		LCD_printf(0,6+36*0,300,24,24,"QR Code:0x%02X 0x%02X 0x%02X",QR_Code_Res[0],QR_Code_Res[1],QR_Code_Res[2]);
		LCD_printf(0,6+36*1,300,24,24,"Color Res:%u %u %u",Color_Res[0],Color_Res[1],Color_Res[2]);
		if (Is_Color_Finished)
			break;
		else
		{
			delay_ms(1);
			++t;
			if (t == 1000)
				Camera_Set_Mode(1);
		}
	}
	
	//Color Check Waiting
	Show_Keyboard();
	POINT_COLOR=BLACK;
	while (1)
	{
		LCD_printf(0,6+36*0,300,24,24,"QR Code:0x%02X 0x%02X 0x%02X",QR_Code_Res[0],QR_Code_Res[1],QR_Code_Res[2]);
		LCD_printf(0,6+36*1,300,24,24,"Color Res:%u %u %u",Color_Res[0],Color_Res[1],Color_Res[2]);
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
			else
				break;
		}
		else
			delay_ms(1);
	}
	
	//QR Code Point 0
	Show_Keyboard();
	POINT_COLOR=BLACK;
	aim_line_point = QR_Code_Point[0];
	SetLine(&aim_line_point);
	while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 20.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
			/*	case keyback:
					SPEED_STOP;
					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
					return;	*/
				default:
					break;
			}
		}
	}
	SPEED_STOP;
	SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
	
	Servo_Duty[0] = 12;
	Servo_Duty[1] = 50;
	Servo_Duty[2] = 33+1;
	Servo_Duty[3] = 27;
	Servo_PWM_SetDuty();
	delay_ms(300);
	
	//QR Code Check
	QR_Code_RX_Finish = 0;
	DMA_SetCurrDataCounter(USART3_DMA_TX_STREAM, QR_Code_TxBufferSize);
	DMA_Cmd(USART3_DMA_TX_STREAM, ENABLE);
	while (1)
	{
		if (QR_Code_RX_Finish)
		{
			if (QR_Code_Res[0] >= '1' && QR_Code_Res[0] <= '3' && 
				QR_Code_Res[1] >= '1' && QR_Code_Res[1] <= '3' && 
				QR_Code_Res[2] >= '1' && QR_Code_Res[2] <= '3')
				break;
			else
			{
				QR_Code_RX_Finish = 0;
				DMA_SetCurrDataCounter(USART3_DMA_TX_STREAM, QR_Code_TxBufferSize);
				DMA_Cmd(USART3_DMA_TX_STREAM, ENABLE);
			}
		}
	}
	
	//QR Code Check Waiting
	Show_Keyboard();
	POINT_COLOR=BLACK;
	while (1)
	{
		LCD_printf(0,6+36*0,300,24,24,"QR Code:0x%02X 0x%02X 0x%02X",QR_Code_Res[0],QR_Code_Res[1],QR_Code_Res[2]);
		LCD_printf(0,6+36*1,300,24,24,"Color Res:%u %u %u",Color_Res[0],Color_Res[1],Color_Res[2]);
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
			else
				break;
		}
		else
			delay_ms(1);
	}
	
	
	//Stock Point To Working Point
	for (process_step = 0; process_step < 3; ++process_step)
	{
		//Color QR Code Compare
		switch (Color_Hash_Table[QR_Code_Res[process_step]-'0'-1])
		{
			case 1:
				if (!process_step)
				{
					aim_line_point = Stock_Point_Offset_Slow[0];
					aim_line_point.aim_position.x = Stock_Point_Middle.aim_position.x + Stock_Point_Offset_Slow[0].aim_position.x;
					aim_line_point.aim_position.y = Stock_Point_Middle.aim_position.y + Stock_Point_Offset_Slow[0].aim_position.y;
					SetLine(&aim_line_point);
				}
				else
				{
					aim_line_point = Stock_Point_Offset_Fast[0];
					aim_line_point.aim_position.x = Stock_Point_Middle.aim_position.x + Stock_Point_Offset_Fast[0].aim_position.x;
					aim_line_point.aim_position.y = Stock_Point_Middle.aim_position.y + Stock_Point_Offset_Fast[0].aim_position.y;
					SetLine(&aim_line_point);
				}
				break;
			case 2:
				if (!process_step)
				{
					aim_line_point = Stock_Point_Offset_Slow[1];
					aim_line_point.aim_position.x = Stock_Point_Middle.aim_position.x + Stock_Point_Offset_Slow[1].aim_position.x;
					aim_line_point.aim_position.y = Stock_Point_Middle.aim_position.y + Stock_Point_Offset_Slow[1].aim_position.y;
					SetLine(&aim_line_point);
				}
				else
				{
					aim_line_point = Stock_Point_Offset_Fast[1];
					aim_line_point.aim_position.x = Stock_Point_Middle.aim_position.x + Stock_Point_Offset_Fast[1].aim_position.x;
					aim_line_point.aim_position.y = Stock_Point_Middle.aim_position.y + Stock_Point_Offset_Fast[1].aim_position.y;
					SetLine(&aim_line_point);
				}
				break;
			case 3:
				if (!process_step)
				{
					aim_line_point = Stock_Point_Offset_Slow[2];
					aim_line_point.aim_position.x = Stock_Point_Middle.aim_position.x + Stock_Point_Offset_Slow[2].aim_position.x;
					aim_line_point.aim_position.y = Stock_Point_Middle.aim_position.y + Stock_Point_Offset_Slow[2].aim_position.y;
					SetLine(&aim_line_point);
				}
				else
				{
					aim_line_point = Stock_Point_Offset_Fast[2];
					aim_line_point.aim_position.x = Stock_Point_Middle.aim_position.x + Stock_Point_Offset_Fast[2].aim_position.x;
					aim_line_point.aim_position.y = Stock_Point_Middle.aim_position.y + Stock_Point_Offset_Fast[2].aim_position.y;
					SetLine(&aim_line_point);
				}
				break;
			default:
				break;
		}
		
		Show_Keyboard();
		POINT_COLOR=BLACK;
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Duty[0] = 10;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 33+1;
		Servo_Duty[3] = 27;
		Servo_PWM_SetDuty();
		delay_ms(300);
		
		aim_line_point = Stock_Point_Grab_Offset;
		aim_line_point.aim_position.x = GPS_List[0].position.x + Stock_Point_Grab_Offset.aim_position.x;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Stock_Point_Grab_Offset.aim_position.y;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Duty[0] = 10;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 33+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(500);
		
		Servo_Duty[0] = 10;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 35+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(200);
		
		aim_line_point = Stock_Point_Leave_Offset;
		aim_line_point.aim_position.x = GPS_List[0].position.x + Stock_Point_Leave_Offset.aim_position.x;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Stock_Point_Leave_Offset.aim_position.y;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 15.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Duty[0] = 48;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 33+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(500);
		
		Show_Keyboard();
		POINT_COLOR=BLACK;
		LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
		//Waiting for beginning signal
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
				else
					break;
			}
			else
				delay_ms(1);
		}
		
		switch (QR_Code_Res[process_step]-'0')
		{
			case 1:
				aim_line_point = Working_Point_Drop_Offset_Fast[Working_Point_Index[0]-1];
				aim_line_point.aim_position.x = Working_Point_Drop_Middle.aim_position.x + Working_Point_Drop_Offset_Fast[Working_Point_Index[0]-1].aim_position.x;
				aim_line_point.aim_position.y = Working_Point_Drop_Middle.aim_position.y + Working_Point_Drop_Offset_Fast[Working_Point_Index[0]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			case 2:
				aim_line_point = Working_Point_Drop_Offset_Fast[Working_Point_Index[1]-1];
				aim_line_point.aim_position.x = Working_Point_Drop_Middle.aim_position.x + Working_Point_Drop_Offset_Fast[Working_Point_Index[1]-1].aim_position.x;
				aim_line_point.aim_position.y = Working_Point_Drop_Middle.aim_position.y + Working_Point_Drop_Offset_Fast[Working_Point_Index[1]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			case 3:
				aim_line_point = Working_Point_Drop_Offset_Fast[Working_Point_Index[2]-1];
				aim_line_point.aim_position.x = Working_Point_Drop_Middle.aim_position.x + Working_Point_Drop_Offset_Fast[Working_Point_Index[2]-1].aim_position.x;
				aim_line_point.aim_position.y = Working_Point_Drop_Middle.aim_position.y + Working_Point_Drop_Offset_Fast[Working_Point_Index[2]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			default:
				break;
		}
		Show_Keyboard();
		POINT_COLOR=BLACK;
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Duty[0] = 50;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 33+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(500);
		
		Servo_Duty[0] = 50;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 13+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(500);
		
		Servo_Duty[0] = 50;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 13+1;
		Servo_Duty[3] = 27;
		Servo_PWM_SetDuty();
		delay_ms(250);
		
		aim_line_point = Working_Point_Drop_Leave_Offset;
		aim_line_point.aim_position.x = GPS_List[0].position.x + Working_Point_Drop_Leave_Offset.aim_position.x;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Working_Point_Drop_Leave_Offset.aim_position.y;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 15.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		if (process_step != 2)
		{
			Servo_Duty[0] = 50;
			Servo_Duty[1] = 50;
			Servo_Duty[2] = 33+1;
			Servo_Duty[3] = 27;
			Servo_PWM_SetDuty();
			delay_ms(250);
			
			Servo_Duty[0] = 12;
			Servo_Duty[1] = 50;
			Servo_Duty[2] = 33+1;
			Servo_Duty[3] = 27;
			Servo_PWM_SetDuty();
			delay_ms(250);
		}
		
		//Waiting for beginning signal
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
				else
					break;
			}
			else
				delay_ms(1);
		}
	}
	
	Servo_Duty[0] = 50;
	Servo_Duty[1] = 33;
	Servo_Duty[2] = 13+1;
	Servo_Duty[3] = 27;
	Servo_PWM_SetDuty();
	delay_ms(250);
	
	//QR Code Point 1
	Show_Keyboard();
	POINT_COLOR=BLACK;
	aim_line_point = QR_Code_Point[1];
	SetLine(&aim_line_point);
	while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 20.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
//				case keyback:
//					SPEED_STOP;
//					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
//					return;
				default:
					break;
			}
		}
	}
	SPEED_STOP;
	SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
	
	Servo_Duty[0] = 48;
	Servo_Duty[1] = 33;
	Servo_Duty[2] = 13+1;
	Servo_Duty[3] = 27;
	Servo_PWM_SetDuty();
	
	//QR Code Check
	QR_Code_RX_Finish = 0;
	DMA_SetCurrDataCounter(USART3_DMA_TX_STREAM, QR_Code_TxBufferSize);
	DMA_Cmd(USART3_DMA_TX_STREAM, ENABLE);
	while (1)
	{
		if (QR_Code_RX_Finish)
		{
			if (QR_Code_Res[0] >= '1' && QR_Code_Res[0] <= '3' && 
				QR_Code_Res[1] >= '1' && QR_Code_Res[1] <= '3' && 
				QR_Code_Res[2] >= '1' && QR_Code_Res[2] <= '3')
				break;
			else
			{
				QR_Code_RX_Finish = 0;
				DMA_SetCurrDataCounter(USART3_DMA_TX_STREAM, QR_Code_TxBufferSize);
				DMA_Cmd(USART3_DMA_TX_STREAM, ENABLE);
			}
		}
	}
	
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
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
			else
				break;
		}
		else
			delay_ms(1);
	}
	
	//Working Point To Product Point
	for (process_step = 0; process_step < 3; ++process_step)
	{
		//QR Code Compare
		switch (QR_Code_Res[process_step]-'0')
		{
			case 1:
				aim_line_point = Working_Point_Take_Offset_Slow[Working_Point_Index[0]-1];
				aim_line_point.aim_position.x = Working_Point_Take_Middle.aim_position.x + Working_Point_Take_Offset_Slow[Working_Point_Index[0]-1].aim_position.x;
				aim_line_point.aim_position.y = Working_Point_Take_Middle.aim_position.y + Working_Point_Take_Offset_Slow[Working_Point_Index[0]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			case 2:
				aim_line_point = Working_Point_Take_Offset_Slow[Working_Point_Index[1]-1];
				aim_line_point.aim_position.x = Working_Point_Take_Middle.aim_position.x + Working_Point_Take_Offset_Slow[Working_Point_Index[1]-1].aim_position.x;
				aim_line_point.aim_position.y = Working_Point_Take_Middle.aim_position.y + Working_Point_Take_Offset_Slow[Working_Point_Index[1]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			case 3:
				aim_line_point = Working_Point_Take_Offset_Slow[Working_Point_Index[2]-1];
				aim_line_point.aim_position.x = Working_Point_Take_Middle.aim_position.x + Working_Point_Take_Offset_Slow[Working_Point_Index[2]-1].aim_position.x;
				aim_line_point.aim_position.y = Working_Point_Take_Middle.aim_position.y + Working_Point_Take_Offset_Slow[Working_Point_Index[2]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			default:
				break;
		}
		
		Show_Keyboard();
		POINT_COLOR=BLACK;
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Duty[0] = 50;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 13+1;
		Servo_Duty[3] = 27;
		Servo_PWM_SetDuty();
		delay_ms(500);
		
		aim_line_point = Working_Point_Take_Grab_Offset;
		aim_line_point.aim_position.x = GPS_List[0].position.x + Working_Point_Take_Grab_Offset.aim_position.x;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Working_Point_Take_Grab_Offset.aim_position.y;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Duty[0] = 50;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 13+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(500);
		
		Servo_Duty[0] = 32;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 14+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(500);
		
		Show_Keyboard();
		POINT_COLOR=BLACK;
		LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
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
				else
					break;
			}
			else
				delay_ms(1);
		}
		
		switch (QR_Code_Res[process_step]-'0')
		{
			case 1:
				aim_line_point = Product_Point_Offset_Slow[Product_Point_Index[0]-1];
				aim_line_point.aim_position.x = Product_Point_Middle.aim_position.x + Product_Point_Offset_Slow[Product_Point_Index[0]-1].aim_position.x;
				aim_line_point.aim_position.y = Product_Point_Middle.aim_position.y + Product_Point_Offset_Slow[Product_Point_Index[0]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			case 2:
				aim_line_point = Product_Point_Offset_Slow[Product_Point_Index[1]-1];
				aim_line_point.aim_position.x = Product_Point_Middle.aim_position.x + Product_Point_Offset_Slow[Product_Point_Index[1]-1].aim_position.x;
				aim_line_point.aim_position.y = Product_Point_Middle.aim_position.y + Product_Point_Offset_Slow[Product_Point_Index[1]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			case 3:
				aim_line_point = Product_Point_Offset_Slow[Product_Point_Index[2]-1];
				aim_line_point.aim_position.x = Product_Point_Middle.aim_position.x + Product_Point_Offset_Slow[Product_Point_Index[2]-1].aim_position.x;
				aim_line_point.aim_position.y = Product_Point_Middle.aim_position.y + Product_Point_Offset_Slow[Product_Point_Index[2]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			default:
				break;
		}
		Show_Keyboard();
		POINT_COLOR=BLACK;
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Duty[0] = 30;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 14+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(500);
		
		Camera_Set_Mode(5);
		check_cnt_no_zero = 0;
		check_cnt_zero = 0;
		check_point_offset.y = 0;
		Product_Calibration_Sign = 0;
		while (1)
		{
			if (Product_Calibration_Sign)
			{
				if (Camera_RxBuffer[0] == 0)
					++check_cnt_zero;
				else
				{
					check_point_offset.y = (check_point_offset.y * check_cnt_no_zero + Camera_RxBuffer[0]) / (check_cnt_no_zero + 1);
					++check_cnt_no_zero;
				}
				Product_Calibration_Sign = 0;
			}
			if (check_cnt_no_zero == 5)
			{
				aim_line_point.aim_position.y = GPS_List[0].position.y + (check_point_offset.y - Product_Point_Camera[0]) * Camera_Pixel_To_Distance[0];
				break;
			}
			else if (check_cnt_zero == 10)
			{
				aim_line_point.aim_position.y = GPS_List[0].position.y;
				break;
			}
		}
		
		Camera_Set_Mode(6);
		check_cnt_no_zero = 0;
		check_cnt_zero = 0;
		check_point_offset.x = 0;
		Product_Calibration_Sign = 0;
		while (1)
		{
			if (Product_Calibration_Sign)
			{
				if (Camera_RxBuffer[0] == 0)
					++check_cnt_zero;
				else
				{
					check_point_offset.x = (check_point_offset.x * check_cnt_no_zero + Camera_RxBuffer[0]) / (check_cnt_no_zero + 1);
					++check_cnt_no_zero;
				}
				Product_Calibration_Sign = 0;
			}
			if (check_cnt_no_zero == 5)
			{
				aim_line_point.aim_position.x = GPS_List[0].position.x + (check_point_offset.x - Product_Point_Camera[1]) * Camera_Pixel_To_Distance[1];
				break;
			}
			else if (check_cnt_zero == 10)
			{
				aim_line_point.aim_position.x = GPS_List[0].position.x;
				break;
			}
		}
		
		aim_line_point.aim_radian = GPS_List[0].radian;
		aim_line_point.pid_list_index = 4;
		aim_line_point.rotation_dir = -1;
		aim_line_point.speed_sta = 30;
		aim_line_point.speed_max = 50;
		aim_line_point.speed_end = 30;
		
		Show_Keyboard();
		POINT_COLOR=BLACK;
		aim_line_point.aim_radian = GPS_List[0].radian;
		aim_line_point.pid_list_index = 4;
		aim_line_point.rotation_dir = -1;
		aim_line_point.speed_sta = 30;
		aim_line_point.speed_max = 50;
		aim_line_point.speed_end = 30;
		
		Show_Keyboard();
		POINT_COLOR=BLACK;
		while (1)
		{
			LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
			LCD_printf(0,6+36*1,300,24,24,"X:%lf",GPS_List[0].position.x);
			LCD_printf(0,6+36*2,300,24,24,"Y:%lf",GPS_List[0].position.y);
			LCD_printf(0,6+36*3,300,24,24,"Angle:%lf",GPS_List[0].angle);
			LCD_printf(0,6+36*4,300,24,24,"Aim_X:%lf",aim_line_point.aim_position.x);
			LCD_printf(0,6+36*5,300,24,24,"Aim_Y:%lf",aim_line_point.aim_position.y);
			LCD_printf(0,6+36*6,300,24,24,"Dis_X:%lf",check_point_offset.x);
			LCD_printf(0,6+36*7,300,24,24,"Dis_Y:%lf",check_point_offset.y);
			
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
				else
					break;
			}
			else
				delay_ms(1);
		}
		
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 3.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Duty[0] = 30;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 13+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(500);
		
		Servo_Duty[0] = 30;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 13+1;
		Servo_Duty[3] = 27;
		Servo_PWM_SetDuty();
		delay_ms(250);
		
		aim_line_point = Product_Point_Leave_Offset;
		aim_line_point.aim_position.x = GPS_List[0].position.x + Product_Point_Leave_Offset.aim_position.x;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Product_Point_Leave_Offset.aim_position.y;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		if (process_step != 2)
		{			
			Servo_Duty[0] = 48;
			Servo_Duty[1] = 33;
			Servo_Duty[2] = 13+1;
			Servo_Duty[3] = 27;
			Servo_PWM_SetDuty();
			delay_ms(500);
		}
		
		Show_Keyboard();
		POINT_COLOR=BLACK;
		LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
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
				else
					break;
			}
			else
				delay_ms(1);
		}
	}
	
	aim_line_point = Original_Point;
	SetLine(&aim_line_point);
	Show_Keyboard();
	POINT_COLOR=BLACK;
	while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 20.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
			/*	case keyback:
					SPEED_STOP;
					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
					return;	*/
				default:
					break;
			}
		}
	}
	SPEED_STOP;
	SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
	
	Servo_Duty[0] = 30;
	Servo_Duty[1] = 36;
	Servo_Duty[2] = 50;
	Servo_Duty[3] = 39;
	Servo_PWM_SetDuty();
	
	delay_ms(500);
	
	Servo_Duty[0] = 10;
	Servo_Duty[1] = 36;
	Servo_Duty[2] = 50;
	Servo_Duty[3] = 39;
	Servo_PWM_SetDuty();
}

void process_Auto(u8 auto_cnt)
{
	struct Line_Point aim_line_point;
	u8 tp_last, key_value, is_key = 0;
	u8 process_step = 0;
	u16 t;
	u8 check_cnt_no_zero = 0, check_cnt_zero = 0;
	struct Point check_point_offset;
	
	if (!(auto_cnt == 0 || auto_cnt == 1))
		return;
	
	GPS_Offset = process_GPS_Offset[auto_cnt];
	delay_ms(100);
	
	Show_Keyboard();
/*	LCD_printf(0,6+36*0,300,24,24,"Be sure Raspberry Pi is OK");
	LCD_printf(0,6+36*1,300,24,24,"Be sure Cameras are OK");
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
			else
				break;
		}
		else
			delay_ms(1);
	}*/
	
	Camera_Set_Mode(8);
	
/*	//Waiting for Working Index
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"1.R G B: Working L->R");
	LCD_printf(0,6+36*1,300,24,24,"2.R B G: Working L->R");
	LCD_printf(0,6+36*2,300,24,24,"3.G R B: Working L->R");
	LCD_printf(0,6+36*3,300,24,24,"4.G B R: Working L->R");
	LCD_printf(0,6+36*4,300,24,24,"5.B R G: Working L->R");
	LCD_printf(0,6+36*5,300,24,24,"6.B G R: Working L->R");
	LCD_printf(0,6+36*6,300,24,24,"Press key to choose index");
	
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
			if (key_value == key1)
			{
				Working_Point_Index[0] = 1;
				Working_Point_Index[1] = 2;
				Working_Point_Index[2] = 3;
				break;
			}
			else if (key_value == key2)
			{
				Working_Point_Index[0] = 1;
				Working_Point_Index[1] = 3;
				Working_Point_Index[2] = 2;
				break;
			}
			else if (key_value == key3)
			{
				Working_Point_Index[0] = 2;
				Working_Point_Index[1] = 1;
				Working_Point_Index[2] = 3;
				break;
			}
			else if (key_value == key4)
			{
				Working_Point_Index[0] = 3;
				Working_Point_Index[1] = 1;
				Working_Point_Index[2] = 2;
				break;
			}
			else if (key_value == key5)
			{
				Working_Point_Index[0] = 2;
				Working_Point_Index[1] = 3;
				Working_Point_Index[2] = 1;
				break;
			}
			else if (key_value == key6)
			{
				Working_Point_Index[0] = 3;
				Working_Point_Index[1] = 2;
				Working_Point_Index[2] = 1;
				break;
			}
			else if (key_value == keyback)
				return;
		}
		else
			delay_ms(1);
	}
	
	//Waiting for Working Index
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"1.R G B: Product D->U");
	LCD_printf(0,6+36*1,300,24,24,"2.R B G: Product D->U");
	LCD_printf(0,6+36*2,300,24,24,"3.G R B: Product D->U");
	LCD_printf(0,6+36*3,300,24,24,"4.G B R: Product D->U");
	LCD_printf(0,6+36*4,300,24,24,"5.B R G: Product D->U");
	LCD_printf(0,6+36*5,300,24,24,"6.B G R: Product D->U");
	LCD_printf(0,6+36*6,300,24,24,"Press key to choose index");
	
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
			if (key_value == key1)
			{
				Product_Point_Index[0] = 1;
				Product_Point_Index[1] = 2;
				Product_Point_Index[2] = 3;
				break;
			}
			else if (key_value == key2)
			{
				Product_Point_Index[0] = 1;
				Product_Point_Index[1] = 3;
				Product_Point_Index[2] = 2;
				break;
			}
			else if (key_value == key3)
			{
				Product_Point_Index[0] = 2;
				Product_Point_Index[1] = 1;
				Product_Point_Index[2] = 3;
				break;
			}
			else if (key_value == key4)
			{
				Product_Point_Index[0] = 3;
				Product_Point_Index[1] = 1;
				Product_Point_Index[2] = 2;
				break;
			}
			else if (key_value == key5)
			{
				Product_Point_Index[0] = 2;
				Product_Point_Index[1] = 3;
				Product_Point_Index[2] = 1;
				break;
			}
			else if (key_value == key6)
			{
				Product_Point_Index[0] = 3;
				Product_Point_Index[1] = 2;
				Product_Point_Index[2] = 1;
				break;
			}
			else if (key_value == keyback)
				return;
		}
		else
			delay_ms(1);
	}*/
	
	Camera_Set_Mode(0);
	//Color Check Point
	POINT_COLOR=BLACK;
	aim_line_point = Color_Check_Point;
	SetLine(&aim_line_point);
	while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
			/*	case keyback:
					SPEED_STOP;
					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
					return;	*/
				default:
					break;
			}
		}
	}
	SPEED_STOP;
	SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
	
	Camera_Set_Mode(128);
	Camera_Set_Mode(1);
	t = 0;
	while (1)
	{
	/*	LCD_printf(0,6+36*0,300,24,24,"QR Code:0x%02X 0x%02X 0x%02X",QR_Code_Res[0],QR_Code_Res[1],QR_Code_Res[2]);
		LCD_printf(0,6+36*1,300,24,24,"Color Res:%u %u %u",Color_Res[0],Color_Res[1],Color_Res[2]);	*/
		if (Is_Color_Finished)
			break;
		else
		{
			delay_ms(1);
			++t;
			if (t == 1000)
				Camera_Set_Mode(1);
		}
	}
	
	//Color Check Waiting
/*	Show_Keyboard();
	POINT_COLOR=BLACK;
	while (1)
	{
		LCD_printf(0,6+36*0,300,24,24,"QR Code:0x%02X 0x%02X 0x%02X",QR_Code_Res[0],QR_Code_Res[1],QR_Code_Res[2]);
		LCD_printf(0,6+36*1,300,24,24,"Color Res:%u %u %u",Color_Res[0],Color_Res[1],Color_Res[2]);
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
			else
				break;
		}
		else
			delay_ms(1);
	}*/
	
	//QR Code Point 0
	POINT_COLOR=BLACK;
	aim_line_point = QR_Code_Point[0];
	SetLine(&aim_line_point);
	while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 20.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
			/*	case keyback:
					SPEED_STOP;
					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
					return;	*/
				default:
					break;
			}
		}
	}
	SPEED_STOP;
	SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
	
	Servo_Duty[0] = 12;
	Servo_Duty[1] = 50;
	Servo_Duty[2] = 33+1;
	Servo_Duty[3] = 27;
	Servo_PWM_SetDuty();
	delay_ms(300);
	
	//QR Code Check
	QR_Code_RX_Finish = 0;
	DMA_SetCurrDataCounter(USART3_DMA_TX_STREAM, QR_Code_TxBufferSize);
	DMA_Cmd(USART3_DMA_TX_STREAM, ENABLE);
	while (1)
	{
		if (QR_Code_RX_Finish)
		{
			if (QR_Code_Res[0] >= '1' && QR_Code_Res[0] <= '3' && 
				QR_Code_Res[1] >= '1' && QR_Code_Res[1] <= '3' && 
				QR_Code_Res[2] >= '1' && QR_Code_Res[2] <= '3')
				break;
			else
			{
				QR_Code_RX_Finish = 0;
				DMA_SetCurrDataCounter(USART3_DMA_TX_STREAM, QR_Code_TxBufferSize);
				DMA_Cmd(USART3_DMA_TX_STREAM, ENABLE);
			}
		}
	}
	
	process_Show_QR_Code(48*0,6+36*0,QR_Code_Res[0]);
	process_Show_QR_Code(48*1,6+36*0,QR_Code_Res[1]);
	process_Show_QR_Code(48*2,6+36*0,QR_Code_Res[2]);
	
	//QR Code Check Waiting
/*	Show_Keyboard();
	POINT_COLOR=BLACK;
	while (1)
	{
		LCD_printf(0,6+36*0,300,24,24,"QR Code:0x%02X 0x%02X 0x%02X",QR_Code_Res[0],QR_Code_Res[1],QR_Code_Res[2]);
		LCD_printf(0,6+36*1,300,24,24,"Color Res:%u %u %u",Color_Res[0],Color_Res[1],Color_Res[2]);
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
			else
				break;
		}
		else
			delay_ms(1);
	}*/
	
	
	//Stock Point To Working Point
	for (process_step = 0; process_step < 3; ++process_step)
	{
		//Color QR Code Compare
		switch (Color_Hash_Table[QR_Code_Res[process_step]-'0'-1])
		{
			case 1:
				if (!process_step)
				{
					aim_line_point = Stock_Point_Offset_Slow[0];
					aim_line_point.aim_position.x = Stock_Point_Middle.aim_position.x + Stock_Point_Offset_Slow[0].aim_position.x;
					aim_line_point.aim_position.y = Stock_Point_Middle.aim_position.y + Stock_Point_Offset_Slow[0].aim_position.y;
					SetLine(&aim_line_point);
				}
				else
				{
					aim_line_point = Stock_Point_Offset_Fast[0];
					aim_line_point.aim_position.x = Stock_Point_Middle.aim_position.x + Stock_Point_Offset_Fast[0].aim_position.x;
					aim_line_point.aim_position.y = Stock_Point_Middle.aim_position.y + Stock_Point_Offset_Fast[0].aim_position.y;
					SetLine(&aim_line_point);
				}
				break;
			case 2:
				if (!process_step)
				{
					aim_line_point = Stock_Point_Offset_Slow[1];
					aim_line_point.aim_position.x = Stock_Point_Middle.aim_position.x + Stock_Point_Offset_Slow[1].aim_position.x;
					aim_line_point.aim_position.y = Stock_Point_Middle.aim_position.y + Stock_Point_Offset_Slow[1].aim_position.y;
					SetLine(&aim_line_point);
				}
				else
				{
					aim_line_point = Stock_Point_Offset_Fast[1];
					aim_line_point.aim_position.x = Stock_Point_Middle.aim_position.x + Stock_Point_Offset_Fast[1].aim_position.x;
					aim_line_point.aim_position.y = Stock_Point_Middle.aim_position.y + Stock_Point_Offset_Fast[1].aim_position.y;
					SetLine(&aim_line_point);
				}
				break;
			case 3:
				if (!process_step)
				{
					aim_line_point = Stock_Point_Offset_Slow[2];
					aim_line_point.aim_position.x = Stock_Point_Middle.aim_position.x + Stock_Point_Offset_Slow[2].aim_position.x;
					aim_line_point.aim_position.y = Stock_Point_Middle.aim_position.y + Stock_Point_Offset_Slow[2].aim_position.y;
					SetLine(&aim_line_point);
				}
				else
				{
					aim_line_point = Stock_Point_Offset_Fast[2];
					aim_line_point.aim_position.x = Stock_Point_Middle.aim_position.x + Stock_Point_Offset_Fast[2].aim_position.x;
					aim_line_point.aim_position.y = Stock_Point_Middle.aim_position.y + Stock_Point_Offset_Fast[2].aim_position.y;
					SetLine(&aim_line_point);
				}
				break;
			default:
				break;
		}
		
		POINT_COLOR=BLACK;
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Duty[0] = 10;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 33+1;
		Servo_Duty[3] = 27;
		Servo_PWM_SetDuty();
		delay_ms(300);
		
		aim_line_point = Stock_Point_Grab_Offset;
		aim_line_point.aim_position.x = GPS_List[0].position.x + Stock_Point_Grab_Offset.aim_position.x;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Stock_Point_Grab_Offset.aim_position.y;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Duty[0] = 10;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 33+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(500);
		
		Servo_Duty[0] = 10;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 35+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(200);
		
		aim_line_point = Stock_Point_Leave_Offset;
		aim_line_point.aim_position.x = GPS_List[0].position.x + Stock_Point_Leave_Offset.aim_position.x;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Stock_Point_Leave_Offset.aim_position.y;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 15.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Duty[0] = 48;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 33+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(300);
		
	/*	Show_Keyboard();
		POINT_COLOR=BLACK;
		LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
		//Waiting for beginning signal
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
				else
					break;
			}
			else
				delay_ms(1);
		}*/
		
		switch (QR_Code_Res[process_step]-'0')
		{
			case 1:
				aim_line_point = Working_Point_Drop_Offset_Fast[Working_Point_Index[0]-1];
				aim_line_point.aim_position.x = Working_Point_Drop_Middle.aim_position.x + Working_Point_Drop_Offset_Fast[Working_Point_Index[0]-1].aim_position.x;
				aim_line_point.aim_position.y = Working_Point_Drop_Middle.aim_position.y + Working_Point_Drop_Offset_Fast[Working_Point_Index[0]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			case 2:
				aim_line_point = Working_Point_Drop_Offset_Fast[Working_Point_Index[1]-1];
				aim_line_point.aim_position.x = Working_Point_Drop_Middle.aim_position.x + Working_Point_Drop_Offset_Fast[Working_Point_Index[1]-1].aim_position.x;
				aim_line_point.aim_position.y = Working_Point_Drop_Middle.aim_position.y + Working_Point_Drop_Offset_Fast[Working_Point_Index[1]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			case 3:
				aim_line_point = Working_Point_Drop_Offset_Fast[Working_Point_Index[2]-1];
				aim_line_point.aim_position.x = Working_Point_Drop_Middle.aim_position.x + Working_Point_Drop_Offset_Fast[Working_Point_Index[2]-1].aim_position.x;
				aim_line_point.aim_position.y = Working_Point_Drop_Middle.aim_position.y + Working_Point_Drop_Offset_Fast[Working_Point_Index[2]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			default:
				break;
		}
		POINT_COLOR=BLACK;
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Duty[0] = 50;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 33+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(200);
		
		Servo_Duty[0] = 50;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 13+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(500);
		
		Servo_Duty[0] = 50;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 13+1;
		Servo_Duty[3] = 27;
		Servo_PWM_SetDuty();
		delay_ms(250);
		
		aim_line_point = Working_Point_Drop_Leave_Offset;
		aim_line_point.aim_position.x = GPS_List[0].position.x + Working_Point_Drop_Leave_Offset.aim_position.x;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Working_Point_Drop_Leave_Offset.aim_position.y;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 15.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		if (process_step != 2)
		{
			Servo_Duty[0] = 50;
			Servo_Duty[1] = 50;
			Servo_Duty[2] = 33+1;
			Servo_Duty[3] = 27;
			Servo_PWM_SetDuty();
			delay_ms(250);
			
			Servo_Duty[0] = 12;
			Servo_Duty[1] = 50;
			Servo_Duty[2] = 33+1;
			Servo_Duty[3] = 27;
			Servo_PWM_SetDuty();
			delay_ms(250);
		}
		
		//Waiting for beginning signal
	/*	while (1)
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
				else
					break;
			}
			else
				delay_ms(1);
		}*/
	}
	
	Servo_Duty[0] = 50;
	Servo_Duty[1] = 33;
	Servo_Duty[2] = 13+1;
	Servo_Duty[3] = 27;
	Servo_PWM_SetDuty();
	
	//QR Code Point 1
	POINT_COLOR=BLACK;
	aim_line_point = QR_Code_Point[1];
	SetLine(&aim_line_point);
	while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 20.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
//				case keyback:
//					SPEED_STOP;
//					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
//					return;
				default:
					break;
			}
		}
	}
	SPEED_STOP;
	SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
	
	Servo_Duty[0] = 48;
	Servo_Duty[1] = 33;
	Servo_Duty[2] = 13+1;
	Servo_Duty[3] = 27;
	Servo_PWM_SetDuty();
	
	//QR Code Check
	QR_Code_RX_Finish = 0;
	DMA_SetCurrDataCounter(USART3_DMA_TX_STREAM, QR_Code_TxBufferSize);
	DMA_Cmd(USART3_DMA_TX_STREAM, ENABLE);
	while (1)
	{
		if (QR_Code_RX_Finish)
		{
			if (QR_Code_Res[0] >= '1' && QR_Code_Res[0] <= '3' && 
				QR_Code_Res[1] >= '1' && QR_Code_Res[1] <= '3' && 
				QR_Code_Res[2] >= '1' && QR_Code_Res[2] <= '3')
				break;
			else
			{
				QR_Code_RX_Finish = 0;
				DMA_SetCurrDataCounter(USART3_DMA_TX_STREAM, QR_Code_TxBufferSize);
				DMA_Cmd(USART3_DMA_TX_STREAM, ENABLE);
			}
		}
	}
	
	process_Show_QR_Code(48*0,6+36*0,QR_Code_Res[0]);
	process_Show_QR_Code(48*1,6+36*0,QR_Code_Res[1]);
	process_Show_QR_Code(48*2,6+36*0,QR_Code_Res[2]);
	
/*	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
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
			else
				break;
		}
		else
			delay_ms(1);
	}*/
	
	//Working Point To Product Point
	for (process_step = 0; process_step < 3; ++process_step)
	{
		//QR Code Compare
		switch (QR_Code_Res[process_step]-'0')
		{
			case 1:
				aim_line_point = Working_Point_Take_Offset_Fast[Working_Point_Index[0]-1];
				aim_line_point.aim_position.x = Working_Point_Take_Middle.aim_position.x + Working_Point_Take_Offset_Fast[Working_Point_Index[0]-1].aim_position.x;
				aim_line_point.aim_position.y = Working_Point_Take_Middle.aim_position.y + Working_Point_Take_Offset_Fast[Working_Point_Index[0]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			case 2:
				aim_line_point = Working_Point_Take_Offset_Fast[Working_Point_Index[1]-1];
				aim_line_point.aim_position.x = Working_Point_Take_Middle.aim_position.x + Working_Point_Take_Offset_Fast[Working_Point_Index[1]-1].aim_position.x;
				aim_line_point.aim_position.y = Working_Point_Take_Middle.aim_position.y + Working_Point_Take_Offset_Fast[Working_Point_Index[1]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			case 3:
				aim_line_point = Working_Point_Take_Offset_Fast[Working_Point_Index[2]-1];
				aim_line_point.aim_position.x = Working_Point_Take_Middle.aim_position.x + Working_Point_Take_Offset_Fast[Working_Point_Index[2]-1].aim_position.x;
				aim_line_point.aim_position.y = Working_Point_Take_Middle.aim_position.y + Working_Point_Take_Offset_Fast[Working_Point_Index[2]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			default:
				break;
		}
		
		POINT_COLOR=BLACK;
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Duty[0] = 50;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 13+1;
		Servo_Duty[3] = 27;
		Servo_PWM_SetDuty();
		delay_ms(200);
		
		aim_line_point = Working_Point_Take_Grab_Offset;
		aim_line_point.aim_position.x = GPS_List[0].position.x + Working_Point_Take_Grab_Offset.aim_position.x;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Working_Point_Take_Grab_Offset.aim_position.y;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Duty[0] = 50;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 13+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(500);
		
		Servo_Duty[0] = 32;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 14+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(300);
		
	/*	Show_Keyboard();
		POINT_COLOR=BLACK;
		LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
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
				else
					break;
			}
			else
				delay_ms(1);
		}*/
		
		switch (QR_Code_Res[process_step]-'0')
		{
			case 1:
				aim_line_point = Product_Point_Offset_Slow[Product_Point_Index[0]-1];
				aim_line_point.aim_position.x = Product_Point_Middle.aim_position.x + Product_Point_Offset_Slow[Product_Point_Index[0]-1].aim_position.x;
				aim_line_point.aim_position.y = Product_Point_Middle.aim_position.y + Product_Point_Offset_Slow[Product_Point_Index[0]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			case 2:
				aim_line_point = Product_Point_Offset_Slow[Product_Point_Index[1]-1];
				aim_line_point.aim_position.x = Product_Point_Middle.aim_position.x + Product_Point_Offset_Slow[Product_Point_Index[1]-1].aim_position.x;
				aim_line_point.aim_position.y = Product_Point_Middle.aim_position.y + Product_Point_Offset_Slow[Product_Point_Index[1]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			case 3:
				aim_line_point = Product_Point_Offset_Slow[Product_Point_Index[2]-1];
				aim_line_point.aim_position.x = Product_Point_Middle.aim_position.x + Product_Point_Offset_Slow[Product_Point_Index[2]-1].aim_position.x;
				aim_line_point.aim_position.y = Product_Point_Middle.aim_position.y + Product_Point_Offset_Slow[Product_Point_Index[2]-1].aim_position.y;
				SetLine(&aim_line_point);
				break;
			default:
				break;
		}
		POINT_COLOR=BLACK;
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Duty[0] = 30;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 14+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(1000);
		
		Camera_Set_Mode(5);
		check_cnt_no_zero = 0;
		check_cnt_zero = 0;
		check_point_offset.y = 0;
		Product_Calibration_Sign = 0;
		while (1)
		{
			if (Product_Calibration_Sign)
			{
				if (Camera_RxBuffer[0] == 0)
					++check_cnt_zero;
				else
				{
					check_point_offset.y = (check_point_offset.y * check_cnt_no_zero + Camera_RxBuffer[0]) / (check_cnt_no_zero + 1);
					++check_cnt_no_zero;
				}
				Product_Calibration_Sign = 0;
			}
			if (check_cnt_no_zero == 3)
			{
				aim_line_point.aim_position.y = GPS_List[0].position.y + (check_point_offset.y - Product_Point_Camera[0]) * Camera_Pixel_To_Distance[0];
				break;
			}
			else if (check_cnt_zero == 6)
			{
				aim_line_point.aim_position.y = GPS_List[0].position.y;
				break;
			}
		}
		
		Camera_Set_Mode(6);
		check_cnt_no_zero = 0;
		check_cnt_zero = 0;
		check_point_offset.x = 0;
		Product_Calibration_Sign = 0;
		while (1)
		{
			if (Product_Calibration_Sign)
			{
				if (Camera_RxBuffer[0] == 0)
					++check_cnt_zero;
				else
				{
					check_point_offset.x = (check_point_offset.x * check_cnt_no_zero + Camera_RxBuffer[0]) / (check_cnt_no_zero + 1);
					++check_cnt_no_zero;
				}
				Product_Calibration_Sign = 0;
			}
			if (check_cnt_no_zero == 3)
			{
				aim_line_point.aim_position.x = GPS_List[0].position.x + (check_point_offset.x - Product_Point_Camera[1]) * Camera_Pixel_To_Distance[1];
				break;
			}
			else if (check_cnt_zero == 6)
			{
				aim_line_point.aim_position.x = GPS_List[0].position.x;
				break;
			}
		}
		
		aim_line_point.aim_radian = GPS_List[0].radian;
		aim_line_point.pid_list_index = 4;
		aim_line_point.rotation_dir = -1;
		aim_line_point.speed_sta = 30;
		aim_line_point.speed_max = 50;
		aim_line_point.speed_end = 30;
		
	/*	Show_Keyboard();
		POINT_COLOR=BLACK;
		while (1)
		{
			LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
			LCD_printf(0,6+36*1,300,24,24,"X:%lf",GPS_List[0].position.x);
			LCD_printf(0,6+36*2,300,24,24,"Y:%lf",GPS_List[0].position.y);
			LCD_printf(0,6+36*3,300,24,24,"Angle:%lf",GPS_List[0].angle);
			LCD_printf(0,6+36*4,300,24,24,"Aim_X:%lf",aim_line_point.aim_position.x);
			LCD_printf(0,6+36*5,300,24,24,"Aim_Y:%lf",aim_line_point.aim_position.y);
			LCD_printf(0,6+36*6,300,24,24,"Dis_X:%lf",check_dis_x);
			LCD_printf(0,6+36*7,300,24,24,"Dis_Y:%lf",check_dis_y);
			
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
				else
					break;
			}
			else
				delay_ms(1);
		}*/
		
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 3.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Duty[0] = 30;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 13+1;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
		delay_ms(300);
		
		Servo_Duty[0] = 30;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 13+1;
		Servo_Duty[3] = 27;
		Servo_PWM_SetDuty();
		delay_ms(250);
		
		aim_line_point = Product_Point_Leave_Offset;
		aim_line_point.aim_position.x = GPS_List[0].position.x + Product_Point_Leave_Offset.aim_position.x;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Product_Point_Leave_Offset.aim_position.y;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		if (process_step != 2)
		{			
			Servo_Duty[0] = 48;
			Servo_Duty[1] = 33;
			Servo_Duty[2] = 13+1;
			Servo_Duty[3] = 27;
			Servo_PWM_SetDuty();
			delay_ms(300);
		}
		
	/*	Show_Keyboard();
		POINT_COLOR=BLACK;
		LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
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
				else
					break;
			}
			else
				delay_ms(1);
		}*/
	}
	
	aim_line_point = Original_Point;
	SetLine(&aim_line_point);
	POINT_COLOR=BLACK;
	while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 20.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
			/*	case keyback:
					SPEED_STOP;
					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
					return;	*/
				default:
					break;
			}
		}
	}
	SPEED_STOP;
	SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
	
	Servo_Duty[0] = 30;
	Servo_Duty[1] = 36;
	Servo_Duty[2] = 50;
	Servo_Duty[3] = 39;
	Servo_PWM_SetDuty();
	delay_ms(500);
	
	Servo_Duty[0] = 10;
	Servo_Duty[1] = 36;
	Servo_Duty[2] = 50;
	Servo_Duty[3] = 39;
	Servo_PWM_SetDuty();
}

void process_Auto_RGB(void)
{
	u8 tp_last, key_value, is_key = 0;
	
	GPS_Clear();
	delay_ms(100);
	
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
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
			else
				break;
		}
		else
			delay_ms(1);
	}
	
	process_Auto(0);
	delay_ms(3000);
	process_Auto(1);
}

u8 process_CCD_Auto(u8 auto_cnt)
{
	struct Line_Point aim_line_point;
	u8 tp_last, key_value, is_key = 0;
	u8 process_step = 0;
	u8 k;
	u16 t;
	u8 check_cnt_no_zero = 0, check_cnt_zero = 0;
	u8 ccd_adjustment_sign = 0;
	struct Point check_point_offset;
	
	if (!(auto_cnt == 0 || auto_cnt == 1))
		return 1;
	
	GPS_Offset = process_GPS_Offset[auto_cnt];
	delay_ms(100);
	
	Show_Keyboard();
/*	LCD_printf(0,6+36*0,300,24,24,"Be sure Raspberry Pi is OK");
	LCD_printf(0,6+36*1,300,24,24,"Be sure Cameras are OK");
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
			else
				break;
		}
		else
			delay_ms(1);
	}*/
	
	Camera_Set_Mode(8);
	
/*	//Waiting for Working Index
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"1.R G B: Working L->R");
	LCD_printf(0,6+36*1,300,24,24,"2.R B G: Working L->R");
	LCD_printf(0,6+36*2,300,24,24,"3.G R B: Working L->R");
	LCD_printf(0,6+36*3,300,24,24,"4.G B R: Working L->R");
	LCD_printf(0,6+36*4,300,24,24,"5.B R G: Working L->R");
	LCD_printf(0,6+36*5,300,24,24,"6.B G R: Working L->R");
	LCD_printf(0,6+36*6,300,24,24,"Press key to choose index");
	
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
			if (key_value == key1)
			{
				Working_Point_Index[0] = 1;
				Working_Point_Index[1] = 2;
				Working_Point_Index[2] = 3;
				break;
			}
			else if (key_value == key2)
			{
				Working_Point_Index[0] = 1;
				Working_Point_Index[1] = 3;
				Working_Point_Index[2] = 2;
				break;
			}
			else if (key_value == key3)
			{
				Working_Point_Index[0] = 2;
				Working_Point_Index[1] = 1;
				Working_Point_Index[2] = 3;
				break;
			}
			else if (key_value == key4)
			{
				Working_Point_Index[0] = 3;
				Working_Point_Index[1] = 1;
				Working_Point_Index[2] = 2;
				break;
			}
			else if (key_value == key5)
			{
				Working_Point_Index[0] = 2;
				Working_Point_Index[1] = 3;
				Working_Point_Index[2] = 1;
				break;
			}
			else if (key_value == key6)
			{
				Working_Point_Index[0] = 3;
				Working_Point_Index[1] = 2;
				Working_Point_Index[2] = 1;
				break;
			}
			else if (key_value == keyback)
				return;
		}
		else
			delay_ms(1);
	}
	
	//Waiting for Working Index
	LCD_Clear(WHITE);
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"1.R G B: Product D->U");
	LCD_printf(0,6+36*1,300,24,24,"2.R B G: Product D->U");
	LCD_printf(0,6+36*2,300,24,24,"3.G R B: Product D->U");
	LCD_printf(0,6+36*3,300,24,24,"4.G B R: Product D->U");
	LCD_printf(0,6+36*4,300,24,24,"5.B R G: Product D->U");
	LCD_printf(0,6+36*5,300,24,24,"6.B G R: Product D->U");
	LCD_printf(0,6+36*6,300,24,24,"Press key to choose index");
	
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
			if (key_value == key1)
			{
				Product_Point_Index[0] = 1;
				Product_Point_Index[1] = 2;
				Product_Point_Index[2] = 3;
				break;
			}
			else if (key_value == key2)
			{
				Product_Point_Index[0] = 1;
				Product_Point_Index[1] = 3;
				Product_Point_Index[2] = 2;
				break;
			}
			else if (key_value == key3)
			{
				Product_Point_Index[0] = 2;
				Product_Point_Index[1] = 1;
				Product_Point_Index[2] = 3;
				break;
			}
			else if (key_value == key4)
			{
				Product_Point_Index[0] = 3;
				Product_Point_Index[1] = 1;
				Product_Point_Index[2] = 2;
				break;
			}
			else if (key_value == key5)
			{
				Product_Point_Index[0] = 2;
				Product_Point_Index[1] = 3;
				Product_Point_Index[2] = 1;
				break;
			}
			else if (key_value == key6)
			{
				Product_Point_Index[0] = 3;
				Product_Point_Index[1] = 2;
				Product_Point_Index[2] = 1;
				break;
			}
			else if (key_value == keyback)
				return;
		}
		else
			delay_ms(1);
	}*/
	
	Camera_Set_Mode(0);
	//Color Check Point
	POINT_COLOR=BLACK;
	aim_line_point = Color_Check_Point;
	SetLine(&aim_line_point);
	while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
			/*	case keyback:
					SPEED_STOP;
					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
					return;	*/
				default:
					break;
			}
		}
	}
	SPEED_STOP;
	SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
	
	Camera_Set_Mode(128);
	Camera_Set_Mode(1);
	t = 0;
	while (1)
	{
	/*	LCD_printf(0,6+36*0,300,24,24,"QR Code:0x%02X 0x%02X 0x%02X",QR_Code_Res[0],QR_Code_Res[1],QR_Code_Res[2]);
		LCD_printf(0,6+36*1,300,24,24,"Color Res:%u %u %u",Color_Res[0],Color_Res[1],Color_Res[2]);	*/
		if (Is_Color_Finished)
			break;
		else
		{
			delay_ms(1);
			++t;
			if (t == 1000)
				Camera_Set_Mode(1);
		}
	}
	
	//Color Check Waiting
	Show_Keyboard();
	POINT_COLOR=BLACK;
	while (1)
	{
		LCD_printf(0,6+36*0,300,24,24,"QR Code:0x%02X 0x%02X 0x%02X",QR_Code_Res[0],QR_Code_Res[1],QR_Code_Res[2]);
		LCD_printf(0,6+36*1,300,24,24,"Color Res:%u %u %u",Color_Res[0],Color_Res[1],Color_Res[2]);
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
				return 2;
			else
				break;
		}
		else
			delay_ms(1);
	}
	
	Servo_QR_Code_Stretch();
	delay_ms(200);
	
	Servo_Intense_Index = Color_Res[0] - 1;
	
	process_Show_QR_Code(48*0,6+36*0,WIFI_Res_1[0]);
	process_Show_QR_Code(48*1,6+36*0,WIFI_Res_1[1]);
	process_Show_QR_Code(48*2,6+36*0,WIFI_Res_1[2]);
	
	//QR Code Check Waiting
/*	Show_Keyboard();
	POINT_COLOR=BLACK;
	while (1)
	{
		LCD_printf(0,6+36*0,300,24,24,"QR Code:0x%02X 0x%02X 0x%02X",QR_Code_Res[0],QR_Code_Res[1],QR_Code_Res[2]);
		LCD_printf(0,6+36*1,300,24,24,"Color Res:%u %u %u",Color_Res[0],Color_Res[1],Color_Res[2]);
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
			else
				break;
		}
		else
			delay_ms(1);
	}*/
	
	
	//Stock Point To Working Point
	for (process_step = 0; process_step < 3; ++process_step)
	{
		if (!process_step)
		{
			aim_line_point = Stock_Point_CCD_Middle_Slow;
			SetLine(&aim_line_point);
		}
		else
		{
			aim_line_point = Stock_Point_CCD_Middle_Fast;
			SetLine(&aim_line_point);
		}
		
		POINT_COLOR=BLACK;
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		TSL1401_SetEnabled(1);
		
		delay_ms(500);
		while (!TSL1401_Cal_Ready);
		TSL1401_Measure(!TSL1401_Is_Find_ADC_Threshold);
		
		while (1)
		{
			LCD_printf(0,6+36*1,300,24,24,"Press any key to start 1");
			LCD_printf(0,6+36*2,300,24,24,"Edge Type:%u %u %u %u",TSL1401_State[0].Line_Edge_Type,TSL1401_State[1].Line_Edge_Type,TSL1401_State[2].Line_Edge_Type,TSL1401_State[3].Line_Edge_Type);
			LCD_printf(0,6+36*3,300,24,24,"Mpos:%u %u %u %u",TSL1401_State[0].Line_Edge_Median_Pos,TSL1401_State[1].Line_Edge_Median_Pos,TSL1401_State[2].Line_Edge_Median_Pos,TSL1401_State[3].Line_Edge_Median_Pos);
			
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
				{
					TSL1401_SetEnabled(0);
					return 2;
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
		switch (TSL1401_State[3].Line_Edge_Type)
		{
			case 0:
				ccd_adjustment_sign &= ~(2 << 6);
				ccd_adjustment_sign |= (0 << 6);
				break;
			case 1:
				ccd_adjustment_sign &= ~(2 << 6);
				ccd_adjustment_sign |= (1 << 6);
				aim_line_point.aim_position.x = GPS_List[0].position.x + Stock_Point_CCD_Line[1].Line_Move_Offset[0].x;
				SetLine(&aim_line_point);
				break;
			case 2:
				ccd_adjustment_sign &= ~(2 << 6);
				ccd_adjustment_sign |= (2 << 6);
				aim_line_point.aim_position.y = GPS_List[0].position.y + Stock_Point_CCD_Line[1].Line_Move_Offset[0].y;
				SetLine(&aim_line_point);
				break;
		}
		if (ccd_adjustment_sign)
		{
			while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
					/*	case keyback:
							SPEED_STOP;
							SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
							return;	*/
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
				{
					TSL1401_SetEnabled(0);
					return 2;
				}
				else
					break;
			}
			else
				delay_ms(1);
		}
		
		k = Color_Hash_Table[WIFI_Res_1[process_step]-'0'-1] - 1;
		aim_line_point = Stock_Point_CCD_Middle_Offset[k];
		aim_line_point.aim_position.x = GPS_List[0].position.x + Stock_Point_CCD_Middle_Offset[k].aim_position.x;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Stock_Point_CCD_Middle_Offset[k].aim_position.y + (TSL1401_State[3].Line_Edge_Median_Pos - Stock_Point_CCD_Line[1].Line_Edge_Median_Pos[3]) * TSL1401_State[3].Pixel_To_Distance;
		SetLine(&aim_line_point);
		
		TSL1401_SetEnabled(0);
		
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 5.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Stock_Point_Grab_Off_Panpilt_Straight();
		delay_ms(300);
		
		aim_line_point = Stock_Point_CCD_Grab_Offset;
		aim_line_point.aim_position.x = GPS_List[0].position.x + Stock_Point_CCD_Grab_Offset.aim_position.x;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Stock_Point_CCD_Grab_Offset.aim_position.y;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		k = Color_Hash_Table[WIFI_Res_1[process_step]-'0'-1] - 1;
		Servo_Stock_Point_Grab_On_Panpilt_Straight(k);
		delay_ms(300);
		
		k = Color_Hash_Table[WIFI_Res_1[process_step]-'0'-1] - 1;
		Servo_Stock_Point_Grab_On_Panpilt_Straight_Lift(k);
		delay_ms(200);
		
		aim_line_point = Stock_Point_CCD_Leave_Offset;
		aim_line_point.aim_position.x = GPS_List[0].position.x + Stock_Point_CCD_Leave_Offset.aim_position.x;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Stock_Point_CCD_Leave_Offset.aim_position.y;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		aim_line_point = Working_Point_Drop_CCD_Middle_Fast;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 20.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		TSL1401_SetEnabled(1);
		
		delay_ms(500);
		while (!TSL1401_Cal_Ready);
		TSL1401_Measure(!TSL1401_Is_Find_ADC_Threshold);
		
		while (1)
		{
			LCD_printf(0,6+36*1,300,24,24,"Press any key to start 1");
			LCD_printf(0,6+36*2,300,24,24,"Edge Type:%u %u %u %u",TSL1401_State[0].Line_Edge_Type,TSL1401_State[1].Line_Edge_Type,TSL1401_State[2].Line_Edge_Type,TSL1401_State[3].Line_Edge_Type);
			LCD_printf(0,6+36*3,300,24,24,"Mpos:%u %u %u %u",TSL1401_State[0].Line_Edge_Median_Pos,TSL1401_State[1].Line_Edge_Median_Pos,TSL1401_State[2].Line_Edge_Median_Pos,TSL1401_State[3].Line_Edge_Median_Pos);
			
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
				{
					TSL1401_SetEnabled(0);
					return 2;
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
		switch (TSL1401_State[1].Line_Edge_Type)
		{
			case 0:
				ccd_adjustment_sign &= ~(2 << 2);
				ccd_adjustment_sign |= (0 << 2);
				break;
			case 1:
				ccd_adjustment_sign &= ~(2 << 2);
				ccd_adjustment_sign |= (1 << 2);
				aim_line_point.aim_position.y = GPS_List[0].position.y + Working_Point_Drop_CCD_Line[1].Line_Move_Offset[1].y;
				SetLine(&aim_line_point);
				break;
			case 2:
				ccd_adjustment_sign &= ~(2 << 2);
				ccd_adjustment_sign |= (2 << 2);
				aim_line_point.aim_position.x = GPS_List[0].position.x + Working_Point_Drop_CCD_Line[1].Line_Move_Offset[1].x;
				SetLine(&aim_line_point);
				break;
		}
		switch (TSL1401_State[2].Line_Edge_Type)
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
					aim_line_point.aim_position.x = GPS_List[0].position.x + Working_Point_Drop_CCD_Line[1].Line_Move_Offset[2].x;
					SetLine(&aim_line_point);
				}
				break;
			case 2:
				ccd_adjustment_sign &= ~(2 << 4);
				ccd_adjustment_sign |= (1 << 4);
				if ((ccd_adjustment_sign & 2) != 1)
				{
					aim_line_point.aim_position.y = GPS_List[0].position.y + Working_Point_Drop_CCD_Line[1].Line_Move_Offset[2].y;
					SetLine(&aim_line_point);
				}
				break;
		}
		if (ccd_adjustment_sign)
		{
			while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
					/*	case keyback:
							SPEED_STOP;
							SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
							return;	*/
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
				{
					TSL1401_SetEnabled(0);
					return 2;
				}
				else
					break;
			}
			else
				delay_ms(1);
		}
		
		k = Working_Point_Index[WIFI_Res_1[process_step]-'0' - 1] - 1;
		aim_line_point = Working_Point_Drop_CCD_Middle_Offset[k];
		aim_line_point.aim_position.x = GPS_List[0].position.x + Working_Point_Drop_CCD_Middle_Offset[k].aim_position.x - (Working_Point_Drop_CCD_Line[1].Line_Edge_Median_Pos[1] - TSL1401_State[1].Line_Edge_Median_Pos) * TSL1401_State[1].Pixel_To_Distance;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Working_Point_Drop_CCD_Middle_Offset[k].aim_position.y + (Working_Point_Drop_CCD_Line[1].Line_Edge_Median_Pos[2] - TSL1401_State[2].Line_Edge_Median_Pos) * TSL1401_State[2].Pixel_To_Distance;;
		SetLine(&aim_line_point);
		
		TSL1401_SetEnabled(0);
		
		k = Working_Point_Index[WIFI_Res_1[process_step]-'0' - 1] - 1;
		Servo_Working_Point_Grab_On_High_Panpilt_Skew(k);
		delay_ms(300);
		
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
	/*	Show_Keyboard();
		POINT_COLOR=BLACK;
		LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
		//Waiting for beginning signal
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
				else
					break;
			}
			else
				delay_ms(1);
		}*/
		
		k = Working_Point_Index[WIFI_Res_1[process_step]-'0' - 1] - 1;
		Servo_Working_Point_Grab_On_High_Panpilt_Straight(k);
		delay_ms(200);
		
		k = Working_Point_Index[WIFI_Res_1[process_step]-'0' - 1] - 1;
		Servo_Working_Point_Grab_On_Low_Panpilt_Straight(k);
		delay_ms(400);
		
		Servo_Working_Point_Grab_Off_Low_Panpilt_Straight();
		delay_ms(300);
		
		k = Working_Point_Index[WIFI_Res_1[process_step]-'0' - 1] - 1;
		Working_Point_Take_CCD_Slow[k].aim_position.x = Working_Point_Take_CCD_Fast[k].aim_position.x = GPS_List[0].position.x;
		Working_Point_Take_CCD_Slow[k].aim_position.y = Working_Point_Take_CCD_Fast[k].aim_position.y = GPS_List[0].position.y - 80;
		
		aim_line_point = Working_Point_Drop_CCD_Leave_Offset;
		aim_line_point.aim_position.x = GPS_List[0].position.x + Working_Point_Drop_CCD_Leave_Offset.aim_position.x;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Working_Point_Drop_CCD_Leave_Offset.aim_position.y;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 20.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		if (process_step != 2)
		{
			Servo_Working_Point_Grab_Off_High_Panpilt_Straight();
			delay_ms(250);
			
			Servo_Stock_Point_Grab_Off_Panpilt_Skew();
			delay_ms(250);
		}
		
		//Waiting for beginning signal
	/*	while (1)
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
				else
					break;
			}
			else
				delay_ms(1);
		}*/
	}
	
	Servo_Working_Point_Grab_Off_Middle_Panpilt_Skew();
	
	process_Show_QR_Code(48*0,6+36*0,WIFI_Res_2[0]);
	process_Show_QR_Code(48*1,6+36*0,WIFI_Res_2[1]);
	process_Show_QR_Code(48*2,6+36*0,WIFI_Res_2[2]);
	
/*	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
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
			else
				break;
		}
		else
			delay_ms(1);
	}*/
	
	//Working Point To Product Point
	for (process_step = 0; process_step < 3; ++process_step)
	{
		//QR Code Compare		
		k = Working_Point_Index[WIFI_Res_2[process_step]-'0' - 1]-1;
		if (!process_step)
		{
			aim_line_point = Working_Point_Take_CCD_Slow[k];
			SetLine(&aim_line_point);
		}
		else
		{
			aim_line_point = Working_Point_Take_CCD_Fast[k];
			SetLine(&aim_line_point);
		}
		
		POINT_COLOR=BLACK;
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		Servo_Working_Point_Grab_Off_Down_Panpilt_Straight();
		delay_ms(200);
		
		aim_line_point = Working_Point_Take_CCD_Grab_Offset;
		aim_line_point.aim_position.x = GPS_List[0].position.x + Working_Point_Take_CCD_Grab_Offset.aim_position.x;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Working_Point_Take_CCD_Grab_Offset.aim_position.y;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		k = Working_Point_Index[WIFI_Res_2[process_step]-'0' - 1]-1;
		Servo_Working_Point_Grab_On_Down_Panpilt_Straight(k);
		delay_ms(300);
		
		aim_line_point = Trans;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 20.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
	/*	Show_Keyboard();
		POINT_COLOR=BLACK;
		LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
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
				else
					break;
			}
			else
				delay_ms(1);
		}*/
		
		k = Working_Point_Index[WIFI_Res_2[process_step]-'0' - 1]-1;
		aim_line_point = Product_Point_CCD_Middle_Fast;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		k = Working_Point_Index[WIFI_Res_2[process_step]-'0' - 1]-1;
		Servo_Product_Point_Grab_On_Middle_Panpilt_Skew(k);
		delay_ms(300);
		
		TSL1401_SetEnabled(1);
		
		delay_ms(500);
		while (!TSL1401_Cal_Ready);
		TSL1401_Measure(!TSL1401_Is_Find_ADC_Threshold);
		
		while (1)
		{
			LCD_printf(0,6+36*1,300,24,24,"Press any key to start 1");
			LCD_printf(0,6+36*2,300,24,24,"Edge Type:%u %u %u %u",TSL1401_State[0].Line_Edge_Type,TSL1401_State[1].Line_Edge_Type,TSL1401_State[2].Line_Edge_Type,TSL1401_State[3].Line_Edge_Type);
			LCD_printf(0,6+36*3,300,24,24,"Mpos:%u %u %u %u",TSL1401_State[0].Line_Edge_Median_Pos,TSL1401_State[1].Line_Edge_Median_Pos,TSL1401_State[2].Line_Edge_Median_Pos,TSL1401_State[3].Line_Edge_Median_Pos);
			
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
				{
					TSL1401_SetEnabled(0);
					return 2;
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
		switch (TSL1401_State[1].Line_Edge_Type)
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
		}
		switch (TSL1401_State[2].Line_Edge_Type)
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
		}
		if (ccd_adjustment_sign)
		{
			while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
					/*	case keyback:
							SPEED_STOP;
							SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
							return;	*/
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
				{
					TSL1401_SetEnabled(0);
					return 2;
				}
				else
					break;
			}
			else
				delay_ms(1);
		}
		
		k = Product_Point_Index[WIFI_Res_2[process_step]-'0' - 1] - 1;
		aim_line_point = Product_Point_CCD_Middle_Offset[k];
		aim_line_point.aim_position.x = GPS_List[0].position.x + Product_Point_CCD_Middle_Offset[k].aim_position.x - (Product_Point_CCD_Line[1].Line_Edge_Median_Pos[1] - TSL1401_State[1].Line_Edge_Median_Pos) * TSL1401_State[1].Pixel_To_Distance;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Product_Point_CCD_Middle_Offset[k].aim_position.y + (Product_Point_CCD_Line[1].Line_Edge_Median_Pos[2] - TSL1401_State[2].Line_Edge_Median_Pos) * TSL1401_State[2].Pixel_To_Distance;
		SetLine(&aim_line_point);
		
		TSL1401_SetEnabled(0);
		
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		k = Product_Point_Index[WIFI_Res_2[process_step]-'0' - 1] - 1;
		Servo_Product_Point_Grab_On_Middle_Panpilt_Straight(k);
		delay_ms(500);
		
		Camera_Set_Mode(5);
		check_cnt_no_zero = 0;
		check_cnt_zero = 0;
		check_point_offset.y = 0;
		Product_Calibration_Sign = 0;
		while (1)
		{
			if (Product_Calibration_Sign)
			{
				if (Camera_RxBuffer[0] == 0)
					++check_cnt_zero;
				else
				{
					check_point_offset.y = (check_point_offset.y * check_cnt_no_zero + Camera_RxBuffer[0]) / (check_cnt_no_zero + 1);
					++check_cnt_no_zero;
				}
				Product_Calibration_Sign = 0;
			}
			if (check_cnt_no_zero == 3)
			{
				aim_line_point.aim_position.y = GPS_List[0].position.y + (check_point_offset.y - Product_Point_Camera[0]) * Camera_Pixel_To_Distance[0];
				break;
			}
			else if (check_cnt_zero == 6)
			{
				aim_line_point.aim_position.y = GPS_List[0].position.y;
				break;
			}
		}
		
		Camera_Set_Mode(6);
		check_cnt_no_zero = 0;
		check_cnt_zero = 0;
		check_point_offset.x = 0;
		Product_Calibration_Sign = 0;
		while (1)
		{
			if (Product_Calibration_Sign)
			{
				if (Camera_RxBuffer[0] == 0)
					++check_cnt_zero;
				else
				{
					check_point_offset.x = (check_point_offset.x * check_cnt_no_zero + Camera_RxBuffer[0]) / (check_cnt_no_zero + 1);
					++check_cnt_no_zero;
				}
				Product_Calibration_Sign = 0;
			}
			if (check_cnt_no_zero == 3)
			{
				aim_line_point.aim_position.x = GPS_List[0].position.x + (check_point_offset.x - Product_Point_Camera[1]) * Camera_Pixel_To_Distance[1];
				break;
			}
			else if (check_cnt_zero == 6)
			{
				aim_line_point.aim_position.x = GPS_List[0].position.x;
				break;
			}
		}
		
		aim_line_point.aim_radian = GPS_List[0].radian;
		aim_line_point.pid_list_index = 4;
		aim_line_point.rotation_dir = -1;
		aim_line_point.speed_sta = 30;
		aim_line_point.speed_max = 50;
		aim_line_point.speed_end = 30;
		
	/*	Show_Keyboard();
		POINT_COLOR=BLACK;
		while (1)
		{
			LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
			LCD_printf(0,6+36*1,300,24,24,"X:%lf",GPS_List[0].position.x);
			LCD_printf(0,6+36*2,300,24,24,"Y:%lf",GPS_List[0].position.y);
			LCD_printf(0,6+36*3,300,24,24,"Angle:%lf",GPS_List[0].angle);
			LCD_printf(0,6+36*4,300,24,24,"Aim_X:%lf",aim_line_point.aim_position.x);
			LCD_printf(0,6+36*5,300,24,24,"Aim_Y:%lf",aim_line_point.aim_position.y);
			LCD_printf(0,6+36*6,300,24,24,"Dis_X:%lf",check_dis_x);
			LCD_printf(0,6+36*7,300,24,24,"Dis_Y:%lf",check_dis_y);
			
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
				else
					break;
			}
			else
				delay_ms(1);
		}*/
		
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 3.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		k = Product_Point_Index[WIFI_Res_2[process_step]-'0' - 1] - 1;
		Servo_Product_Point_Grab_On_Down_Panpilt_Straight(k);
		delay_ms(400);
		
		Servo_Product_Point_Grab_Off_Down_Panpilt_Straight();
		delay_ms(350);
		
		aim_line_point = Product_Point_CCD_Leave_Offset;
		aim_line_point.aim_position.x = GPS_List[0].position.x + Product_Point_CCD_Leave_Offset.aim_position.x;
		aim_line_point.aim_position.y = GPS_List[0].position.y + Product_Point_CCD_Leave_Offset.aim_position.y;
		SetLine(&aim_line_point);
		while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 20.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
				/*	case keyback:
						SPEED_STOP;
						SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
						return;	*/
					default:
						break;
				}
			}
		}
		SPEED_STOP;
		SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
		
		if (process_step != 2)
		{			
			Servo_Duty[0] = 42;
			Servo_Duty[1] = 33;
			Servo_Duty[2] = 14;
			Servo_Duty[3] = 27;
			Servo_PWM_SetDuty();
			delay_ms(200);
			
			aim_line_point = Trans;
			SetLine(&aim_line_point);
			while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 20.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
					/*	case keyback:
							SPEED_STOP;
							SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
							return;	*/
						default:
							break;
					}
				}
			}
			SPEED_STOP;
			SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
			
			Servo_Working_Point_Grab_Off_Middle_Panpilt_Skew();
		}
		
	/*	Show_Keyboard();
		POINT_COLOR=BLACK;
		LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
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
				else
					break;
			}
			else
				delay_ms(1);
		}*/
	}
	
	aim_line_point = Original_Point;
	SetLine(&aim_line_point);
	POINT_COLOR=BLACK;
	while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 20.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
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
			/*	case keyback:
					SPEED_STOP;
					SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
					return;	*/
				default:
					break;
			}
		}
	}
	SPEED_STOP;
	SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
	
	Servo_Product_Point_Bend();
	delay_ms(500);
	
	Servo_Original_Point_Bend();
	
	return 0;
}

void process_CCD_Auto_RGB(void)
{
	u8 tp_last, key_value, is_key = 0;
	u8 res;
	
	GPS_Clear();
	delay_ms(100);
	
	WIFI_Res_1[0] = '1';
	WIFI_Res_1[1] = '2';
	WIFI_Res_1[2] = '3';
	
	WIFI_Res_2[0] = '3';
	WIFI_Res_2[1] = '2';
	WIFI_Res_2[2] = '1';
	
	SW_Start_Flag = 0;
	
	KeyBoard_State = 0;
	Show_Keyboard();
	POINT_COLOR=BLACK;
	LCD_printf(0,6+36*0,300,24,24,"Press any key to start");
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
			else
				break;
		}
		else
			delay_ms(1);
		
		if (SW_Start_Flag)
			break;
	}
	
	res = process_CCD_Auto(0);
}
//offset 494.97
struct Line_Point Task_1_Take_Point[4] = {
	{{-494.97, 1194.97}, 0, 40, 300, 40, -1, 2},
	{{-494.97, 205.03}, 0, 40, 300, 40, -1, 2},
	{{494.97, 205.03}, 0, 40, 300, 40, -1, 2},
	{{494.97, 1194.97}, 0, 40, 300, 40, -1, 2},
};
struct Line_Point Task_1_Take_Point_Offset[4] = {
	{{-345, 345}, 0, 40, 300, 40, -1, 2},
	{{-345, -345}, 0, 40, 300, 40, -1, 2},
	{{345, -345}, 0, 40, 300, 40, -1, 2},
	{{345, 345}, 0, 40, 300, 40, -1, 2},
};
struct Line_Point Task_1_Put_Point_Offset[5] = {
	{{-167, 0}, 0, 40, 100, 40, -1, 2}, //blue
	{{0, -167}, 0, 40, 100, 40, -1, 2},//green
	{{167, 0}, 0, 40, 100, 40, -1, 2},//red
	{{0, 167}, 0, 40, 100, 40, -1, 2},//white
	{{167, 167}, 0, 40, 100, 40, -1, 2}
};
struct Line_Point Center_Point =
	{{0, 700}, 0, 40, 300, 40, -1, 2};
struct Line_Point Start_Point = 
	{{0, 0}, 0, 40, 300, 40, -1, 2};
struct CCD_Line Center_Point_CCD_Line = 
	{{64, 64, 64, 64 }, {{0, 0}, {0, 0}, {0, 0}, {0, 0}}};

/*
void Return_Center(void)
{
	struct Line_Point aim_line_point;
	u8 is_key = 0;
	
	aim_line_point = Center_Point;
	SetLine(&aim_line_point);
	while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
	{
		GoLine();

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
void Go_Task_1_Take_Point(u8 Point_Num)
{
	struct Line_Point aim_line_point;
	u8 is_key = 0;
	
	aim_line_point = Task_1_Take_Point[Point_Num - 1];
	SetLine(&aim_line_point);
	while (!(GetLength(&(GPS_List[0].position), &Aim_Line_Point.aim_position) < 10.0 && fabs(GPS_List[0].radian - Aim_Line_Point.aim_radian) < 1.0 * DEG2RAD))
	{
		GoLine();
		
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
}*/
void process_Point_Test(void)
{
	static struct Line_Point aim_line_point;
	u8 is_key = 0;
	
	GPS_Clear();
	
	Show_Keyboard();
	LCD_printf(0,6+36*0,300,24,24,"Ready to GO!");
	
	is_key = keyScan(1);
	
	while (1)
	{
		is_key = keyScan(1);
		if (is_key)
		{
			is_key = 0;
			if (keyValue == keyback)
				return;
			else
				break;
		}
		else
			delay_ms(1);
	}
	Show_Keyboard();
	Return_Any_Point(&Center_Point,10.0,1.0);  // Center Point
	delay_ms(1000);
	
	CCD_Adjust_to_GPS(Center_Point_CCD_Line,Front,Left,Center_Point.aim_position);
//	Return_Any_Point(&Task_1_Take_Point[1-1],20,2);
//	Return_Any_Point(&Center_Point,20,2);
//	Return_Any_Point(&Task_1_Take_Point[2-1],20,2);
//	Return_Any_Point(&Center_Point,20,2);
//	Return_Any_Point(&Task_1_Take_Point[3-1],20,2);
//	Return_Any_Point(&Center_Point,20,2);
//	Return_Any_Point(&Task_1_Take_Point[4-1],20,2);
//	Return_Any_Point(&Center_Point,20,2);
	delay_ms(1000);
	
	aim_line_point = Task_1_Take_Point_Offset[1 - 1];
	aim_line_point.aim_position.x = GPS_List[0].position.x + Task_1_Take_Point_Offset[1 - 1].aim_position.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y + Task_1_Take_Point_Offset[1 - 1].aim_position.y;
	Return_Any_Point(&aim_line_point,15.0,1.5); //1
	
	delay_ms(1000);
	
	aim_line_point.aim_position.x = GPS_List[0].position.x - Task_1_Take_Point_Offset[1 - 1].aim_position.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y - Task_1_Take_Point_Offset[1 - 1].aim_position.y;
	Return_Any_Point(&aim_line_point,15.0,1.5); //Center
	
	delay_ms(1000);
	
	CCD_Adjust_to_GPS(Center_Point_CCD_Line,Front,Left,Center_Point.aim_position);
	delay_ms(1000);
	
	aim_line_point.aim_position.x = GPS_List[0].position.x + Task_1_Take_Point_Offset[2 - 1].aim_position.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y + Task_1_Take_Point_Offset[2 - 1].aim_position.y;
	Return_Any_Point(&aim_line_point,15.0,1.5); //2
	
	delay_ms(1000);
	
	aim_line_point.aim_position.x = GPS_List[0].position.x - Task_1_Take_Point_Offset[2 - 1].aim_position.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y - Task_1_Take_Point_Offset[2 - 1].aim_position.y;
	Return_Any_Point(&aim_line_point,15.0,1.5); //Center
	
	CCD_Adjust_to_GPS(Center_Point_CCD_Line,Front,Left,Center_Point.aim_position);
	delay_ms(1000);
	
	aim_line_point.aim_position.x = GPS_List[0].position.x + Task_1_Take_Point_Offset[3 - 1].aim_position.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y + Task_1_Take_Point_Offset[3 - 1].aim_position.y;
	Return_Any_Point(&aim_line_point,15.0,1.5); //3
	
	delay_ms(1000);
	
	aim_line_point.aim_position.x = GPS_List[0].position.x - Task_1_Take_Point_Offset[3 - 1].aim_position.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y - Task_1_Take_Point_Offset[3 - 1].aim_position.y;
	Return_Any_Point(&aim_line_point,15.0,1.5); //Center
	
	CCD_Adjust_to_GPS(Center_Point_CCD_Line,Front,Left,Center_Point.aim_position);
	delay_ms(1000);
	
	aim_line_point.aim_position.x = GPS_List[0].position.x + Task_1_Take_Point_Offset[4 - 1].aim_position.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y + Task_1_Take_Point_Offset[4 - 1].aim_position.y;
	Return_Any_Point(&aim_line_point,15.0,1.5); //4
	
	delay_ms(1000);
	
	aim_line_point.aim_position.x = GPS_List[0].position.x - Task_1_Take_Point_Offset[4 - 1].aim_position.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y - Task_1_Take_Point_Offset[4 - 1].aim_position.y;
	Return_Any_Point(&aim_line_point,15.0,1.5); //Center
	  
	CCD_Adjust_to_GPS(Center_Point_CCD_Line,Front,Left,Center_Point.aim_position);
	delay_ms(1000);
}

void process_My_Test(void)
{
	struct Line_Point aim_line_point,put_line_point;
//	u8 is_key = 0;	
	
	Show_Keyboard();
	Return_Any_Point(&Center_Point,10.0,1.0);  // Center Point
	delay_ms(1000);
	
	CCD_Adjust_to_GPS(Center_Point_CCD_Line,Front,Left,Center_Point.aim_position);
	delay_ms(1000);
	while(1)
	{
	set_loc[0] = 400000;
	set_loc[1] = PanTilt_Zero + 1024;
	
	aim_line_point = Task_1_Take_Point_Offset[1 - 1];
	aim_line_point.aim_position.x = GPS_List[0].position.x + Task_1_Take_Point_Offset[1 - 1].aim_position.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y + Task_1_Take_Point_Offset[1 - 1].aim_position.y;
	Return_Any_Point(&aim_line_point,10.0,1.0); //1
	
	pos_Grab();
	
	put_line_point = Color_Judge();
	
	aim_line_point.aim_position.x = GPS_List[0].position.x - Task_1_Take_Point_Offset[1 - 1].aim_position.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y - Task_1_Take_Point_Offset[1 - 1].aim_position.y;
	Return_Any_Point(&aim_line_point,10.0,1.0); //Center
	
	CCD_Adjust_to_GPS(Center_Point_CCD_Line,Front,Left,Center_Point.aim_position);
	
	Return_Any_Point(&put_line_point,5.0,1.0);
	delay_ms(500);
	pos_Put();
	
	Return_Any_Point(&Center_Point,10.0,1.0);
	CCD_Adjust_to_GPS(Center_Point_CCD_Line,Front,Left,Center_Point.aim_position);
	}
	
//	set_loc[1] = PanTilt_Zero - 1024*2 - 100; 
//	
//	aim_line_point = Task_1_Put_Point_Offset[3 - 1];
//	aim_line_point.aim_position.x = GPS_List[0].position.x + Task_1_Put_Point_Offset[3 - 1].aim_position.x;
//	aim_line_point.aim_position.y = GPS_List[0].position.y + Task_1_Put_Point_Offset[3 - 1].aim_position.y;
//	Return_Any_Point(&aim_line_point,5.0,1.0); //red
//	
//	pos_Put();
//	
//	aim_line_point = Task_1_Put_Point_Offset[3 - 1];
//	aim_line_point.aim_position.x = GPS_List[0].position.x - Task_1_Put_Point_Offset[3 - 1].aim_position.x;
//	aim_line_point.aim_position.y = GPS_List[0].position.y - Task_1_Put_Point_Offset[3 - 1].aim_position.y;
//	Return_Any_Point(&aim_line_point,10.0,1.0);
//	CCD_Adjust_to_GPS(Center_Point_CCD_Line,Front,Left,Center_Point.aim_position);

/*	set_loc[0] = 400000;
	set_loc[1] = PanTilt_Zero + 1024*3;
	
	aim_line_point = Task_1_Take_Point_Offset[2 - 1];
	aim_line_point.aim_position.x = GPS_List[0].position.x + Task_1_Take_Point_Offset[2 - 1].aim_position.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y + Task_1_Take_Point_Offset[2 - 1].aim_position.y;
	Return_Any_Point(&aim_line_point,10.0,1.0); //2
	
	delay_ms(1000); 
	
	Cylinder = Cylin_Down;
	delay_ms(1500);
	delay_ms(1500);
	Grab = Grab_Close;
	delay_ms(1000);
	Cylinder = Cylin_Up;
	delay_ms(1000);

	aim_line_point.aim_position.x = GPS_List[0].position.x - Task_1_Take_Point_Offset[2 - 1].aim_position.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y - Task_1_Take_Point_Offset[2 - 1].aim_position.y;
	Return_Any_Point(&aim_line_point,10.0,1.0); //Center
	
	CCD_Adjust_to_GPS(Center_Point_CCD_Line,Front,Left,Center_Point.aim_position);
	delay_ms(1000);
	
	set_loc[0] = 400000;
	set_loc[1] = PanTilt_Zero + 1024*5;
	
	aim_line_point = Task_1_Take_Point_Offset[3 - 1];
	aim_line_point.aim_position.x = GPS_List[0].position.x + Task_1_Take_Point_Offset[3 - 1].aim_position.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y + Task_1_Take_Point_Offset[3 - 1].aim_position.y;
	Return_Any_Point(&aim_line_point,10.0,1.0); //3
	
	delay_ms(1000);
	
	aim_line_point.aim_position.x = GPS_List[0].position.x - Task_1_Take_Point_Offset[3 - 1].aim_position.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y - Task_1_Take_Point_Offset[3 - 1].aim_position.y;
	Return_Any_Point(&aim_line_point,10.0,1.0); //Center
	
	CCD_Adjust_to_GPS(Center_Point_CCD_Line,Front,Left,Center_Point.aim_position);
	delay_ms(1000);
	
	set_loc[0] = 400000;
	set_loc[1] = PanTilt_Zero + 1024*7;
	
	aim_line_point = Task_1_Take_Point_Offset[4 - 1];
	aim_line_point.aim_position.x = GPS_List[0].position.x + Task_1_Take_Point_Offset[4 - 1].aim_position.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y + Task_1_Take_Point_Offset[4 - 1].aim_position.y;
	Return_Any_Point(&aim_line_point,10.0,1.0); //4
	
	delay_ms(1000);
	
	aim_line_point.aim_position.x = GPS_List[0].position.x - Task_1_Take_Point_Offset[4 - 1].aim_position.x;
	aim_line_point.aim_position.y = GPS_List[0].position.y - Task_1_Take_Point_Offset[4 - 1].aim_position.y;
	Return_Any_Point(&aim_line_point,10.0,1.0); //Center
	
	CCD_Adjust_to_GPS(Center_Point_CCD_Line,Front,Left,Center_Point.aim_position);
	delay_ms(1000);*/
	
//	CCD_Adjust_to_GPS(Corner_Point_CCD_Line[1-1],0,1,Corner_Point[1-1].aim_position);
//	delay_ms(1000);
//	Return_Any_Point(&Corner_Point[2-1],15.0,1.5);
//	CCD_Adjust_to_GPS(Corner_Point_CCD_Line[2-1],0,2,Corner_Point[2-1].aim_position);
//	delay_ms(1000);
//	Return_Any_Point(&Corner_Point[3-1],15.0,1.5);
//	CCD_Adjust_to_GPS(Corner_Point_CCD_Line[3-1],3,2,Corner_Point[3-1].aim_position);
//	delay_ms(1000);
//	Return_Any_Point(&Corner_Point[4-1],15.0,1.5);
//	CCD_Adjust_to_GPS(Corner_Point_CCD_Line[4-1],3,1,Corner_Point[4-1].aim_position);
	
//	delay_ms(1000); 
}
