#ifndef __M_GAME_FUNC_H
#define __M_GAME_FUNC_H

#include "sys.h"
#include "MyTypeDef.h"

void Return_Any_Point(struct Line_Point *aim_line_point, double distance_err, double angle_err);
void CCD_Adjust(struct CCD_Line ccd_line, uint8_t ccdx, uint8_t ccdy);


#endif
