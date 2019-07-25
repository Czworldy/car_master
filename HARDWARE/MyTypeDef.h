/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MYTYPEDEF_H
#define __MYTYPEDEF_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

//��ṹ��
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

//·����Ϣ�ṹ��
struct Path_Point
{
	struct Point position;	//λ��
	double speeddir;		//�ٶȷ���
	double selfdir;			//���巽��
	double speed;			//�ٶȴ�С
};

//PID�ṹ��
struct PID
{
	double p;
	double i;
	double d;
	double mend;
	double ep1;
	double ep2;
};

//ÿ�����Ӷ�Ӧ��״̬
struct Mecanum_State
{
	uint8_t port;
	int8_t arg;				//����ϵ��
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
	double Convert1;		//��תϵ��
	double Convert2;		//��תϵ��
	double Distance;
	double Radius;			//������תʱ���̵���ת�뾶
	double radian;			//�����복������ϵX��������ļн�
	int8_t dir;				//�ı�����ת�����������Ҫ�ķ�������1��������-1��
};

struct GPS_State
{
	struct Point position;	//��ǰ����
	double angle;           //��ǰ�Ƕ�
	double radian;          //��ǰ����
//	struct Point position;	//��ǰ����	
//	double distancestep1; 	//����1����ǰ������
//	double distancestep2;   //����2����ǰ������
//	double distance1;	  	//����1ǰ������
//	double distance2;		//����2ǰ������
//	double angle;        	//��ǰ�Ƕ� 		
//	double radian;			//��ǰ����
};

//CCD�ṹ��
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

//����
enum Route_Direction
{
	ROUTE_FRONT = 0,
	ROUTE_BACK,
	ROUTE_LEFT,
	ROUTE_RIGHT,
};

//����ֵ
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

//�б���ʾ�����
struct Input_ListValue
{
	void *value;
	Value_Type type;
	char *name;
};

#endif 

/**********************************END OF FILE*********************************/
