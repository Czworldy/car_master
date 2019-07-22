/* Includes ------------------------------------------------------------------*/
#include "mecanum.h"
#include "mymath.h"
#include "motor.h"

//���������ϵ�ǻ����˵ľֲ�����ϵ
double Speed_X = 0;				// mm/s
double Speed_Y = 0;				// mm/s
double Speed_Rotation = 0;		// (rad/s)/100
double RPM_Limit = 500; //3000

struct Mecanum_State Mec_FL = {3, -1};
struct Mecanum_State Mec_FR = {2, -1};
struct Mecanum_State Mec_BL = {4, -1};
struct Mecanum_State Mec_BR = {1, -1};

double Mec_wheel_r_FL = 28.0;
double Mec_wheel_r_FR = 28.0;
double Mec_wheel_r_BL = 28.0;
double Mec_wheel_r_BR = 28.0;

double Mec_Len_FL = 138.84;//97.5
double Mec_Len_FR = 138.84;
double Mec_Len_BL = 138.84;
double Mec_Len_BR = 138.84;

static double Mec_Rad_FL = 3*pi/4;
static double Mec_Rad_FR = pi/4;
static double Mec_Rad_BL = 5*pi/4;
static double Mec_Rad_BR = 7*pi/4;

/*
 * ������: SetSpeed
 * ��  ��: Ϊ�����˸��ٶ�
 * ��  ��: ����������ϵX�����ٶ�(mm/s)��Y�����ٶ�(mm/s)����ת�ٶ�(rad/s)/100
 * ��  ��: ��
 * ��  ��: �ⲿ����
 */
void SetSpeed(double speed_x, double speed_y, double speed_rotation)
{
	/*���ٶ�*/
	double fl_speed;
	double fr_speed;
	double bl_speed;
	double br_speed;
	
	double RPM_Max;				//���ɵ�PWM���Ӧ���ٶ����ֵ
	
	double dec_rot = 1.0/100;//��ת�ٶ�(rad/s)/100
	double cov = 60.0/(2*pi);//���ٶȺ�ת�ٵ�ת��ϵ��
	
	/****************************ͨ���ſ˱Ⱦ�����ٶȷֽ⵽��������******************************/
	fl_speed = (-sin(Mec_Rad_FL) * speed_x + cos(Mec_Rad_FL) * speed_y + Mec_Len_FL * speed_rotation * dec_rot) / Mec_wheel_r_FL * cov;
	fr_speed = (-sin(Mec_Rad_FR) * speed_x + cos(Mec_Rad_FR) * speed_y + Mec_Len_FR * speed_rotation * dec_rot) / Mec_wheel_r_FR * cov;
	bl_speed = (-sin(Mec_Rad_BL) * speed_x + cos(Mec_Rad_BL) * speed_y + Mec_Len_BL * speed_rotation * dec_rot) / Mec_wheel_r_BL * cov;
	br_speed = (-sin(Mec_Rad_BR) * speed_x + cos(Mec_Rad_BR) * speed_y + Mec_Len_BR * speed_rotation * dec_rot) / Mec_wheel_r_BR * cov;

	fl_speed = fl_speed * Mec_FL.arg;
	fr_speed = fr_speed * Mec_FR.arg;
	bl_speed = bl_speed * Mec_BL.arg;
	br_speed = br_speed * Mec_BR.arg;
 	/************************�������ٶ��ٴν�������****************************/
 	RPM_Max = MaxFour(fabs(fl_speed), fabs(fr_speed), fabs(bl_speed), fabs(br_speed));
	if (RPM_Max >= RPM_Limit)
 	{
		fl_speed *= RPM_Limit / RPM_Max;
		fr_speed *= RPM_Limit / RPM_Max;
		bl_speed *= RPM_Limit / RPM_Max;
 		br_speed *= RPM_Limit / RPM_Max;
 	}
	/************************����Ӧ�Ķ˿ڽ��и�ֵ******************************/
	Motor_Set_Rotation_Speed(Mec_FL.port, fl_speed);
	Motor_Set_Rotation_Speed(Mec_FR.port, fr_speed);
 	Motor_Set_Rotation_Speed(Mec_BL.port, bl_speed);
	Motor_Set_Rotation_Speed(Mec_BR.port, br_speed);
}

/**********************************END OF FILE*********************************/
