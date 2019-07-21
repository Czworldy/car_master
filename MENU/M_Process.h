#ifndef __M_PROCESS_H
#define __M_PROCESS_H

#include "sys.h"
#include "MyTypeDef.h"

extern struct Line_Point QR_Code_Point[];

extern u8 Working_Point_Index[];
extern u8 Product_Point_Index[];

extern struct Line_Point Original_Point;
extern struct Line_Point Color_Check_Point;

extern u8 Product_Point_Camera[];
extern double Camera_Pixel_To_Distance[];
extern struct GPS_State process_GPS_Offset[];

extern struct Line_Point Stock_Point_Middle;
extern struct Line_Point Stock_Point_Offset_Slow[];
extern struct Line_Point Stock_Point_Offset_Fast[];
extern struct Line_Point Stock_Point_Grab_Offset;
extern struct Line_Point Stock_Point_Leave_Offset;

extern struct Line_Point Working_Point_Drop_Middle;
extern struct Line_Point Working_Point_Drop_Offset_Slow[];
extern struct Line_Point Working_Point_Drop_Offset_Fast[];
extern struct Line_Point Working_Point_Drop_Leave_Offset;

extern struct Line_Point Working_Point_Take_Middle;
extern struct Line_Point Working_Point_Take_Offset_Slow[];
extern struct Line_Point Working_Point_Take_Offset_Fast[];
extern struct Line_Point Working_Point_Take_Grab_Offset;

extern struct Line_Point Product_Point_Middle;
extern struct Line_Point Product_Point_Offset_Slow[];
extern struct Line_Point Product_Point_Offset_Fast[];
extern struct Line_Point Product_Point_Leave_Offset;

extern struct Line_Point CCD_Adjustment;

extern struct Line_Point Stock_Point_CCD_Middle_Slow;
extern struct Line_Point Stock_Point_CCD_Middle_Fast;
extern struct Line_Point Stock_Point_CCD_Middle_Offset[];
extern struct Line_Point Stock_Point_CCD_Grab_Offset;
extern struct Line_Point Stock_Point_CCD_Leave_Offset;
extern struct CCD_Line Stock_Point_CCD_Line[];

extern struct Line_Point Working_Point_Drop_CCD_Middle_Slow;
extern struct Line_Point Working_Point_Drop_CCD_Middle_Fast;
extern struct Line_Point Working_Point_Drop_CCD_Middle_Offset[];
extern struct Line_Point Working_Point_Drop_CCD_Leave_Offset;
extern struct CCD_Line Working_Point_Drop_CCD_Line[];

extern struct Line_Point Working_Point_Take_CCD_Slow[];
extern struct Line_Point Working_Point_Take_CCD_Fast[];
extern struct Line_Point Working_Point_Take_CCD_Grab_Offset;

extern struct Line_Point Product_Point_CCD_Middle_Slow;
extern struct Line_Point Product_Point_CCD_Middle_Fast;
extern struct Line_Point Product_Point_CCD_Middle_Offset[];
extern struct Line_Point Product_Point_CCD_Leave_Offset;
extern struct CCD_Line Product_Point_CCD_Line[];

void process_Show_QR_Code(u16 x,u16 y,u8 num);
void process_Line_Point(struct Line_Point *aim_line_point);
void process_Line(void);
void process_Servo(void);
void process_QR_Code(void);
void process_Camera(void);
void process_Test(void);
void process_All(void);
void process_Auto(u8 auto_cnt);
void process_Auto_RGB(void);
u8 process_CCD_Auto(u8 auto_cnt);
void process_CCD_Auto_RGB(void);
//void process_Auto_BGR(void);
//void process_Auto(u8 process_type);
//void process_Calibration_RGB(void);
//void process_Calibration_BGR(void);
//void process_Calibration(u8 process_type);
void process_Point_Test(void);

#endif
