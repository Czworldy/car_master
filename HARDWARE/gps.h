#ifndef __GPS_H
#define __GPS_H

#include "sys.h"
#include "MyTypeDef.h"

#define GPS_STATE_SIZE	2

extern struct GPS_State GPS_List[];
extern struct GPS_State GPS_Offset;

void GPS_Clear(void);
void GPS_Init(float x, float y);
void GPS_Gyro_Set_Zero(void);

#endif
