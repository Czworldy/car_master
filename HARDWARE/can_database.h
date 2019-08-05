#ifndef _CAN_DATABASE_H
#define _CAN_DATABASE_H
	#include "stm32f4xx.h"
	
	#ifndef NULL
	#define NULL ((void *)0)
	#endif
	
	#define fp64 double
	#define fp32  float
	#define deviceOffset 0x1FF
	
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
		ControlMotorID = 0x200,
		ControlMotorID2 = 0x1FF,
		MOTOR0 = MotorBaseID + 1,
		MOTOR1 = MotorBaseID + 2,
		MOTOR2 = MotorBaseID + 3,
		MOTOR3 = MotorBaseID + 4,
		
		PanTiltID = 0x205,
	}ID_NUMDEF;	
	
	
	
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

#endif


