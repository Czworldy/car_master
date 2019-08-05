#ifndef _CAN_DATABASE_H
#define _CAN_DATABASE_H
	#include "stm32f4xx.h"
	
	#ifndef NULL
	#define NULL ((void *)0)
	#endif
	
	#define fp64 double
	#define fp32  float
	#define deviceOffset 0x1FF
	
union fi64_to_u8     //fp64�����ݣ���int64_t������ת��u8�����ݽ���can���߷���
	{
		fp64	f64_data;
		int64_t i64_data;
		uint64_t u64_data;
		uint16_t u16_data[4];
		int16_t i16_data[4];
		uint8_t u8_data[8];
	};
	
	union fi32_to_u8     //fp32�����ݣ���int32_t������ת��u8�����ݽ���can���߷���
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

	#define READ_ONLY  0	//���ض�������д
	#define WRITE_ONLY 1	//����д�������
	#define Control    0  //��������
	#define Message    1	//��Ϣ����	
	#define MotorBaseID 0x200

/*���������Ӧ��ID���б�*/
/*
IDλ��	[	(GS:GPS Slave  MS:Motor Slave)							]
NO.7	[			0--GS			|		1--Others				]
NO.6	[	0--MOSI		|	1--MISO	|	0--MS MOSI	|	1--Others	]
NO.5~0	[	ID numbers				|	ID numbers  &  Others		]
	
	Others��
		B11-000-xxx ����&&ISOЭ����ͨ��ID
		B11-001-xxx ����&&cameraͨ��ID--MISO
		B11-011-xxx ����&&cameraͨ��ID--MOSI
		B11-010-xxx ������relayͨ��ID
		B11-100-xxx �����벿��Э����ͨ��ID   ��������������
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
		
		//��can���߽ӵ����ݺ󣬵��õĺ���
		void (*MenuFunc)(void);			//��ں���		
		uint8_t  Channel;
		uint8_t  Fifo_num;			//�ڽ��շ�����ID���õ�fifo��
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


