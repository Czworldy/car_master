
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
	{WRITE_ONLY,    ControlMotorID2,	(uint8_t*)(&CtrlVoltage.u8_data),  			8,         	NULL,            2,        CAN_Filter_FIFO1},
	{WRITE_ONLY,    ControlMotorID,		(uint8_t*)(&CtrlCurrent.u8_data),  			8,         	NULL,            2,        CAN_Filter_FIFO0},
	{READ_ONLY,     MOTOR0,            	(uint8_t*)(&Motor2Stm[0].u8_data), 			8,          PID_01,          2,        CAN_Filter_FIFO1},
	{READ_ONLY,     PanTiltID,          (uint8_t*)(&Motor2Stm[1].u8_data), 			8,          PID_02,          2,        CAN_Filter_FIFO0},
};

uint16_t HASH_TABLE[10]={10};

void Hash_Table_init(void)
{
	int i;
	
	Can_Data_Num = sizeof(Can_Database) / sizeof(Can_Database[0]);
	for(i=0;i<10;i++)
	{
		HASH_TABLE[i] = 10;
	}
	for(i=0;i<Can_Data_Num;i++)
	{
		HASH_TABLE[Can_Database[i].Data_ID - deviceOffset] = i;
	}
}

void Write_Database(ID_NUMDEF ID_NUM)
{
	uint8_t j;
	CanTxMsg TxMessage;
	/* Check the parameters */
	if((HASH_TABLE[ID_NUM - deviceOffset] >= Can_Data_Num)&&(Can_Database[HASH_TABLE[ID_NUM - deviceOffset]].Data_type!=WRITE_ONLY))
	{
// 		LED4_on;
		return;
	}
	
	TxMessage.StdId=Can_Database[HASH_TABLE[ID_NUM - deviceOffset]].Data_ID;
	TxMessage.ExtId=0;
	TxMessage.IDE=CAN_ID_STD;
	TxMessage.RTR=CAN_RTR_DATA;
	TxMessage.DLC=Can_Database[HASH_TABLE[ID_NUM - deviceOffset]].Data_length;
	
	for(j=0;j<Can_Database[HASH_TABLE[ID_NUM - deviceOffset]].Data_length;j++)
	{
		TxMessage.Data[j]=(*(Can_Database[HASH_TABLE[ID_NUM - deviceOffset]].Data_ptr+j));
	}
	
	Can_SendData(&TxMessage,Can_Database[HASH_TABLE[ID_NUM - deviceOffset]].Channel);
	
}
