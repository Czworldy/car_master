#ifndef __M_GAME_FUNC_H
#define __M_GAME_FUNC_H

#include "sys.h"
#include "MyTypeDef.h"

void Return_Any_Point(struct Line_Point *aim_line_point, double distance_err, double angle_err);
void CCD_Adjust(struct CCD_Line ccd_line, uint8_t ccdx, uint8_t ccdy);
void CCD_Adjust_to_GPS(struct CCD_Line ccd_line, uint8_t ccdx, uint8_t ccdy, struct Point std_point);
void CCD_Adjust_to_GPS_X(struct CCD_Line ccd_line, uint8_t ccdx, struct Point std_start_pos);
void CCD_Adjust_to_GPS_Y(struct CCD_Line ccd_line, uint8_t ccdy, struct Point std_start_pos);
struct Line_Point Color_Judge(void);
void pos_Grab(void);
void pos_Put(void);


extern struct Line_Point Corner_Point[];
extern struct CCD_Line Corner_Point_CCD_Line[];
extern u8 black_mask;

#endif

