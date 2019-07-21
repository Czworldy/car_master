#ifndef __CAMERA_H
#define __CAMERA_H

#include "sys.h"

extern u8 Camera_Mode;
extern u8 Color_Hash_Table[];
extern u8 Color_Res[];
extern u8 Is_Color_Finished;

extern u8 Product_Calibration_Sign;

void Camera_Set_Mode(u8 mode);

#endif
