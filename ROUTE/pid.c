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
 * ������: PID_Clear
 * ��  ��: ��PID�洢�����ֵ���
 * ��  ��: ��
 * ��  ��: ��
 * ��  ��: �ⲿ����
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
 * ������: PID
 * ��  ��: λ��ʽPID����������������ʽ�ĵ���
 * ��  ��: -Error �����
 *		   -pid pid����
 * ��  ��: �������
 * ��  ��: �ⲿ����
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
 * ������: AnglePID
 * ��  ��: λ��ʽ�Ƕ�PID����������������ʽ�ĵ���
 * ��  ��: -Error �����
 *		   -pid pid����
 * ��  ��: ���ٶ�
 * ��  ��: �ⲿ����
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
 * ������: DistancePID
 * ��  ��: λ��ʽ����PID����������������ʽ�ĵ���
 * ��  ��: -Error �����
 *		   -pid pid����
 * ��  ��: �ٶ�
 * ��  ��: �ⲿ����
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
