#include "gps.h"
#include "mymath.h"
#include "usart.h"
#include "delay.h"

struct GPS_State GPS_List[GPS_STATE_SIZE] = {0};
struct GPS_State GPS_Offset = {{0.0, 0.0}, 0.0, 0.0};

void GPS_Clear(void)
{
#ifdef BSP_USING_UART4_DMA
	GPS_TxBuffer[0] = 0xFF;
	GPS_TxBuffer[1] = 0xAA;
	GPS_TxBuffer[2] = 0x00;
	GPS_TxBuffer[3] = 0xAA;
	GPS_TxBuffer[8] = 0x00;
	DMA_SetCurrDataCounter(UART4_DMA_TX_STREAM, GPS_TxBufferSize);
	DMA_Cmd(UART4_DMA_TX_STREAM, ENABLE);
#endif
}

void GPS_Init(float x, float y)
{
#ifdef BSP_USING_UART4_DMA
	GPS_TxBuffer[0] = 0xFF;
	GPS_TxBuffer[1] = 0xAA;
	GPS_TxBuffer[2] = 0x01;
	GPS_TxBuffer[3] = 0xAA;
	(*((float*)GPS_TxBuffer + 1)) = x;
	GPS_TxBuffer[8] = 0x00;
	DMA_SetCurrDataCounter(UART4_DMA_TX_STREAM, GPS_TxBufferSize);
	DMA_Cmd(UART4_DMA_TX_STREAM, ENABLE);
	
	while (DMA_GetCurrDataCounter(UART4_DMA_TX_STREAM) != 0);
	delay_ms(90);
	
	GPS_TxBuffer[0] = 0xFF;
	GPS_TxBuffer[1] = 0xAA;
	GPS_TxBuffer[2] = 0x02;
	GPS_TxBuffer[3] = 0xAA;
	(*((float*)GPS_TxBuffer + 1)) = y;
	GPS_TxBuffer[8] = 0x00;
	DMA_SetCurrDataCounter(UART4_DMA_TX_STREAM, GPS_TxBufferSize);
	DMA_Cmd(UART4_DMA_TX_STREAM, ENABLE);
#endif
}

void GPS_Gyro_Set_Zero(void)
{
#ifdef BSP_USING_UART4_DMA
	GPS_TxBuffer[0] = 0xFF;
	GPS_TxBuffer[1] = 0xAA;
	GPS_TxBuffer[2] = 0x03;
	GPS_TxBuffer[3] = 0xAA;
	GPS_TxBuffer[8] = 0x00;
	DMA_SetCurrDataCounter(UART4_DMA_TX_STREAM, GPS_TxBufferSize);
	DMA_Cmd(UART4_DMA_TX_STREAM, ENABLE);
#endif
}
