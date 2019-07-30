
#include "all.h"

uint8_t Can_Data_Num=0;
union fi64_to_u8 CtrlCurrent;
union fi64_to_u8 Motor2Stm[4];
union fi64_to_u8 CtrlVoltage;

//SLAVER--M3508 or M2006
//新加ID时，在ID_NUMDEF中定义相应ID的意义
/**/
Can_Data Can_Database[]=
{
	{WRITE_ONLY,    ControlMotorID,		(uint8_t*)(&CtrlCurrent.u8_data),  			8,         	NULL,            2,        CAN_Filter_FIFO0},
	{WRITE_ONLY,    ControlMotorID2,	(uint8_t*)(&CtrlVoltage.u8_data),  			8,         	NULL,            2,        CAN_Filter_FIFO1},
	{READ_ONLY,     MOTOR0,            	(uint8_t*)(&Motor2Stm[0].u8_data), 			8,          PID_01,          2,        CAN_Filter_FIFO1},
//	{READ_ONLY,     MOTOR2,            	(uint8_t*)(&Motor2Stm[1].u8_data), 			8,          PID_02,          2,        CAN_Filter_FIFO0},
//	{READ_ONLY,     MOTOR3,            	(uint8_t*)(&Motor2Stm[2].u8_data), 			8,          PID_03,          2,        CAN_Filter_FIFO1},
//	{READ_ONLY,     MOTOR4,            	(uint8_t*)(&Motor2Stm[3].u8_data),			8,          PID_04,          2,        CAN_Filter_FIFO0},
	
	{READ_ONLY,     PanTiltID,          (uint8_t*)(&Motor2Stm[1].u8_data), 			8,          PID_02,          2,        CAN_Filter_FIFO0},

//	{READ_ONLY,     MISO_ANG_ID,       	(uint8_t*)(&Angle.u8_data),        			4,          PID_Ang,         1,        CAN_Filter_FIFO1},
//	{WRITE_ONLY,    MOSI_RestartGyro_ID,(uint8_t*)(&RestartFlag),   				1,          NULL,            1,        CAN_Filter_FIFO1},
//	{READ_ONLY,	    S_GYRO_RAD_ID,				(uint8_t*)(&MISO_GYRO_RAD.u8_data),	8,			S_GYRO_RAD_FUNC, 1,				CAN_Filter_FIFO0},

//	{READ_ONLY,     MISO_MR2_WAKEUP_ID, (uint8_t*)(&MR2_StartFlag),  			    1,          DOG_GO,      	 1,      	CAN_Filter_FIFO1},
//	
//	{WRITE_ONLY,    MISO_MR2_RISE_ID,  	(uint8_t*)(&MR2_RiseFlag),  			    1,          NULL,   		 1,  		 	CAN_Filter_FIFO1},
//	
//	{WRITE_ONLY,	MISO_CYLINDER_ID,	(uint8_t*)(&Cylinder_Flag),					1,			NULL,			 1,				CAN_Filter_FIFO1},

//	{READ_ONLY,     MISO_ANG_UP,       	(uint8_t*)(&Angle_up.u8_data),        		2,          PID_Ang_up,      1,        CAN_Filter_FIFO1},
//	{READ_ONLY,     MISO_ANG_DOWN,      (uint8_t*)(&Angle_down.u8_data),        	2,          PID_Ang_down,    1,        CAN_Filter_FIFO1},

//	{READ_ONLY,		MISO_START_ID,				(uint8_t*)(&Start_Flag),								1,					DOG_GO						1,				CAN_Filter_FIFO0},

};

//HASH_TABLE初始值为255，认为Can_Data_Num值小于256，即设备数少于256个
uint16_t HASH_TABLE[1000]={999};

void Hash_Table_init(void)
{
	int i;
	
	Can_Data_Num = sizeof(Can_Database) / sizeof(Can_Database[0]);
	for(i=0;i<1000;i++)
	{
		HASH_TABLE[i] = 999;
	}
	for(i=0;i<Can_Data_Num;i++)
	{
		HASH_TABLE[Can_Database[i].Data_ID] = i;
	}
}

void Write_Database(ID_NUMDEF ID_NUM)
{
	uint8_t j;
	CanTxMsg TxMessage;
	/* Check the parameters */
	if((HASH_TABLE[ID_NUM] >= Can_Data_Num)&&(Can_Database[HASH_TABLE[ID_NUM]].Data_type!=WRITE_ONLY))
	{
// 		LED4_on;
		return;
	}
	
	TxMessage.StdId=Can_Database[HASH_TABLE[ID_NUM]].Data_ID;
	TxMessage.ExtId=0;
	TxMessage.IDE=CAN_ID_STD;
	TxMessage.RTR=CAN_RTR_DATA;
	TxMessage.DLC=Can_Database[HASH_TABLE[ID_NUM]].Data_length;
	
	for(j=0;j<Can_Database[HASH_TABLE[ID_NUM]].Data_length;j++)
	{
		TxMessage.Data[j]=(*(Can_Database[HASH_TABLE[ID_NUM]].Data_ptr+j));
	}
	
	Can_SendData(&TxMessage,Can_Database[HASH_TABLE[ID_NUM]].Channel);
	
}
