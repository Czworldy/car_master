#ifndef _CAN_DATABASE_H
#define _CAN_DATABASE_H
	#include "stm32f4xx.h"
	
	#ifndef NULL
	#define NULL ((void *)0)
	#endif
	
	#define fp64 double
	#define fp32  float
	
union fi64_to_u8     //fp64型数据，或int64_t型数据转成u8型数据进行can总线发送
	{
		fp64	f64_data;
		int64_t i64_data;
		uint64_t u64_data;
		uint16_t u16_data[4];
		int16_t i16_data[4];
		uint8_t u8_data[8];
	};
	
	union fi32_to_u8     //fp32型数据，或int32_t型数据转成u8型数据进行can总线发送
	{
		fp32	f32_data;
		int32_t i32_data;
		uint32_t u32_data;
		int16_t i16_data[2];
		uint8_t u8_data[4];
	};
	
	union u16_to_u8
	{
		uint16_t u16_data;
		uint8_t u8_data[2];
	};

	#define READ_ONLY  0	//主控读，外设写
	#define WRITE_ONLY 1	//主控写，外设读
	#define Control    0  //命令类型
	#define Message    1	//信息类型	
	#define MotorBaseID 0x200

/*所有命令对应的ID号列表*/
/*
ID位号	[	(GS:GPS Slave  MS:Motor Slave)							]
NO.7	[			0--GS			|		1--Others				]
NO.6	[	0--MOSI		|	1--MISO	|	0--MS MOSI	|	1--Others	]
NO.5~0	[	ID numbers				|	ID numbers  &  Others		]
	
	Others：
		B11-000-xxx 主控&&ISO协主控通信ID
		B11-001-xxx 主控&&camera通信ID--MISO
		B11-011-xxx 主控&&camera通信ID--MOSI
		B11-010-xxx 主控与relay通信ID
		B11-100-xxx 主控与部分协主控通信ID   包括：超声波板
*/
	typedef enum
	{
		W_MaxSpeed_ID = 0x1C,
		W_StartMoving_ID = 0x1D,
		W_DelayTime_ID = 0x1E,
			
		ControlMotorID = 0x200,
		ControlMotorID2 = 0x1FF,
		MOTOR0 = MotorBaseID + 1,
		MOTOR1 = MotorBaseID + 2,
		MOTOR2 = MotorBaseID + 3,
		MOTOR3 = MotorBaseID + 4,
		
		PanTiltID = 0x205,
		
		MISO_MR2_WAKEUP_ID=0x01,
		MISO_MR2_RISE_ID=0xD0,
		MISO_ANG_ID = 0xcc,
		MOSI_RestartGyro_ID = 0xce,
		S_GYRO_RAD_ID	= 0x52,
		MISO_CYLINDER_ID = 0xd1,
		MISO_ANG_UP = 0x02,
		MISO_ANG_DOWN = 0x03,
	}ID_NUMDEF;	
	
	/*主控和GPS协主控之间的命令格式*/
	typedef enum
	{
		NO_COMMAND			= 0x00,
		//M_G_CMD_ID下的命令
		GPS_READ			= 0x01,		//索取GPS信息命令
		CHECK_FLOAT			= 0x02,		//通知GPS协主控校准陀螺仪零漂命令
		GYRO_INIT			= 0x03,		//通知GPS协主控标定陀螺仪命令
		ENC_L_INIT			= 0x04,		//通知GPS协主控标定码盘正反转系数命令
		ENC_R_INIT			= 0x05,		//通知GPS协主控标定码盘旋转半径命令
		//G_M_CMD_ID下的命令
		CF_NORMAL			= 0x06,
		CF_CHANGED			= 0x07,
		CF_ERROR			= 0x08
	}COM_TYPE;
	
	typedef enum
	{
		FIND_ONCE = 0x01,
		FIND_CONTINIOUS = 0x02,
		FIND_NO_SEND = 0x03,
		FIND_STOP = 0x00
	}CAMERA_CMD;
	
	typedef struct
	{
		uint8_t  Data_type;
		ID_NUMDEF  Data_ID;
		uint8_t* Data_ptr;
		uint8_t  Data_length;
		
		//在can总线接到数据后，调用的函数
		void (*MenuFunc)(void);			//入口函数		
		uint8_t  Channel;
		uint8_t  Fifo_num;			//在接收方将该ID配置的fifo号
	}Can_Data;

	
	extern uint8_t Can_Data_Num;
	extern Can_Data Can_Database[];
	extern uint16_t HASH_TABLE[];
	extern union fi64_to_u8 CtrlCurrent;
	extern union fi64_to_u8 Motor2Stm[];
	extern union fi64_to_u8 CtrlVoltage;

	
	void Hash_Table_init(void);
	void Write_Database(ID_NUMDEF ID_NUM);
typedef union 
{
    u8 d[2];
    s16 v;
}u8tos16_t;

typedef struct
{
		u8tos16_t	x_or_angle;
		u8tos16_t	y_or_dis;
		u8tos16_t	z;
	  u8tos16_t	turn;  
		int time_flag;
}camera_t;

extern union fi64_to_u8 camera_data1;
extern uint8_t MISO_FAN_GRAB_STATUS;
extern uint8_t M0SI_FAN_GRAB;

#endif


