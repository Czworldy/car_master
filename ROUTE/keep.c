#include "all.h"

struct Point Aim_Keep_Point;
double Aim_Keep_Radian;
double Speed_Keep_Max;
double Speed_Rotation_Max = 150;

/*
 * 函数名: SetKeep
 * 描  述: 快速到达指定位置与角度
 * 输  入: -end_point  目标位置
 *		   -aim_radian 目标角度
 * 输  出: 无
 * 调  用: 外部调用
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
	double speed_x, speed_y;						//世界坐标里的速度与分速度
	double speed_robot_x, speed_robot_y;			//转换到机器人坐标的分速度
	
	double error_angle,error_dis;				//角度误差与距离误差
	double Vout_A = 0;							//PID调整后角度输出值
	double Vout_D = 0;							//PID调整后距离输出值
	
	cur_point.x = GPS_List[0].position.x;
	cur_point.y = GPS_List[0].position.y;
	cur_radian = GPS_List[0].radian;
	
	lineangle = GetLineAngle(&cur_point, &Aim_Keep_Point);	//求出该路径线段的倾角
	
	//求角度误差与距离误差
	error_angle = Aim_Keep_Radian - cur_radian;
	error_dis = GetLength(&cur_point, &Aim_Keep_Point);
	
	while (error_angle > pi)
		error_angle -= 2 * pi;
	while (error_angle < -pi)
		error_angle += 2 * pi;
	
	//PID调整
	Vout_A = 1000 * AnglePID(error_angle, Pid_ang);
	Vout_D = DistancePID(error_dis, Pid_dis);
	
	//限最大转速
	if (Vout_A > Speed_Rotation_Max)
		Vout_A = Speed_Rotation_Max;
	else if (Vout_A < -Speed_Rotation_Max)
		Vout_A = -Speed_Rotation_Max;
	
	speed = Vout_D;
	
	//限最大速
	if (speed > Speed_Keep_Max)
		speed = Speed_Keep_Max;
	else if (speed < -Speed_Keep_Max)
		speed = -Speed_Keep_Max;
	
	//求速度在x,y方向上的分量
	speed_x = speed * cos(lineangle);
	speed_y = speed * sin(lineangle);
	
	//将世界坐标的速度转换为机器人局部坐标的速度
	speed_robot_x =  speed_x*cos(cur_radian) + speed_y*sin(cur_radian);
	speed_robot_y = -speed_x*sin(cur_radian) + speed_y*cos(cur_radian);
	
	//为四轮赋速度
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
