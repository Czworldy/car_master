/* Includes ------------------------------------------------------------------*/
#include "mecanum.h"
#include "mymath.h"
#include "motor.h"

//下面的坐标系是机器人的局部坐标系
double Speed_X = 0;				// mm/s
double Speed_Y = 0;				// mm/s
double Speed_Rotation = 0;		// (rad/s)/100
double RPM_Limit = 500; //3000

struct Mecanum_State Mec_FL = {3, -1};//2//4//3
struct Mecanum_State Mec_FR = {2, -1};//3//1//2
struct Mecanum_State Mec_BL = {4, -1};//1//3//4
struct Mecanum_State Mec_BR = {1, -1};//4//2//1

double Mec_wheel_r_FL = 28.0;
double Mec_wheel_r_FR = 28.0;
double Mec_wheel_r_BL = 28.0;
double Mec_wheel_r_BR = 28.0;

double Mec_Len_FL = 140.01;//138.84;//97.5//140.01
double Mec_Len_FR = 140.01;
double Mec_Len_BL = 140.01;
double Mec_Len_BR = 140.01;

static double Mec_Rad_FL = 3*pi/4;
static double Mec_Rad_FR = pi/4;
static double Mec_Rad_BL = 5*pi/4;
static double Mec_Rad_BR = 7*pi/4;

/*
 * 函数名: SetSpeed
 * 描  述: 为机器人赋速度
 * 输  入: 机器人坐标系X方向速度(mm/s)，Y方向速度(mm/s)和自转速度(rad/s)/100
 * 输  出: 无
 * 调  用: 外部调用
 */
void SetSpeed(double speed_x, double speed_y, double speed_rotation)
{
	/*角速度*/
	double fl_speed;
	double fr_speed;
	double bl_speed;
	double br_speed;
	
	double RPM_Max;				//生成的PWM后对应的速度最大值
	
	double dec_rot = 1.0/100;//自转速度(rad/s)/100
	double cov = 60.0/(2*pi);//角速度和转速的转化系数
	
	/****************************通过雅克比矩阵把速度分解到各个轮子******************************/
	fl_speed = (-sin(Mec_Rad_FL) * speed_x + cos(Mec_Rad_FL) * speed_y + Mec_Len_FL * speed_rotation * dec_rot) / Mec_wheel_r_FL * cov;
	fr_speed = (-sin(Mec_Rad_FR) * speed_x + cos(Mec_Rad_FR) * speed_y + Mec_Len_FR * speed_rotation * dec_rot) / Mec_wheel_r_FR * cov;
	bl_speed = (-sin(Mec_Rad_BL) * speed_x + cos(Mec_Rad_BL) * speed_y + Mec_Len_BL * speed_rotation * dec_rot) / Mec_wheel_r_BL * cov;
	br_speed = (-sin(Mec_Rad_BR) * speed_x + cos(Mec_Rad_BR) * speed_y + Mec_Len_BR * speed_rotation * dec_rot) / Mec_wheel_r_BR * cov;

	fl_speed = fl_speed * Mec_FL.arg;
	fr_speed = fr_speed * Mec_FR.arg;
	bl_speed = bl_speed * Mec_BL.arg;
	br_speed = br_speed * Mec_BR.arg;
 	/************************对最终速度再次进行限制****************************/
 	RPM_Max = MaxFour(fabs(fl_speed), fabs(fr_speed), fabs(bl_speed), fabs(br_speed));
	if (RPM_Max >= RPM_Limit)
 	{
		fl_speed *= RPM_Limit / RPM_Max;
		fr_speed *= RPM_Limit / RPM_Max;
		bl_speed *= RPM_Limit / RPM_Max;
 		br_speed *= RPM_Limit / RPM_Max;
 	}
	/************************给相应的端口进行赋值******************************/
	Motor_Set_Rotation_Speed(Mec_FL.port, fl_speed);
	Motor_Set_Rotation_Speed(Mec_FR.port, fr_speed);
 	Motor_Set_Rotation_Speed(Mec_BL.port, bl_speed);
	Motor_Set_Rotation_Speed(Mec_BR.port, br_speed);
}

/**********************************END OF FILE*********************************/
