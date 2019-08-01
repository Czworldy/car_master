#include "camera.h"
#include "usart.h"
#include "delay.h"

u8 Camera_Mode = 0;
u8 Color_Hash_Table[3] = {0};
u8 Color_Res[10] = {0};
u8 Is_Color_Finished = 0;

u8 Product_Calibration_Sign = 0;

void Camera_Set_Mode(u8 mode)
{
	Camera_Mode = mode;
	
	USART_SendByte(USART2, 0x00);
	delay_ms(10);
	USART_ClearFlag(USART2, USART_FLAG_RXNE);
	switch (mode)
	{
		case 1:
			Is_Color_Finished = 0;
			Color_Hash_Table[0] = Color_Hash_Table[1] = Color_Hash_Table[2] = 0;
			Color_Res[0] = Color_Res[1] = Color_Res[2] = 0;
			Camera_RxBuffer[0] = Camera_RxBuffer[1] = Camera_RxBuffer[2] = Camera_RxBuffer[3] = 0x00;
			break;
		case 2:
			Is_Color_Finished = 0;
			Color_Hash_Table[0] = Color_Hash_Table[1] = Color_Hash_Table[2] = 0;
			Color_Res[0] = Color_Res[1] = Color_Res[2] = 0;
			Camera_RxBuffer[0] = Camera_RxBuffer[1] = Camera_RxBuffer[2] = Camera_RxBuffer[3] = 0x00;
			break;
		case 3:
		case 4:
		case 5:
		case 6:
			Product_Calibration_Sign = 0;
			break;
		default:
			break;
	}
	USART_SendByte(USART2, mode);
	delay_ms(10);
}
