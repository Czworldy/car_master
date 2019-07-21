#ifndef __SERVO_H
#define __SERVO_H

#include "sys.h"

#define Servo_Size 4

extern u8 Servo_Duty[];
extern u8 Servo_Intense_Index;

void Servo_Disable(void);
void Servo_PWM_SetDuty(void);

void Servo_Original_Point_Bend(void);
void Servo_Product_Point_Bend(void);
void Servo_QR_Code_Stretch(void);
void Servo_Stock_Point_Grab_Off_Panpilt_Straight(void);
void Servo_Stock_Point_Grab_On_Panpilt_Straight(u8 k);
void Servo_Stock_Point_Grab_On_Panpilt_Straight_Lift(u8 k);
void Servo_Working_Point_Grab_On_High_Panpilt_Skew(u8 k);
void Servo_Working_Point_Grab_On_High_Panpilt_Straight(u8 k);
void Servo_Working_Point_Grab_On_Low_Panpilt_Straight(u8 k);
void Servo_Working_Point_Grab_Off_Low_Panpilt_Straight(void);
void Servo_Working_Point_Grab_Off_High_Panpilt_Straight(void);
void Servo_Stock_Point_Grab_Off_Panpilt_Skew(void);
void Servo_Working_Point_Grab_Off_Middle_Panpilt_Straight(void);
void Servo_Working_Point_Grab_Off_Middle_Panpilt_Skew(void);
void Servo_Working_Point_Grab_Off_Down_Panpilt_Straight(void);
void Servo_Working_Point_Grab_On_Down_Panpilt_Straight(u8 k);
void Servo_Product_Point_Grab_On_Middle_Panpilt_Skew(u8 k);
void Servo_Product_Point_Grab_On_Middle_Panpilt_Straight(u8 k);
void Servo_Product_Point_Grab_On_Down_Panpilt_Straight(u8 k);
void Servo_Product_Point_Grab_Off_Down_Panpilt_Straight(void);

#endif
