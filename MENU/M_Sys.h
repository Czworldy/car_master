/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MENUSYS_H
#define __MENUSYS_H

/* Includes ------------------------------------------------------------------*/
#include "sys.h"
/* variable ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
void sys_CCD(void);
//void sys_Gyro(void);
void sys_Encoder(void);
void sys_GPS(void);
void sys_Mecanum(void);
void sys_Servo(void);
void sys_QR_Code(void);
void sys_Camera(void);
void sys_PanTilt(void);

#endif 

/**********************************END OF FILE*********************************/
