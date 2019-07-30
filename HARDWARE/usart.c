#include "usart.h"
#include "gps.h"
#include "mymath.h"
#include "delay.h"
#include "camera.h"
#include "led.h"
#include "qr_code.h"
#include "handle.h"
#include "key.h"

u8 Is_USART_Key_Receive = 0;

__align(32) volatile u8 Key_RxBuffer[Key_RxBufferSize] = {0};
__align(32) volatile u8 Handle_RxBuffer[Handle_RxBufferSize] = {0};
__align(32) volatile u8 Camera_RxBuffer[Camera_RxBufferSize] = {0};
__align(32) volatile u8 QR_Code_RxBuffer[QR_Code_RxBufferSize] = {0};
__align(32) volatile u8 WIFI_RxBuffer[WIFI_RxBufferSize] = {0};
u8 QR_Code_TxBuffer[QR_Code_TxBufferSize] = {0x7E, 0x00, 0x08, 0x01, 0x00, 0x02, 0x01, 0xAB, 0xCD};
__align(32) volatile u8 GPS_RxBuffer[GPS_RxBufferSize] = {0};
__align(32) u8 GPS_TxBuffer[GPS_TxBufferSize] = {0};
//__align(32) u8 PanTilt_TxBuffer[PanTilt_TxBufferSize] = {0};
//__align(32) volatile u8 PanTilt_RxBuffer[PanTilt_RxBufferSize] = {0};

u8 WIFI_RxBuffer_Idx = 0;

void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

#ifdef BSP_USING_USART1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(USART1_RX_GPIO_CLK | USART1_TX_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN;
	GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(USART1_RX_GPIO_PORT, USART1_RX_SOURCE, GPIO_AF_USART1);
	GPIO_PinAFConfig(USART1_TX_GPIO_PORT, USART1_TX_SOURCE, GPIO_AF_USART1);
	
	USART_InitStructure.USART_BaudRate = USART1_BAUDRATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
#ifndef BSP_USING_USART1_DMA
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ClearFlag(USART1, USART_FLAG_RXNE);
	USART_ClearFlag(USART1, USART_FLAG_TC);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	
	USART_Cmd(USART1, ENABLE);
#else
	RCC_AHB1PeriphClockCmd(USART1_DMA_CLK, ENABLE);
	
	DMA_InitStructure.DMA_Channel = USART1_DMA_RX_CHANNEL;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (USART1_BASE+0x04);
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)Handle_RxBuffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = Handle_RxBufferSize;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(USART1_DMA_RX_STREAM, &DMA_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_DMA_RX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ClearFlag(USART1, USART_FLAG_RXNE);
	USART_ClearFlag(USART1, USART_FLAG_TC);
	
	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
	DMA_ClearITPendingBit(USART1_DMA_RX_STREAM, USART1_DMA_RX_IT_TC);
	DMA_ITConfig(USART1_DMA_RX_STREAM, DMA_IT_TC, ENABLE);
	
	DMA_Cmd(USART1_DMA_RX_STREAM, DISABLE);
	while (DMA_GetCmdStatus(USART1_DMA_RX_STREAM) != DISABLE) {}
	
	USART_Cmd(USART1, ENABLE);
#endif
#endif

#ifdef BSP_USING_USART2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(USART2_RX_GPIO_CLK | USART2_TX_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = USART2_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(USART2_RX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = USART2_TX_PIN;
	GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(USART2_RX_GPIO_PORT, USART2_RX_SOURCE, GPIO_AF_USART2);
	GPIO_PinAFConfig(USART2_TX_GPIO_PORT, USART2_TX_SOURCE, GPIO_AF_USART2);
	
	USART_InitStructure.USART_BaudRate = USART2_BAUDRATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);
	
#ifndef BSP_USING_USART2_DMA
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ClearFlag(USART2, USART_FLAG_RXNE);
	USART_ClearFlag(USART2, USART_FLAG_TC);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);
#else
	USART_ClearFlag(USART2, USART_FLAG_TC);
	USART_Cmd(USART2, ENABLE);
	USART_SendByte(USART2, 0xA5);
	USART_SendByte(USART2, 0x81);
	USART_SendByte(USART2, 0x26);
	USART_Cmd(USART2, DISABLE);
	delay_ms(10);
	USART_ClearFlag(USART2, USART_FLAG_TC);
	USART_ClearFlag(USART2, USART_FLAG_RXNE);
	
	RCC_AHB1PeriphClockCmd(USART2_DMA_CLK, ENABLE);
	
	DMA_InitStructure.DMA_Channel = USART2_DMA_RX_CHANNEL;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (USART2_BASE+0x04);
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)Color_RxBuffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = Color_RxBufferSize;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(USART2_DMA_RX_STREAM, &DMA_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_DMA_RX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ClearFlag(USART2, USART_FLAG_RXNE);
	USART_ClearFlag(USART2, USART_FLAG_TC);
	
	USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);
	DMA_ClearITPendingBit(USART2_DMA_RX_STREAM, USART2_DMA_RX_IT_TC);
	DMA_ITConfig(USART2_DMA_RX_STREAM, DMA_IT_TC, ENABLE);
	
	DMA_Cmd(USART2_DMA_RX_STREAM, DISABLE);
	while (DMA_GetCmdStatus(USART2_DMA_RX_STREAM) != DISABLE) {}
	
	USART_Cmd(USART2, ENABLE);
#endif
#endif

#ifdef BSP_USING_USART3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_AHB1PeriphClockCmd(USART3_RX_GPIO_CLK | USART3_TX_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = USART3_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(USART3_RX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = USART3_TX_PIN;
	GPIO_Init(USART3_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(USART3_RX_GPIO_PORT, USART3_RX_SOURCE, GPIO_AF_USART3);
	GPIO_PinAFConfig(USART3_TX_GPIO_PORT, USART3_TX_SOURCE, GPIO_AF_USART3);
	
	USART_InitStructure.USART_BaudRate = USART3_BAUDRATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);

#ifndef BSP_USING_USART3_DMA
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ClearFlag(USART3, USART_FLAG_RXNE);
	USART_ClearFlag(USART3, USART_FLAG_TC);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	
	USART_Cmd(USART3, ENABLE);
#else
	RCC_AHB1PeriphClockCmd(USART3_DMA_CLK, ENABLE);
	
	DMA_InitStructure.DMA_Channel = USART3_DMA_RX_CHANNEL;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (USART3_BASE+0x04);
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)QR_Code_RxBuffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = QR_Code_RxBufferSize;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(USART3_DMA_RX_STREAM, &DMA_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_DMA_RX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	DMA_InitStructure.DMA_Channel = USART3_DMA_TX_CHANNEL;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (USART3_BASE+0x04);
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)QR_Code_TxBuffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = QR_Code_TxBufferSize;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(USART3_DMA_TX_STREAM, &DMA_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_DMA_TX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ClearFlag(USART3, USART_FLAG_RXNE);
	USART_ClearFlag(USART3, USART_FLAG_TC);
	
	USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);
	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
	DMA_ClearITPendingBit(USART3_DMA_RX_STREAM, USART3_DMA_RX_IT_TC);
	DMA_ClearITPendingBit(USART3_DMA_TX_STREAM, USART3_DMA_TX_IT_TC);
	DMA_ITConfig(USART3_DMA_RX_STREAM, DMA_IT_TC, ENABLE);
	DMA_ITConfig(USART3_DMA_TX_STREAM, DMA_IT_TC, ENABLE);
	
	DMA_Cmd(USART3_DMA_RX_STREAM, ENABLE);
	DMA_Cmd(USART3_DMA_TX_STREAM, DISABLE);
	
	USART_Cmd(USART3, ENABLE);
#endif
#endif

#ifdef BSP_USING_UART4
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	RCC_AHB1PeriphClockCmd(UART4_RX_GPIO_CLK | UART4_TX_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = UART4_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(UART4_RX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = UART4_TX_PIN;
	GPIO_Init(UART4_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(UART4_RX_GPIO_PORT, UART4_RX_SOURCE, GPIO_AF_UART4);
	GPIO_PinAFConfig(UART4_TX_GPIO_PORT, UART4_TX_SOURCE, GPIO_AF_UART4);
	
	USART_InitStructure.USART_BaudRate = UART4_BAUDRATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4, &USART_InitStructure);
	
#ifndef BSP_USING_UART4_DMA
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ClearFlag(UART4, USART_FLAG_RXNE);
	USART_ClearFlag(UART4, USART_FLAG_TC);
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);	
	USART_Cmd(UART4, ENABLE);
#else
	RCC_AHB1PeriphClockCmd(UART4_DMA_CLK, ENABLE);
	
	DMA_InitStructure.DMA_Channel = UART4_DMA_RX_CHANNEL;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (UART4_BASE+0x04);
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)GPS_RxBuffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = GPS_RxBufferSize;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(UART4_DMA_RX_STREAM, &DMA_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = UART4_DMA_RX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	DMA_InitStructure.DMA_Channel = UART4_DMA_TX_CHANNEL;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (UART4_BASE+0x04);
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)GPS_TxBuffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = GPS_TxBufferSize;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(UART4_DMA_TX_STREAM, &DMA_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = UART4_DMA_TX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ClearFlag(UART4, USART_FLAG_RXNE);
	USART_ClearFlag(UART4, USART_FLAG_TC);
	
	USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE);
	USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE);
	DMA_ClearITPendingBit(UART4_DMA_RX_STREAM, UART4_DMA_RX_IT_TC);
	DMA_ClearITPendingBit(UART4_DMA_TX_STREAM, UART4_DMA_TX_IT_TC);
	DMA_ITConfig(UART4_DMA_RX_STREAM, DMA_IT_TC, ENABLE);
	DMA_ITConfig(UART4_DMA_TX_STREAM, DMA_IT_TC, ENABLE);
	
	DMA_Cmd(UART4_DMA_RX_STREAM, DISABLE);
	DMA_Cmd(UART4_DMA_TX_STREAM, DISABLE);
	
	USART_Cmd(UART4, ENABLE);
#endif
#endif

#ifdef BSP_USING_UART5
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
	RCC_AHB1PeriphClockCmd(UART5_RX_GPIO_CLK | UART5_TX_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = UART5_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(UART5_RX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = UART5_TX_PIN;
	GPIO_Init(UART5_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(UART5_RX_GPIO_PORT, UART5_RX_SOURCE, GPIO_AF_UART5);
	GPIO_PinAFConfig(UART5_TX_GPIO_PORT, UART5_TX_SOURCE, GPIO_AF_UART5);
	
	USART_InitStructure.USART_BaudRate = UART5_BAUDRATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART5, &USART_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ClearFlag(UART5, USART_FLAG_RXNE);
	USART_ClearFlag(UART5, USART_FLAG_TC);
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
	USART_Cmd(UART5, ENABLE);
#endif

#ifdef BSP_USING_USART6
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	RCC_AHB1PeriphClockCmd(USART6_RX_GPIO_CLK | USART6_TX_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = USART6_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(USART6_RX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = USART6_TX_PIN;
	GPIO_Init(USART6_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(USART6_RX_GPIO_PORT, USART6_RX_SOURCE, GPIO_AF_USART6);
	GPIO_PinAFConfig(USART6_TX_GPIO_PORT, USART6_TX_SOURCE, GPIO_AF_USART6);
	
	USART_InitStructure.USART_BaudRate = USART6_BAUDRATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART6, &USART_InitStructure);
	
#ifndef BSP_USING_USART6_DMA
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ClearFlag(USART6, USART_FLAG_RXNE);
	USART_ClearFlag(USART6, USART_FLAG_TC);
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);	
	USART_Cmd(USART6, ENABLE);
#else
	RCC_AHB1PeriphClockCmd(USART6_DMA_CLK, ENABLE);
	
	DMA_InitStructure.DMA_Channel = USART6_DMA_RX_CHANNEL;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (USART6_BASE+0x04);
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)PanTilt_RxBuffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = PanTilt_RxBufferSize;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(USART6_DMA_RX_STREAM, &DMA_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART6_DMA_RX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	DMA_InitStructure.DMA_Channel = USART6_DMA_TX_CHANNEL;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (USART6_BASE+0x04);
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)PanTilt_TxBuffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = PanTilt_TxBufferSize;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(USART6_DMA_TX_STREAM, &DMA_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART6_DMA_TX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ClearFlag(USART6, USART_FLAG_RXNE);
	USART_ClearFlag(USART6, USART_FLAG_TC);
	
	USART_DMACmd(USART6, USART_DMAReq_Rx, ENABLE);
	USART_DMACmd(USART6, USART_DMAReq_Tx, ENABLE);
	DMA_ClearITPendingBit(USART6_DMA_RX_STREAM, USART6_DMA_RX_IT_TC);
	DMA_ClearITPendingBit(USART6_DMA_TX_STREAM, USART6_DMA_TX_IT_TC);
	DMA_ITConfig(USART6_DMA_RX_STREAM, DMA_IT_TC, ENABLE);
	DMA_ITConfig(USART6_DMA_TX_STREAM, DMA_IT_TC, ENABLE);
	
//	DMA_Cmd(USART6_DMA_RX_STREAM, DISABLE);
//	DMA_Cmd(USART6_DMA_TX_STREAM, DISABLE);
	
	DMA_Cmd(USART6_DMA_RX_STREAM, ENABLE);
	DMA_Cmd(USART6_DMA_TX_STREAM, ENABLE);
	
	USART_Cmd(USART6, ENABLE);
#endif
#endif
}

void Handle_USART_DMA_EN(void)
{
#ifdef BSP_USING_USART1_DMA
	uint8_t handle_start, j;
	uint8_t handle_temp[Handle_RxBufferSize] = {0};
	
	handle_start = 0;
	j = 0;
	while (!handle_start)
	{
		if (j == 0)
		{
			handle_temp[j] = USART_GetByte(USART1);
			if (handle_temp[j] == 0xAA)
			{
				j = 1;
				handle_temp[j] = USART_GetByte(USART1);
				if (handle_temp[j] == 0xBB)
					j = 2;
				else
					j = 0;
			}
			else
				j = 0;
		}
		else
		{
			handle_temp[j++] = USART_GetByte(USART1);
			switch (j)
			{
				case 11:
					if (handle_temp[10] != 0xCC)
						j = 0;
					break;
				case 12:
					if (handle_temp[11] != 0xDD)
						j = 0;
					else
					{
						handle_start = 1;
						while (1)
						{
							if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
							{
								break;
							}
						}
						DMA_Cmd(USART1_DMA_RX_STREAM, ENABLE);
					}
					break;
				default:
					break;
			}
		}
	}
#endif	
}

void GPS_USART_DMA_EN(void)
{
#ifdef BSP_USING_UART4_DMA
	uint8_t gps_start, j;
	uint8_t gps_temp[GPS_RxBufferSize] = {0};
	
	gps_start = 0;
	j = 0;
	while (!gps_start)
	{
		if (j == 0)
		{
			gps_temp[j] = USART_GetByte(UART4);
			if (gps_temp[j] == 0xAB)
			{
				j = 1;
				gps_temp[j] = USART_GetByte(UART4);
				if (gps_temp[j] == 0xBC)
				{
					j = 2;
					gps_temp[j] = USART_GetByte(UART4);
					if (gps_temp[j] == 0xCD)
					{
						j = 3;
						gps_temp[j] = USART_GetByte(UART4);
						if (gps_temp[j] == 0xDE)
						{
							j = 4;
						}
						else
							j = 0;
					}
					else
						j = 0;
				}
				else
					j = 0;
			}
			else
				j = 0;
		}
		else
		{
			gps_temp[j++] = USART_GetByte(UART4);
			switch (j)
			{
				case GPS_RxBufferSize - 3:
					if (gps_temp[j-1] != 0xED)
						j = 0;
					break;
				case GPS_RxBufferSize - 2:
					if (gps_temp[j-1] != 0xDC)
						j = 0;
					break;
				case GPS_RxBufferSize - 1:
					if (gps_temp[j-1] != 0xCB)
						j = 0;
					break;
				case GPS_RxBufferSize:
					if (gps_temp[j-1] != 0xBA)
						j = 0;
					else
					{
						gps_start = 1;
						while (1)
						{
							if (USART_GetFlagStatus(UART4, USART_FLAG_RXNE) == SET)
							{
								break;
							}
						}
						DMA_Cmd(UART4_DMA_RX_STREAM, ENABLE);
					}
					break;
				default:
					break;
			}
		}
	}
#endif
}

void Color_USART_DMA_EN(void)
{
#ifdef BSP_USING_USART2_DMA
	uint8_t color_start = 0, j = 0;
	uint8_t color_temp[Color_RxBufferSize] = {0};
	
	while (!color_start)
	{
		if (j <= 3)
		{
			color_temp[j] = USART_GetByte(USART2);
			if (color_temp[j] == 0x5A)
			{
				j = 1;
				color_temp[j] = USART_GetByte(USART2);
				if (color_temp[j] == 0x5A)
				{
					j = 2;
					color_temp[j] = USART_GetByte(USART2);
					if (color_temp[j] == 0x45)
					{
						j = 3;
						color_temp[j] = USART_GetByte(USART2);
						if (color_temp[j] == 0x03)
						{
							j = 4;
						}
						else
							j = 0;
					}
					else
						j = 0;
				}
				else
					j = 0;
			}
			else
				j = 0;
		}
		else
		{
			color_temp[j++] = USART_GetByte(USART2);
			switch (j)
			{
				case Color_RxBufferSize:
					if (((color_temp[0] + color_temp[1] + color_temp[2] + color_temp[3] + 
					      color_temp[4] + color_temp[5] + color_temp[6]) & 0xff) == color_temp[7])
					{
						color_start = 1;
						while (1)
						{
							if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET)
							{
								break;
							}
						}
						DMA_Cmd(USART2_DMA_RX_STREAM, ENABLE);
					}
					else
					{
						j = 0;
					}
					break;
				default:
					break;
			}
		}
	}
#endif
}

void USART_SendByte(USART_TypeDef *USARTx, uint8_t dat)
{
	USART_SendData(USARTx, dat);
	while (!USART_GetFlagStatus(USARTx, USART_FLAG_TXE));
}

uint8_t USART_GetByte(USART_TypeDef *USARTx)
{
	uint8_t dat;
	while (!USART_GetFlagStatus(USARTx, USART_FLAG_RXNE));
	dat = (USART_ReceiveData(USARTx) & 0xff);
	return dat;
}

void USART_puts(USART_TypeDef * USARTx, char * str)
{
	while (*str)
	{
		USART_SendByte(USARTx, *str++);
	}
}

void USART_printf(USART_TypeDef * USARTx, char *fmt, ...)
{
	va_list ap;
	char str[128];

	va_start(ap,fmt);
	vsprintf(str,fmt,ap);
	va_end(ap);
	USART_puts(USARTx, str);
}

//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while ((Print_USART->SR&0X40)==0);//循环发送,直到发送完毕   
	Print_USART->DR = (u8) ch;      
	return ch;
}

#ifdef BSP_USING_USART1
#ifdef BSP_USING_USART1_DMA
void USART1_DMA_RX_IRQHandler(void)
{
	if (DMA_GetITStatus(USART1_DMA_RX_STREAM, USART1_DMA_RX_IT_TC) == SET)
	{
		if (((Handle_RxBuffer[3] << 8) | Handle_RxBuffer[2]))
			Handle_Key_Value = ((Handle_RxBuffer[3] << 8) | Handle_RxBuffer[2]);
		DMA_ClearITPendingBit(USART1_DMA_RX_STREAM, USART1_DMA_RX_IT_TC);
	}
}
#else
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		Key_RxBuffer[0] = USART1->DR;
		Is_USART_Key_Receive = 1;
	}
}
#endif
#endif

#ifdef BSP_USING_USART2
#ifdef BSP_USING_USART2_DMA
void USART2_DMA_RX_IRQHandler(void)
{
	if (DMA_GetITStatus(USART2_DMA_RX_STREAM, USART2_DMA_RX_IT_TC) == SET)
	{
		Cur_Color.r = Color_RxBuffer[4];
		Cur_Color.g = Color_RxBuffer[5];
		Cur_Color.b = Color_RxBuffer[6];
		Cur_Color.rgb565 = ((((u16)Cur_Color.r >> 3) << 11) | (((u16)Cur_Color.g >> 2) << 5) | ((u16)Cur_Color.b >> 3));
		
		DMA_ClearITPendingBit(USART2_DMA_RX_STREAM, USART2_DMA_RX_IT_TC);
	}
}
#else
void USART2_IRQHandler(void)
{
	u8 temp[3] = {0};
	u8 i;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		Camera_RxBuffer[3] = Camera_RxBuffer[2];
		Camera_RxBuffer[2] = Camera_RxBuffer[1];
		Camera_RxBuffer[1] = Camera_RxBuffer[0];
		Camera_RxBuffer[0] = USART2->DR;
		
		switch (Camera_Mode)
		{
			case 1:
				temp[0] = (Camera_RxBuffer[0] >> 0) & 0x03;
				temp[1] = (Camera_RxBuffer[0] >> 2) & 0x03;
				temp[2] = (Camera_RxBuffer[0] >> 4) & 0x03;
				if (Camera_RxBuffer[0] == Camera_RxBuffer[1] && 
				    Camera_RxBuffer[1] == Camera_RxBuffer[2] &&
				    Camera_RxBuffer[2] == Camera_RxBuffer[3] &&
				    temp[0] >= 1 && temp[0] <= 3 && 
				    temp[1] >= 1 && temp[1] <= 3 && 
				    temp[2] >= 1 && temp[2] <= 3)
				{
					for (i = 0; i < 3; ++i)
					{
						Color_Res[i] = temp[i];
						Color_Hash_Table[Color_Res[i]-1] = i + 1;
					}
					Is_Color_Finished = 1;
					USART_SendByte(USART2, 0x00);
				}
				break;
			case 2:
				temp[0] = (Camera_RxBuffer[0] >> 0) & 0x03;
				temp[1] = (Camera_RxBuffer[0] >> 2) & 0x03;
				temp[2] = (Camera_RxBuffer[0] >> 4) & 0x03;
				if (Camera_RxBuffer[0] == Camera_RxBuffer[1] && 
				    Camera_RxBuffer[1] == Camera_RxBuffer[2] &&
				    Camera_RxBuffer[2] == Camera_RxBuffer[3] &&
				    temp[0] >= 1 && temp[0] <= 3 && 
				    temp[1] >= 1 && temp[1] <= 3 && 
				    temp[2] >= 1 && temp[2] <= 3)
				{
					for (i = 0; i < 3; ++i)
					{
						Color_Res[i] = temp[i];
						Color_Hash_Table[Color_Res[i]-1] = i + 1;
					}
				}
				break;
			case 3:
			case 4:
			case 5:
			case 6:
				Product_Calibration_Sign = 1;
				break;
			default:
				break;
		}
	}
}
#endif
#endif

#ifdef BSP_USING_USART3
#ifdef BSP_USING_USART3_DMA
void USART3_DMA_RX_IRQHandler(void)
{
	if (DMA_GetITStatus(USART3_DMA_RX_STREAM, USART3_DMA_RX_IT_TC) == SET)
	{
		if (QR_Code_RxBuffer[10] == 0x0D)
		{
			QR_Code_Res[0] = QR_Code_RxBuffer[7];
			QR_Code_Res[1] = QR_Code_RxBuffer[8];
			QR_Code_Res[2] = QR_Code_RxBuffer[9];
			QR_Code_RX_Finish = 1;
		}		
		DMA_ClearITPendingBit(USART3_DMA_RX_STREAM, USART3_DMA_RX_IT_TC);
	}
}

void USART3_DMA_TX_IRQHandler(void)
{
	if (DMA_GetITStatus(USART3_DMA_TX_STREAM, USART3_DMA_TX_IT_TC) == SET)
	{		
		DMA_ClearITPendingBit(USART3_DMA_TX_STREAM, USART3_DMA_TX_IT_TC);
		DMA_Cmd(USART3_DMA_TX_STREAM, DISABLE);
	}
}
#else
void USART3_IRQHandler(void)
{
	u8 c;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		c = USART3->DR;
		USART_printf(USART3, "%c", c);
	}
}
#endif
#endif

#ifdef BSP_USING_UART4
#ifdef BSP_USING_UART4_DMA
void UART4_DMA_RX_IRQHandler(void)
{
	if (DMA_GetITStatus(UART4_DMA_RX_STREAM, UART4_DMA_RX_IT_TC) == SET)
	{
		GPS_List[0].position.x = (*((float*)GPS_RxBuffer + 1)) + GPS_Offset.position.x;
		GPS_List[0].position.y = (*((float*)GPS_RxBuffer + 2)) + GPS_Offset.position.y;
		GPS_List[0].angle = *((float*)GPS_RxBuffer + 3) + GPS_Offset.angle;
		GPS_List[0].radian = GPS_List[0].angle * DEG2RAD;
		DMA_ClearITPendingBit(UART4_DMA_RX_STREAM, UART4_DMA_RX_IT_TC);
	}
}

void UART4_DMA_TX_IRQHandler(void)
{
	if (DMA_GetITStatus(UART4_DMA_TX_STREAM, UART4_DMA_TX_IT_TC) == SET)
	{
		DMA_ClearITPendingBit(UART4_DMA_TX_STREAM, UART4_DMA_TX_IT_TC);
		DMA_Cmd(UART4_DMA_TX_STREAM, DISABLE);
	}
}
#else
void UART4_IRQHandler(void)
{
	if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
		WIFI_RxBuffer[WIFI_RxBuffer_Idx++] = UART4->DR;
		if (WIFI_RxBuffer_Idx == WIFI_RxBufferSize)
		{
			WIFI_Res_1[0] = WIFI_RxBuffer[0];
			WIFI_Res_1[1] = WIFI_RxBuffer[1];
			WIFI_Res_1[2] = WIFI_RxBuffer[2];
			WIFI_Res_2[0] = WIFI_RxBuffer[4];
			WIFI_Res_2[1] = WIFI_RxBuffer[5];
			WIFI_Res_2[2] = WIFI_RxBuffer[6];
			WIFI_RxBuffer_Idx = 0;
			WIFI_Finish = 1;
			USART_SendByte(UART4, 0xFF);
		}
	} 
}
#endif
#endif

#ifdef BSP_USING_UART5
void UART5_IRQHandler(void)
{
	u8 c;
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
	{ 	
		c = UART5->DR;
		USART_printf(UART5, "%c", c);
	} 
}
#endif

#ifdef BSP_USING_USART6
#ifdef BSP_USING_USART6_DMA
void USART6_DMA_RX_IRQHandler(void)
{
	if (DMA_GetITStatus(USART6_DMA_RX_STREAM, USART6_DMA_RX_IT_TC) == SET)
	{

		DMA_ClearITPendingBit(USART6_DMA_RX_STREAM, USART6_DMA_RX_IT_TC);
	}
}

void USART6_DMA_TX_IRQHandler(void)
{
	if (DMA_GetITStatus(USART6_DMA_TX_STREAM, USART6_DMA_TX_IT_TC) == SET)
	{
		DMA_ClearITPendingBit(USART6_DMA_TX_STREAM, USART6_DMA_TX_IT_TC);
		DMA_Cmd(USART6_DMA_TX_STREAM, DISABLE);
	}
}
#else
void USART6_IRQHandler(void)
{
	if (USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)
	{
		WIFI_RxBuffer[WIFI_RxBuffer_Idx] = USART6->DR;
		if (WIFI_RxBuffer[WIFI_RxBuffer_Idx] == '+')
		{
			WIFI_Start = 1;
		}
		else
		{
			if (WIFI_Start && !WIFI_Finish)
			{
				if (WIFI_Res_CNT < 3)
				{
					WIFI_Res_2[WIFI_Res_CNT] = WIFI_RxBuffer[WIFI_RxBuffer_Idx];
					++WIFI_Res_CNT;
				}
				else
				{
					WIFI_Res_1[WIFI_Res_CNT-3] = WIFI_RxBuffer[WIFI_RxBuffer_Idx];
					++WIFI_Res_CNT;
					if (WIFI_Res_CNT == 6)
						WIFI_Finish = 1;
				}
			}
		}
		
		if (WIFI_RxBuffer_Idx == WIFI_RxBufferSize)
		{
			WIFI_RxBuffer_Idx = 0;
		}
		else
		{
			++WIFI_RxBuffer_Idx;
		}
	} 
}
#endif
#endif
