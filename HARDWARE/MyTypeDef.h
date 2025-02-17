/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MYTYPEDEF_H
#define __MYTYPEDEF_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

//点结构体
struct Point
{
	double x;
	double y;
};

struct Line_Point
{
	struct Point aim_position;
	double aim_radian;
	double speed_sta;
	double speed_max;
	double speed_end;
	s8 rotation_dir;
	u8 pid_list_index;
};

struct CCD_Line
{
	uint8_t Line_Edge_Median_Pos[4];
	struct Point Line_Move_Offset[4];
};

//路径信息结构体
struct Path_Point
{
	struct Point position;	//位置
	double speeddir;		//速度方向
	double selfdir;			//车体方向
	double speed;			//速度大小
};

//PID结构体
struct PID
{
	double p;
	double i;
	double d;
	double mend;
	double ep1;
	double ep2;
};

//每个轮子对应的状态
struct Mecanum_State
{
	uint8_t port;
	int8_t arg;				//方向系数
};

struct Color_State
{
	uint16_t rgb565;
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

enum Color_Type
{
	Color_Red = 0x01,
	Color_Green = 0x02,
	Color_Blue = 0x03,
};

struct Encoder_State
{
	int64_t Now;
	int64_t Last;
	int64_t Total;
	double Convert1;		//正转系数
	double Convert2;		//反转系数
	double Distance;
	double Radius;			//车身自转时码盘的旋转半径
	double radian;			//码盘与车身坐标系X轴正方向的夹角
	int8_t dir;				//改变正反转方向（如果是需要的方向则置1，否则置-1）
};

struct GPS_State
{
	struct Point position;	//当前坐标
	double angle;           //当前角度
	double radian;          //当前弧度
//	struct Point position;	//当前坐标	
//	double distancestep1; 	//码盘1本次前进距离
//	double distancestep2;   //码盘2本次前进距离
//	double distance1;	  	//码盘1前进距离
//	double distance2;		//码盘2前进距离
//	double angle;        	//当前角度 		
//	double radian;			//当前弧度
};

//CCD结构体
struct CCD_State
{
	float Pixel_To_Distance;
	
	uint16_t Line_ADC_Threshold;
	uint16_t Difference_ADC_Threshold;
	
	uint8_t ADC_Channel_Index;
	
	uint8_t Line_Edge_Left_Pos;
	uint8_t Line_Edge_Right_Pos;
	uint8_t Line_Edge_Median_Pos;
	uint8_t Line_Edge_Type;
	
	uint16_t ADC_Max;
	uint16_t ADC_Min;
	
	uint8_t Line_Edge_Distance;
	
};

//方向
enum Route_Direction
{
	ROUTE_FRONT = 0,
	ROUTE_BACK,
	ROUTE_LEFT,
	ROUTE_RIGHT,
};

//按键值
enum M_KeyNumType
{
    key1 = 1,
    key2,
    key3,
    key4,
    keyback,//5
    emergency,//6
    
    key5,//7
    key6,//8
    key7,//9
    key8,//10
    keyempty1,//11
    keyempty2,//12
    
    key9,//13
    key0,
    keypoint,
    keysign,
    keydelete,
    keyOK,
	keyboardtab
};
#define pageup point
#define pagedown sign

typedef enum {
 		Type_Fp64 = 1 ,
 		Type_Int64,
 		Type_Fp32 ,
 		Type_Int32,
 		Type_Uint32,
 		Type_Int16,
 		Type_Uint16,
 		Type_Int8,
 		Type_Uint8,
 		Type_Gyro,
 		Type_Encoder,
 		Type_PID,
 		Type_Mecanum,
}SD_Value_Type;


typedef enum {
		TYPE_INT8	=  1,
		TYPE_UINT8	,
		TYPE_INT16	,
		TYPE_UINT16	,
		TYPE_INT32	,
		TYPE_UINT32	,
		TYPE_INT64	,
		TYPE_UINT64	,
		TYPE_FP32		,
		TYPE_FP64		,
//     TYPE_POINTFP32,
//     TYPE_POINTFP64,
}Value_Type;

//列表显示与更改
struct Input_ListValue
{
	void *value;
	Value_Type type;
	char *name;
};

#endif 

/**********************************END OF FILE*********************************/
