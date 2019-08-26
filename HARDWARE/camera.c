#include "camera.h"
#include "usart.h"
#include "delay.h"

u8 Camera_Mode = 0;
u8 Color_Hash_Table[3] = {0};
u8 Color_Res[15] = {0};
u8 Is_Color_Finished = 0;

//u8 Product_Calibration_Sign = 0;
//a 0x11 o 0x12 s 0x21 p 0x22    take photo: 0x31
//put_detect 4
//color_detect 2
//circle_detect 3
//ask 1
//poweroff 0

void Camera_Set_Mode(u8 mode)
{
	Camera_Mode = mode;
	
//	USART_SendByte(USART2, 0x00);
//	delay_ms(10);
//	USART_ClearFlag(USART2, USART_FLAG_RXNE);
	switch (mode)
	{
		case 0:
			Is_Color_Finished = 0;
			USART_SendByte(USART2,0x12);
//			Color_Hash_Table[0] = Color_Hash_Table[1] = Color_Hash_Table[2] = 0;
//			Color_Res[0] = Color_Res[1] = Color_Res[2] = 0;
//			Camera_RxBuffer[0] = Camera_RxBuffer[1] = Camera_RxBuffer[2] = Camera_RxBuffer[3] = 0x00;
			break;
		case 1:
			Is_Color_Finished = 0;
			USART_SendByte(USART2,0x11);
//			Color_Hash_Table[0] = Color_Hash_Table[1] = Color_Hash_Table[2] = 0;
//			Color_Res[0] = Color_Res[1] = Color_Res[2] = 0;
//			Camera_RxBuffer[0] = Camera_RxBuffer[1] = Camera_RxBuffer[2] = Camera_RxBuffer[3] = 0x00;
			break;
		case 2:
			Is_Color_Finished = 0;
			Camera_RxBuffer[0] = Camera_RxBuffer[1] = Camera_RxBuffer[2] = Camera_RxBuffer[3] = 0x00;
		 	USART_SendByte(USART2,0x21);
			break;
		case 3:
			Is_Color_Finished = 0;
			Camera_RxBuffer[0] = Camera_RxBuffer[1] = Camera_RxBuffer[2] = Camera_RxBuffer[3] = 0x00;
			Circle_X = Circle_Y = 0;
			USART_SendByte(USART2,0x32);
		case 4:
			Is_Color_Finished = 0;
			Camera_RxBuffer[0] = Camera_RxBuffer[1] = Camera_RxBuffer[2] = Camera_RxBuffer[3] = 0x00;
			Put_Circle_X = Put_Circle_Y = 0;
			USART_SendByte(USART2,0x33);
//		case 5:
//		case 6:
//			Product_Calibration_Sign = 0;
//			break;
		default:
			break;
	}
	//USART_SendByte(USART2, mode);
	delay_ms(10);
}
