#ifndef __M_GAME_FUNC_H
#define __M_GAME_FUNC_H

#include "sys.h"
#include "MyTypeDef.h"

void Return_Any_Point(struct Line_Point *aim_line_point, double distance_err, double angle_err, u8 goLine_timeout);
void CCD_Adjust(struct CCD_Line ccd_line, uint8_t ccdx, uint8_t ccdy);
void CCD_Adjust_to_GPS(struct CCD_Line ccd_line, uint8_t ccdx, uint8_t ccdy, struct Point std_point);
void CCD_Adjust_to_GPS_X(struct CCD_Line ccd_line, uint8_t ccdx, struct Point std_start_pos);
void CCD_Adjust_to_GPS_Y(struct CCD_Line ccd_line, uint8_t ccdy, struct Point std_start_pos);
struct Line_Point Color_Judge(void);
void pos_Grab(void);
void pos_Put(void);
void Camera_Cvt_GPS(u8 point, int8_t cam_x, int8_t cam_y);
void Put_Camera_Cvt_GPS(u8 color, int8_t cam_x, int8_t cam_y);

extern struct Line_Point Corner_Point[];
extern u8 black_Mask;
extern u8 is_This_Black_Noput;
extern u8 pos_Grab_cnt;
extern u8 last_Black;
extern u8 is_put_balck;

#endif

