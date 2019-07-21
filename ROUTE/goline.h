#ifndef __GOLINE_H
#define __GOLINE_H

#include "sys.h"
#include "MyTypeDef.h"

extern struct Line_Point Aim_Line_Point;
extern struct Point Sta_Point;
extern struct Point End_Point;
extern double Aim_Radian;
extern double Speed_Sta;
extern double Speed_End;
extern double Speed_Max;
extern double Line_Angle;
extern double Line_Length;
extern double Acc_Dis, Dec_Dis;
extern double Acc_Dis_Rate, Dec_Dis_Rate;
extern double Acc, Dec;
extern s8 Rotation_Dir;
extern u8 PID_List_Index;

void SetLine(struct Line_Point *line_point);
void GoLine(void);

#endif
