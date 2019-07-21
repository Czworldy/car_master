#include "servo.h"
#include "usart.h"

u8 Servo_Duty[Servo_Size] = {0};
u8 Servo_Intense_Index = 0;

void Servo_Disable(void)
{
#ifdef BSP_USING_UART4_DMA
	GPS_TxBuffer[0] = 0xFF;
	GPS_TxBuffer[1] = 0xAB;
	GPS_TxBuffer[2] = 0x00;
	GPS_TxBuffer[3] = 0xAB;
	GPS_TxBuffer[8] = 0x00;
	DMA_SetCurrDataCounter(UART4_DMA_TX_STREAM, GPS_TxBufferSize);
	DMA_Cmd(UART4_DMA_TX_STREAM, ENABLE);
#endif
}

void Servo_PWM_SetDuty(void)
{
#ifdef BSP_USING_UART4_DMA
	GPS_TxBuffer[0] = 0xFF;
	GPS_TxBuffer[1] = 0xAB;
	GPS_TxBuffer[2] = 0x01;
	GPS_TxBuffer[3] = 0xAB;
	GPS_TxBuffer[4] = Servo_Duty[0];
	GPS_TxBuffer[5] = Servo_Duty[1];
	GPS_TxBuffer[6] = Servo_Duty[2];
	GPS_TxBuffer[7] = Servo_Duty[3];
	GPS_TxBuffer[8] = 0x00;
	DMA_SetCurrDataCounter(UART4_DMA_TX_STREAM, GPS_TxBufferSize);
	DMA_Cmd(UART4_DMA_TX_STREAM, ENABLE);
#endif
}

void Servo_Original_Point_Bend(void)
{
	Servo_Duty[0] = 10;
	Servo_Duty[1] = 36;
	Servo_Duty[2] = 50;
	Servo_Duty[3] = 39;
	Servo_PWM_SetDuty();
}

void Servo_Product_Point_Bend(void)
{
	Servo_Duty[0] = 10;
	Servo_Duty[1] = 36;
	Servo_Duty[2] = 50;
	Servo_Duty[3] = 39;
	Servo_PWM_SetDuty();
}

void Servo_QR_Code_Stretch(void)
{
	Servo_Duty[0] = 12;
	Servo_Duty[1] = 50;
	Servo_Duty[2] = 34;
	Servo_Duty[3] = 27;
	Servo_PWM_SetDuty();
}

void Servo_Stock_Point_Grab_Off_Panpilt_Straight(void)
{
	Servo_Duty[0] = 10;
	Servo_Duty[1] = 50;
	Servo_Duty[2] = 34;
	Servo_Duty[3] = 27;
	Servo_PWM_SetDuty();
}

void Servo_Stock_Point_Grab_On_Panpilt_Straight(u8 k)
{
	if (k != 0)
	{
		Servo_Duty[0] = 10;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 34;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
	}
	else
	{
		Servo_Duty[0] = 10;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 34;
		Servo_Duty[3] = 39;
		Servo_PWM_SetDuty();
	}
}

void Servo_Stock_Point_Grab_On_Panpilt_Straight_Lift(u8 k)
{
	if (k)
	{
		Servo_Duty[0] = 10;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 34;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
	}
	else
	{
		Servo_Duty[0] = 10;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 34;
		Servo_Duty[3] = 39;
		Servo_PWM_SetDuty();
	}
}

void Servo_Working_Point_Grab_On_High_Panpilt_Skew(u8 k)
{
	if (k == Servo_Intense_Index)
	{
		Servo_Duty[0] = 28;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 34;
		Servo_Duty[3] = 39;
		Servo_PWM_SetDuty();
	}
	else
	{
		Servo_Duty[0] = 28;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 34;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
	}
}

void Servo_Working_Point_Grab_On_High_Panpilt_Straight(u8 k)
{
	if (k == Servo_Intense_Index)
	{
		Servo_Duty[0] = 30;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 34;
		Servo_Duty[3] = 39;
		Servo_PWM_SetDuty();
	}
	else
	{
		Servo_Duty[0] = 30;
		Servo_Duty[1] = 50;
		Servo_Duty[2] = 34;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
	}
}

void Servo_Working_Point_Grab_On_Low_Panpilt_Straight(u8 k)
{
	if (k == Servo_Intense_Index)
	{
		Servo_Duty[0] = 30;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 13;
		Servo_Duty[3] = 39;
		Servo_PWM_SetDuty();
	}
	else
	{
		Servo_Duty[0] = 30;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 13;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
	}
}

void Servo_Working_Point_Grab_Off_Low_Panpilt_Straight(void)
{
	Servo_Duty[0] = 30;
	Servo_Duty[1] = 33;
	Servo_Duty[2] = 13;
	Servo_Duty[3] = 27;
	Servo_PWM_SetDuty();
}

void Servo_Working_Point_Grab_Off_High_Panpilt_Straight(void)
{
	Servo_Duty[0] = 30;
	Servo_Duty[1] = 50;
	Servo_Duty[2] = 34;
	Servo_Duty[3] = 27;
	Servo_PWM_SetDuty();
}

void Servo_Stock_Point_Grab_Off_Panpilt_Skew(void)
{
	Servo_Duty[0] = 12;
	Servo_Duty[1] = 50;
	Servo_Duty[2] = 34;
	Servo_Duty[3] = 27;
	Servo_PWM_SetDuty();
}

void Servo_Working_Point_Grab_Off_Middle_Panpilt_Straight(void)
{
	Servo_Duty[0] = 30;
	Servo_Duty[1] = 33;
	Servo_Duty[2] = 14;
	Servo_Duty[3] = 27;
	Servo_PWM_SetDuty();
}

void Servo_Working_Point_Grab_Off_Middle_Panpilt_Skew(void)
{
	Servo_Duty[0] = 28;
	Servo_Duty[1] = 33;
	Servo_Duty[2] = 14;
	Servo_Duty[3] = 27;
	Servo_PWM_SetDuty();
}

void Servo_Working_Point_Grab_Off_Down_Panpilt_Straight(void)
{
	Servo_Duty[0] = 30;
	Servo_Duty[1] = 33;
	Servo_Duty[2] = 13;
	Servo_Duty[3] = 27;
	Servo_PWM_SetDuty();
}

void Servo_Working_Point_Grab_On_Down_Panpilt_Straight(u8 k)
{
	if (k == Servo_Intense_Index)
	{
		Servo_Duty[0] = 30;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 14;
		Servo_Duty[3] = 39;
		Servo_PWM_SetDuty();
	}
	else
	{
		Servo_Duty[0] = 30;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 14;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
	}
}

void Servo_Product_Point_Grab_On_Middle_Panpilt_Skew(u8 k)
{
	if (k == Servo_Intense_Index)
	{
		Servo_Duty[0] = 12;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 15;
		Servo_Duty[3] = 39;
		Servo_PWM_SetDuty();
	}
	else
	{
		Servo_Duty[0] = 12;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 15;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
	}
}

void Servo_Product_Point_Grab_On_Middle_Panpilt_Straight(u8 k)
{
	if (k == Servo_Intense_Index)
	{
		Servo_Duty[0] = 10;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 15;
		Servo_Duty[3] = 39;
		Servo_PWM_SetDuty();
	}
	else
	{
		Servo_Duty[0] = 10;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 15;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
	}
}

void Servo_Product_Point_Grab_On_Down_Panpilt_Straight(u8 k)
{
	if (k == Servo_Intense_Index)
	{
		Servo_Duty[0] = 10;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 14;
		Servo_Duty[3] = 39;
		Servo_PWM_SetDuty();
	}
	else
	{
		Servo_Duty[0] = 10;
		Servo_Duty[1] = 33;
		Servo_Duty[2] = 14;
		Servo_Duty[3] = 37;
		Servo_PWM_SetDuty();
	}
}

void Servo_Product_Point_Grab_Off_Down_Panpilt_Straight(void)
{
	Servo_Duty[0] = 10;
	Servo_Duty[1] = 33;
	Servo_Duty[2] = 14;
	Servo_Duty[3] = 27;
	Servo_PWM_SetDuty();
}
