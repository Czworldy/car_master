/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MECANUM_H
#define __MECANUM_H

/* Includes ------------------------------------------------------------------*/
#include "sys.h"
#include "MyTypeDef.h"
/* Exported macro ------------------------------------------------------------*/

#define SPEED_STOP Speed_X = Speed_Y = Speed_Rotation = 0

/* Exported variables --------------------------------------------------------*/

extern double Speed_X;
extern double Speed_Y;
extern double Speed_Rotation;
extern double RPM_Limit;

extern struct Mecanum_State Mec_FL;		//四轮的状态参数
extern struct Mecanum_State Mec_FR;
extern struct Mecanum_State Mec_BL;
extern struct Mecanum_State Mec_BR;

extern double Mec_wheel_r_FL;
extern double Mec_wheel_r_FR;
extern double Mec_wheel_r_BL;
extern double Mec_wheel_r_BR;

extern double Mec_Len_FL;
extern double Mec_Len_FR;
extern double Mec_Len_BL;
extern double Mec_Len_BR;

/* Exported function prototype -----------------------------------------------*/
void SetSpeed(double speed_x, double speed_y, double speed_rotation);

#endif 

/**********************************END OF FILE*********************************/
