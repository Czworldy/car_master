#include "pid.h"

struct PID Pid_List[]=
{
  	{0.3,1000000,0,0,0,0},
	{0.4,1000000,0,0,0,0},
	
	{0.1,1000000,0,0,0,0},
	{0.2,1000000,0,0,0,0},
	
	
	{0.1,1000000,0,0,0,0},//{0.3,1000000,0,0,0,0}, //angle?
	{1.0,1000000,0,0,0,0},
	
	{0.3,1000000,0,0,0,0},
	{1.0,1000000,0,0,0,0},
	
	{0.001,50000,0,0,0,0},
	{0.001,50000,0,0,0,0},
};
static uint8_t Pid_List_Size = sizeof(Pid_List)/sizeof(struct PID);

static double A_ErrorPast1 = 0;
static double A_ErrorPast2 = 0;
static double A_Mend = 0;
static double D_ErrorPast1 = 0;
static double D_ErrorPast2 = 0;
static double D_Mend = 0;

double Vout[5] = {0.0};


/*
 * 函数名: PID_Clear
 * 描  述: 将PID存储的误差值清除
 * 输  入: 无
 * 输  出: 无
 * 调  用: 外部调用
 */
void PID_Clear(void)
{
	u8 i;
	
	for (i = 0; i < Pid_List_Size; ++i)
	{
		Pid_List[i].mend = 0;
		Pid_List[i].ep1 = 0;
		Pid_List[i].ep2 = 0;
	}
	
	A_ErrorPast1 = 0.0;
	A_ErrorPast2 = 0.0;
	A_Mend = 0.0;
	D_ErrorPast1 = 0.0;
	D_ErrorPast2 = 0.0;
	D_Mend = 0.0;
	
	for (i = 0; i < 5; ++i)
	   Vout[i] = 0;
}

/*
 * 函数名: PID
 * 描  述: 位置式PID调整，利用了增量式的递推
 * 输  入: -Error 误差量
 *		   -pid pid参数
 * 输  出: 反馈结果
 * 调  用: 外部调用
 */
double PID(double Error,struct PID *pid)
{
	double A = 0;
	double B = 0;
	double C = 0;
	double delta = 0;
	
	A = (pid->p*(1+1/pid->i+pid->d));
	B = -pid->p*(1+2*pid->d);
	C = pid->p*pid->d;
	
	delta = A*Error + B*pid->ep1 + C*pid->ep2;
	pid->mend += delta;
	
	pid->ep2 = pid->ep1;
	pid->ep1 = Error;
	
	return pid->mend;
}


/*
 * 函数名: AnglePID
 * 描  述: 位置式角度PID调整，利用了增量式的递推
 * 输  入: -Error 误差量
 *		   -pid pid参数
 * 输  出: 角速度
 * 调  用: 外部调用
 */
double AnglePID(double Error,struct PID *pid)
{
	double A = 0;
	double B = 0;
	double C = 0;
	double delta = 0;

	
	A = (pid->p*(1+1/pid->i+pid->d));
	B = -pid->p*(1+2*pid->d);
	C = pid->p*pid->d;
	
	delta = A*Error + B*A_ErrorPast1 + C*A_ErrorPast2;
	A_Mend += delta;
	
	A_ErrorPast2 = A_ErrorPast1;
	A_ErrorPast1 = Error;
	
	return A_Mend;
}

/*
 * 函数名: DistancePID
 * 描  述: 位置式距离PID调整，利用了增量式的递推
 * 输  入: -Error 误差量
 *		   -pid pid参数
 * 输  出: 速度
 * 调  用: 外部调用
 */
double DistancePID(double Error,struct PID *pid)
{
	double A = 0;
	double B = 0;
	double C = 0;
	double delta = 0;
	
	A = (pid->p*(1+1/pid->i+pid->d));
	B = -pid->p*(1+2*pid->d);
	C = pid->p*pid->d;
	
	delta = A*Error + B*D_ErrorPast1 + C*D_ErrorPast2;
	D_Mend += delta;
	
	D_ErrorPast2 = D_ErrorPast1;
	D_ErrorPast1 = Error;
	
	return D_Mend;
}
