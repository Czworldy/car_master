#include "all.h"
#include <stdio.h>

moto_measure_t moto_chassis[4];

int set_spd[4]={0,0,0,0};
int64_t set_loc[4]={0,0,0,0};

pid_t pid_spd[4];
uint16_t set_angle[4];
pid_t pid_spd[4];
pid_t pid_loc[4];

int Mode[4] = {	Location_Mode,//main
								Location_Mode,//angle
								Speed_Mode,//side1
								Speed_Mode};//side2

void abs_limit(float *a, float ABS_MAX){
    if(*a > ABS_MAX)
        *a = ABS_MAX;
    if(*a < -ABS_MAX)
        *a = -ABS_MAX;
}

static void pid_param_init(
    pid_t *pid, 
    uint32_t mode,
    uint32_t maxout,
    uint32_t intergral_limit,
    float 	kp, 
    float 	ki, 
    float 	kd){
    
    pid->IntegralLimit = intergral_limit;
    pid->MaxOutput = maxout;
    pid->pid_mode = mode;
    
    pid->p = kp;
    pid->i = ki;
    pid->d = kd;
    
}
void calibrate(void);
void calibrate_up(float degree);
void calibrate_down(float degree);

float PID_DJI(pid_t *pid, float get, float set){
	pid->get[NOW] = get;
	pid->set[NOW] = set;
	pid->err[NOW] = set - get;	//set - measure
	
	
//	pid->pout = pid->p * (pid->err[NOW] - pid->err[LAST]);
//	pid->iout = pid->i * pid->err[NOW];
//	pid->dout = pid->d * (pid->err[NOW] - 2*pid->err[LAST] + pid->err[LLAST]);

//	abs_limit(&(pid->iout), pid->IntegralLimit);//???
//	pid->delta_u = pid->pout + pid->iout + pid->dout;
//	pid->delta_out = pid->last_delta_out + pid->delta_u;
//	abs_limit(&(pid->delta_out), pid->MaxOutput);
//	pid->last_delta_out = pid->delta_out;	//update last time
	if(pid->pid_mode == POSITION_PID) //位置式p
    {
        pid->pout = pid->p * pid->err[NOW];
        pid->iout += pid->i * pid->err[NOW];
        pid->dout = pid->d * (pid->err[NOW] - pid->err[LAST] );
        abs_limit(&(pid->iout), pid->IntegralLimit);
        pid->pos_out = pid->pout + pid->iout + pid->dout;
        abs_limit(&(pid->pos_out), pid->MaxOutput);
        pid->last_pos_out = pid->pos_out;	//update last time 
    }
    else if(pid->pid_mode == DELTA_PID)//增量式P
    {
        pid->pout = pid->p * (pid->err[NOW] - pid->err[LAST]);
        pid->iout = pid->i * pid->err[NOW];
        pid->dout = pid->d * (pid->err[NOW] - 2*pid->err[LAST] + pid->err[LLAST]);
        
        abs_limit(&(pid->iout), pid->IntegralLimit);
        pid->delta_u = pid->pout + pid->iout + pid->dout;
        pid->delta_out = pid->last_delta_out + pid->delta_u;
        abs_limit(&(pid->delta_out), pid->MaxOutput);
        pid->last_delta_out = pid->delta_out;	//update last time
    }
	
	pid->err[LLAST] = pid->err[LAST];
	pid->err[LAST] = pid->err[NOW];
	pid->get[LLAST] = pid->get[LAST];
	pid->get[LAST] = pid->get[NOW];
	pid->set[LLAST] = pid->set[LAST];
	pid->set[LAST] = pid->set[NOW];
	
	
	return pid->pid_mode==POSITION_PID ? pid->pos_out : pid->delta_out;
}

/**
*@bref GET电机上电的相对角度
	*/
void get_total_angle(moto_measure_t *p){
	
	int res1, res2, delta;
	if(p->angle < p->last_angle){			
		res1 = p->angle + 8192 - p->last_angle;	//正转,delta=+
		res2 = p->angle - p->last_angle;				//反转	delta=-
	}else{	//angle > last
		res1 = p->angle - 8192 - p->last_angle ;//反转	delta -
		res2 = p->angle - p->last_angle;				//正转	delta +
	}
	
	if(ABS(res1)<ABS(res2))
		delta = res1;
	else
		delta = res2;

	p->total_angle += delta;
	p->last_angle = p->angle;
}

void PID_struct_init(
    pid_t* pid,
    uint32_t mode,
    uint32_t maxout,
    uint32_t intergral_limit,
    
    float 	kp, 
    float 	ki, 
    float 	kd){
    /*init function pointer*/
    pid->f_param_init = pid_param_init;
//    pid->f_pid_reset = pid_reset;
//	pid->f_cal_pid = pid_calc;	
//	pid->f_cal_sp_pid = pid_sp_calc;	//addition
		
    /*init pid param */
    pid->f_param_init(pid, mode, maxout, intergral_limit, kp, ki, kd);
}	
void set_moto_current( s16 iq1, s16 iq2, s16 iq3, s16 iq4)
{
		CtrlCurrent.u8_data[0] = iq1 >> 8;
		CtrlCurrent.u8_data[1] = iq1;
		CtrlCurrent.u8_data[2] = iq2 >> 8;
		CtrlCurrent.u8_data[3] = iq2;
		CtrlCurrent.u8_data[4] = iq3 >> 8;
		CtrlCurrent.u8_data[5] = iq3;
		CtrlCurrent.u8_data[6] = iq4 >> 8;
		CtrlCurrent.u8_data[7] = iq4;
		Write_Database(ControlMotorID);
}	
void set_motor_voltage(int16_t v1, int16_t v2, int16_t v3, int16_t v4)
{

	
	CtrlVoltage.u8_data[0] = (v1>>8)&0xff;
	CtrlVoltage.u8_data[1] =    (v1)&0xff;
	CtrlVoltage.u8_data[2] = (v2>>8)&0xff;
	CtrlVoltage.u8_data[3] =    (v2)&0xff;
	CtrlVoltage.u8_data[4] = (v3>>8)&0xff;
	CtrlVoltage.u8_data[5] =    (v3)&0xff;
	CtrlVoltage.u8_data[6] = (v4>>8)&0xff;
	CtrlVoltage.u8_data[7] =    (v4)&0xff;
	
	Write_Database(ControlMotorID2);
}

void get_moto_chassis(int i)
{
		moto_chassis[i].angle = (uint16_t)(Motor2Stm[i].u8_data[0] << 8 | Motor2Stm[i].u8_data[1]);
		moto_chassis[i].speed_rpm = (int16_t)(Motor2Stm[i].u8_data[2] << 8 | Motor2Stm[i].u8_data[3]);
		moto_chassis[i].real_current = (int16_t)(Motor2Stm[i].u8_data[4] << 8 | Motor2Stm[i].u8_data[5]);
		moto_chassis[i].temperature = (uint8_t) Motor2Stm[i].u8_data[6];
}

int error = 0;

void PID_DJI_Handler(int i)
{
	float pid_out;
		
	get_moto_chassis(i);
	get_total_angle(&moto_chassis[i]);
	if(Mode[i] == Speed_Mode)
	{			
		pid_out = PID_DJI(&pid_spd[i], moto_chassis[i].speed_rpm, set_spd[i]);
		if(i == 1)
		{
			error = moto_chassis[i].total_angle - set_loc[i];
			if( abs(error) <= 100 )
			{	
				Mode[1] = Location_Mode;
				set_spd[1] = 0;
			}
		}
	}
	else if(Mode[i] == Location_Mode)
	{
		if(i == 1)
		{
			error = moto_chassis[i].total_angle - set_loc[i];
			if(abs(error) >= 100) //抓手电机 
			{	
				Mode[1] = Speed_Mode;
				if(error < 0)
					set_spd[1] = 75;
				else if(error > 0)
					set_spd[1] = -75;
			}
		}	
		pid_out = PID_DJI(&pid_loc[i], moto_chassis[i].total_angle, set_loc[i]);
		pid_out = PID_DJI(&pid_spd[i], moto_chassis[i].speed_rpm, pid_out);
	}
	if(i == 0)
		set_moto_current(pid_out,0,0,0);
	else if(i == 1)
		set_motor_voltage(pid_out,0,0,0);
}

void PID_01(void){PID_DJI_Handler(0);}
void PID_02(void){PID_DJI_Handler(1);}
void PID_03(void){}
void PID_04(void){}

void PID_Init(void)
{	
	PID_struct_init(&pid_spd[0], DELTA_PID, 8000, 16384,
								24.0f,	1.2f,	0.02f	);  //4 motos angular rate closeloop.  0.80f,	0.03f,	0.0015f	(超调)
	PID_struct_init(&pid_loc[0], DELTA_PID, 9600, 9600,
								0.80f,	0.003f,	0.000f	);  //4 motos angular location closeloop.}
	PID_struct_init(&pid_spd[1], DELTA_PID, 30000, 30000,
								60.0f,	0.001f,	0.1f	);  //4 motos angular rate closeloop.  0.80f,	0.03f,	0.0015f	(超调)
	PID_struct_init(&pid_loc[1], DELTA_PID, 50, 50,
								2.0f,	0.010f,	0.00f	);  //0.80f,	0.003f,	0.000f	);  //4 motos angular location closeloop.}
//	PID_struct_init(&pid_spd[2], DELTA_PID, 8000, 16384,
//								24.0f,	1.2f,	0.02f	);  //4 motos angular rate closeloop.  0.80f,	0.03f,	0.0015f	(超调)
//	PID_struct_init(&pid_loc[2], DELTA_PID, 9600, 9600,
//								0.80f,	0.003f,	0.000f	);  //4 motos angular location closeloop.}

//	PID_struct_init(&pid_spd[3], DELTA_PID, 8000, 16384,
//								24.0f,	1.2f,	0.02f	);  //4 motos angular rate closeloop.  0.80f,	0.03f,	0.0015f	(超调)
//	PID_struct_init(&pid_loc[3], DELTA_PID, 9600, 9600,
//								0.80f,	0.003f,	0.000f	);  //4 motos angular location closeloop.}	
}






