#include "all.h"

struct Line_Point Aim_Line_Point;
struct Point Sta_Point;
struct Point End_Point;
double Aim_Radian;
double Speed_Sta;
double Speed_End;
double Speed_Max;
double Line_Angle;
double Line_Length;
double Acc_Dis, Dec_Dis;
double Acc_Dis_Rate, Dec_Dis_Rate;
double Acc, Dec;
s8 Rotation_Dir;
u8 PID_List_Index = 2;


/*
 * ������: SetLine
 * ��  ��: ��ʼ����ֱ�߹���
 * ��  ��: -end_point  Ŀ��λ��
 *		   -aim_radian Ŀ��Ƕ�
 *		   -speed_sta  ��ʼ�ٶ�
 *		   -speed_max  ����ٶ�
 *		   -speed_end  �����ٶ�
 * ��  ��: ��
 * ��  ��: �ⲿ����
 */
void SetLine(struct Line_Point *line_point)
{
	Aim_Line_Point = *line_point;
	Sta_Point = GPS_List[0].position;		//��¼��ʼλ��
	End_Point = line_point->aim_position;
	Aim_Radian = line_point->aim_radian;
	
	Speed_Sta = line_point->speed_sta;
	Speed_End = line_point->speed_end;
	Speed_Max = line_point->speed_max;
	
	Rotation_Dir = line_point->rotation_dir;
	PID_List_Index = line_point->pid_list_index;
	
	Line_Angle = GetLineAngle(&Sta_Point,&End_Point);	//�����·���߶ε����
	
	Line_Length = GetLength(&Sta_Point,&End_Point);				//�����·���߶εĳ���
	
	Acc_Dis_Rate = (Speed_Max*Speed_Max - Speed_Sta*Speed_Sta)/(2*Speed_Max*Speed_Max - Speed_Sta*Speed_Sta - Speed_End*Speed_End);
	Dec_Dis_Rate = (Speed_Max*Speed_Max - Speed_End*Speed_End)/(2*Speed_Max*Speed_Max - Speed_Sta*Speed_Sta - Speed_End*Speed_End);
	
	Acc_Dis = Acc_Dis_Rate * Line_Length;//���پ���ͼ��پ���
	Dec_Dis = Dec_Dis_Rate * Line_Length;
	
	Acc = (Speed_Max * Speed_Max - Speed_Sta * Speed_Sta) / (2 * Acc_Dis);//���ٶ�����ٶ� v^2 = v0^2 + 2ax
	Dec = (Speed_Max * Speed_Max - Speed_End * Speed_End) / (2 * Dec_Dis);
	
//	LCD_printf(0,6+36*8,300,24,24,"8.Line Angle:%.3lf",Line_Angle);
//	LCD_printf(0,6+36*9,300,24,24,"9.Acc:%.3lf,Dec:%.3lf",Acc,Dec);
//	LCD_printf(0,6+36*10,300,24,24,"10.Sta.X:%.3lf,Sta.Y:%.3lf",Sta_Point.x,Sta_Point.y);
//	LCD_printf(0,6+36*11,300,24,24,"11.End.X:%.3lf,End.Y:%.3lf",End_Point.x,End_Point.y);
//	delay_ms(1000);
//	delay_ms(1000);
//	delay_ms(1000);
	
	PID_Clear();
}

void GoLine(void)
{
	struct Point pos = {0};						//��������
	struct Point cur_pos = {0};
	double cur_radian = 0;
	
	double speed_x = 0;							//������������ٶ�����ٶ�
	double speed_y = 0;
	double speed = 0;
	double speed_robot_x = 0;
	double speed_robot_y = 0;					//ת��������������ķ��ٶ�
	
	double error_angle = 0, error_dis = 0;			//�Ƕ������������
	double Vout_A = 0;						//PID������Ƕ����ֵ
	double Vout_D = 0;						//PID������������ֵ
	double v_err_x = 0, v_err_y = 0;					//PID�����ٶȵķ���
	
	double sin_temp = 0, cos_temp = 0;
	double temp_dis = 0;
	
	cur_pos.x = GPS_List[0].position.x;
	cur_pos.y = GPS_List[0].position.y;
	cur_radian = GPS_List[0].radian;
	
	pos = GetFoot_P2L_PP(&cur_pos, &Sta_Point, &End_Point);	//�õ���������
	
	//�����������긳�ٶ�
	temp_dis = GetLength(&Sta_Point,&pos);
	if (temp_dis <= Acc_Dis)
	{
		speed = sqrt(Speed_Sta * Speed_Sta + 2 * Acc * temp_dis);
		if (speed > Speed_Max)
			speed = Speed_Max;
	}
	else if (temp_dis >= Line_Length)
	{
		speed = -sqrt(Speed_End * Speed_End + 2 * Dec * GetLength(&End_Point, &pos));
		if (speed < -Speed_Max)
			speed = -Speed_Max;
	}
	else if (temp_dis >= (Line_Length - Dec_Dis))
	{
		speed = sqrt(Speed_End * Speed_End + 2 * Dec * GetLength(&End_Point, &pos));
		if (speed > Speed_Max)
			speed = Speed_Max;
	}
	else
		speed = Speed_Max;
	
	cos_temp = cos(Line_Angle);
	sin_temp = sin(Line_Angle);
	
	//���ٶ���x,y�����ϵķ���
	speed_x = speed * cos_temp;
	speed_y = speed * sin_temp;
	
	//�Ƕ����;������
	error_angle = Aim_Radian - cur_radian;
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
	
	//error_disΪ��ֱ·��������ƫ��·���ľ��룬����
	error_dis = (cur_pos.x - Sta_Point.x) * sin_temp -(cur_pos.y - Sta_Point.y) * cos_temp;
	
	//PID����
	//if(GetLength(GPS.position,Sta_Point) >= Acc_Dis)
	Vout_A = 1000*AnglePID(error_angle, &Pid_List[PID_List_Index << 1]);
	Vout_D = DistancePID(error_dis, &Pid_List[(PID_List_Index << 1) | 1]);
	
	if (Vout_A >= 100)  //300
		Vout_A = 100;
	if (Vout_A <= -100)
		Vout_A = -100;
	
	//PID�����ٶȵķ���
	v_err_x = -Vout_D * sin_temp;
	v_err_y =  Vout_D * cos_temp;
	
	//���ϵ�������
	speed_x += v_err_x;
	speed_y += v_err_y;
	
	speed = sqrt(speed_x * speed_x + speed_y * speed_y);
	if (speed > Speed_Max)
	{
		speed_x *= Speed_Max / speed;
		speed_y *= Speed_Max / speed;
	}
	
	cos_temp = cos(GPS_List[0].radian);
	sin_temp = sin(GPS_List[0].radian);
	
	//������������ٶ�ת��Ϊ�����˾ֲ�������ٶ�
	speed_robot_x =  speed_x * cos_temp + speed_y * sin_temp;
	speed_robot_y = -speed_x * sin_temp + speed_y * cos_temp;
	
	//Ϊ���ָ��ٶ�
	Speed_X = speed_robot_x;
	Speed_Y = speed_robot_y;
	Speed_Rotation = Vout_A;
	
	SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
	
//	POINT_COLOR = BLACK;
//	LCD_printf(0,6+36*0,300,24,24,"1.Angle = %.6lf        ",GPS_List[0].angle);
//	LCD_printf(0,6+36*1,300,24,24,"2.X = %.6lf        ",GPS_List[0].position.x);
//	LCD_printf(0,6+36*2,300,24,24,"3.Y = %.6lf        ",GPS_List[0].position.y);
//	LCD_printf(0,6+36*3,300,24,24,"4.speed_x = %.6lf        ",speed_x);
//	LCD_printf(0,6+36*4,300,24,24,"5.speed_Y = %.6lf        ",speed_y);
//	
//	if (Vout_A < 0)
//		POINT_COLOR = RED;
//	else
//		POINT_COLOR = BLACK;
//	LCD_printf(0,6+36*5,300,24,24,"6.Vout_A = %.6lf        ",Vout_A);
//	
//	if (v_err_x < 0)
//		POINT_COLOR = RED;
//	else
//		POINT_COLOR = BLACK;
//	LCD_printf(0,6+36*6,300,24,24,"7.v_err_x = %.6lf        ",v_err_x);
//	
//	if (v_err_y < 0)
//		POINT_COLOR = RED;
//	else
//		POINT_COLOR = BLACK;
//	LCD_printf(0,6+36*7,300,24,24,"8.v_err_y = %.6lf        ",v_err_y);
}
