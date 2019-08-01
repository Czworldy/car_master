#ifndef __ALL_H
#define __ALL_H

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "delay.h"
#include "sys.h"

#include "led.h"
#include "exti.h"
#include "key.h"
#include "motor.h"
#include "servo.h"
#include "timer.h"
#include "usart.h"
#include "camera.h"
#include "handle.h"
#include "qr_code.h"
#include "gps.h"
#include "lcd.h"
#include "font.h"
#include "touch.h"
#include "ccd.h"
#include "mecanum.h"
#include "encoder.h"
#include "can.h"
#include "can_database.h"
#include "can_pid.h"

#include "MyTypeDef.h"
#include "M_TypeDef.h"

#include "M_List.h"
#include "M_Func.h"
#include "M_Sys.h"
#include "M_Route.h"
#include "M_Process.h"
#include "M_Game_Func.h"

#include "goline.h"
#include "keep.h"
#include "pid.h"

#include "mymath.h"
#include "arm_math.h"

#define PanTilt_Zero 1500
#define Grab     PEout(2)    
#define Cylinder PEout(5)

#define Cylin_Up 0
#define Cylin_Down 1
#define Grab_Open 1
#define Grab_Close 0

#endif
