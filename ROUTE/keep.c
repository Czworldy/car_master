#include "all.h"

struct Point Aim_Keep_Point;
double Aim_Keep_Radian;
double Speed_Keep_Max;
double Speed_Rotation_Max = 150;

/*
 * ������: SetKeep
 * ��  ��: ���ٵ���ָ��λ����Ƕ�
 * ��  ��: -end_point  Ŀ��λ��
 *		   -aim_radian Ŀ��Ƕ�
 * ��  ��: ��
 * ��  ��: �ⲿ����
 */
void SetKeep(struct Point *end_point, double aim_radian, double speed_max)
{
	Aim_Keep_Point = *end_point;
	Aim_Keep_Radian = aim_radian;
	Speed_Keep_Max = speed_max;
	PID_Clear();
}

void Keep(struct PID *Pid_ang,struct PID *Pid_dis)
{
	struct Point cur_point;
	double cur_radian;
	double lineangle;
	
	double speed = 0;
	double speed_x, speed_y;						//������������ٶ�����ٶ�
	double speed_robot_x, speed_robot_y;			//ת��������������ķ��ٶ�
	
	double error_angle,error_dis;				//�Ƕ������������
	double Vout_A = 0;							//PID������Ƕ����ֵ
	double Vout_D = 0;							//PID������������ֵ
	
	cur_point.x = GPS_List[0].position.x;
	cur_point.y = GPS_List[0].position.y;
	cur_radian = GPS_List[0].radian;
	
	lineangle = GetLineAngle(&cur_point, &Aim_Keep_Point);	//�����·���߶ε����
	
	//��Ƕ������������
	error_angle = Aim_Keep_Radian - cur_radian;
	error_dis = GetLength(&cur_point, &Aim_Keep_Point);
	
	while (error_angle > pi)
		error_angle -= 2 * pi;
	while (error_angle < -pi)
		error_angle += 2 * pi;
	
	//PID����
	Vout_A = 1000 * AnglePID(error_angle, Pid_ang);
	Vout_D = DistancePID(error_dis, Pid_dis);
	
	//�����ת��
	if (Vout_A > Speed_Rotation_Max)
		Vout_A = Speed_Rotation_Max;
	else if (Vout_A < -Speed_Rotation_Max)
		Vout_A = -Speed_Rotation_Max;
	
	speed = Vout_D;
	
	//�������
	if (speed > Speed_Keep_Max)
		speed = Speed_Keep_Max;
	else if (speed < -Speed_Keep_Max)
		speed = -Speed_Keep_Max;
	
	//���ٶ���x,y�����ϵķ���
	speed_x = speed * cos(lineangle);
	speed_y = speed * sin(lineangle);
	
	//������������ٶ�ת��Ϊ�����˾ֲ�������ٶ�
	speed_robot_x =  speed_x*cos(cur_radian) + speed_y*sin(cur_radian);
	speed_robot_y = -speed_x*sin(cur_radian) + speed_y*cos(cur_radian);
	
	//Ϊ���ָ��ٶ�
	Speed_X = speed_robot_x;
	Speed_Y = speed_robot_y;
	Speed_Rotation = Vout_A;
	
	SetSpeed(Speed_X, Speed_Y, Speed_Rotation);
	
//	POINT_COLOR = BLACK;
//	LCD_printf(0,6+36*0,300,24,24,"1.Angle = %.6lf        ",GPS_List[0].angle);
//	LCD_printf(0,6+36*1,300,24,24,"2.X = %.6lf        ",GPS_List[0].position.x);
//	LCD_printf(0,6+36*2,300,24,24,"3.Y = %.6lf        ",GPS_List[0].position.y);
//	
//	if (Vout_A < 0)
//		POINT_COLOR = RED;
//	else
//		POINT_COLOR = BLACK;
//	LCD_printf(0,6+36*3,300,24,24,"4.Vout_A = %.6lf        ",Vout_A);
//	
//	if (speed_x < 0)
//		POINT_COLOR = RED;
//	else
//		POINT_COLOR = BLACK;
//	LCD_printf(0,6+36*4,300,24,24,"5.speed_x = %.6lf        ",speed_x);
//	
//	if (speed_y < 0)
//		POINT_COLOR = RED;
//	else
//		POINT_COLOR = BLACK;
//	LCD_printf(0,6+36*5,300,24,24,"6.speed_y = %.6lf        ",speed_y);
}
