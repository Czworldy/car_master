/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PID_H
#define __PID_H

/* Includes ------------------------------------------------------------------*/
#include "sys.h"
#include "MyTypeDef.h"
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

extern struct PID Pid_List[];
extern double Vout[5];
extern uint8_t Pid_List_Size;

/* Exported function prototype -----------------------------------------------*/

void PID_Clear(void);
double PID(double Error,struct PID *pid);
double AnglePID(double Error,struct PID *pid);
double DistancePID(double Error,struct PID *pid);

#endif 

/**********************************END OF FILE*********************************/
