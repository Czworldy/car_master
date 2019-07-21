#ifndef __USART_H
#define __USART_H

#include "sys.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define Key_RxBufferSize 1
#define Handle_RxBufferSize 12
#define Camera_RxBufferSize 4
#define QR_Code_RxBufferSize 11
#define QR_Code_TxBufferSize 9
#define GPS_RxBufferSize 20
#define GPS_TxBufferSize 9
#define WIFI_RxBufferSize 7
#define PanTilt_TxBufferSize 18
#define PanTilt_RxBufferSize 8

#define Print_USART USART1

#define BSP_USING_USART1
#define BSP_USING_USART2
#define BSP_USING_USART3
#define BSP_USING_UART4
//#define BSP_USING_UART5
#define BSP_USING_USART6

#ifdef BSP_USING_USART1
//	#define BSP_USING_USART1_DMA
#endif

#ifdef BSP_USING_USART2
//	#define BSP_USING_USART2_DMA
#endif

#ifdef BSP_USING_USART3
	#define BSP_USING_USART3_DMA
#endif

#ifdef BSP_USING_UART4
	#define BSP_USING_UART4_DMA
#endif

#ifdef BSP_USING_USART6
	#define BSP_USING_USART6_DMA
#endif

#if ((defined BSP_USING_USART1) && (!defined BSP_USING_USART1_DMA))
	#define BSP_USING_USART_KEY
#endif

#ifdef BSP_USING_USART1
	#define USART1_BAUDRATE                    115200

	#define USART1_RX_GPIO_PORT                GPIOA
	#define USART1_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
	#define USART1_RX_PIN                      GPIO_Pin_10
	#define USART1_RX_SOURCE                   GPIO_PinSource10

	#define USART1_TX_GPIO_PORT                GPIOA
	#define USART1_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
	#define USART1_TX_PIN                      GPIO_Pin_9
	#define USART1_TX_SOURCE                   GPIO_PinSource9
	
	#ifdef BSP_USING_USART1_DMA
		#define USART1_DR_BASE                 (USART1_BASE+0x04)
		#define USART1_DMA_CLK                 RCC_AHB1Periph_DMA2	
		#define USART1_DMA_RX_CHANNEL          DMA_Channel_4
		#define USART1_DMA_RX_STREAM           DMA2_Stream5
		#define USART1_DMA_RX_IRQHandler       DMA2_Stream5_IRQHandler
		#define USART1_DMA_RX_IRQn             DMA2_Stream5_IRQn
		#define USART1_DMA_RX_IT_TC            DMA_IT_TCIF5
	#endif
#endif

#ifdef BSP_USING_USART2
	#define USART2_BAUDRATE                    115200

	#define USART2_RX_GPIO_PORT                GPIOA
	#define USART2_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
	#define USART2_RX_PIN                      GPIO_Pin_3
	#define USART2_RX_SOURCE                   GPIO_PinSource3

	#define USART2_TX_GPIO_PORT                GPIOA
	#define USART2_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
	#define USART2_TX_PIN                      GPIO_Pin_2
	#define USART2_TX_SOURCE                   GPIO_PinSource2
	
	#ifdef BSP_USING_USART2_DMA
		#define USART2_DR_BASE                 (USART2_BASE+0x04)
		#define USART2_DMA_CLK                 RCC_AHB1Periph_DMA1	
		#define USART2_DMA_RX_CHANNEL          DMA_Channel_4
		#define USART2_DMA_RX_STREAM           DMA1_Stream5
		#define USART2_DMA_RX_IRQHandler       DMA1_Stream5_IRQHandler
		#define USART2_DMA_RX_IRQn             DMA1_Stream5_IRQn
		#define USART2_DMA_RX_IT_TC            DMA_IT_TCIF5
	#endif
#endif

#ifdef BSP_USING_USART3
	#define USART3_BAUDRATE                    115200

	#define USART3_RX_GPIO_PORT                GPIOB
	#define USART3_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOB
	#define USART3_RX_PIN                      GPIO_Pin_11
	#define USART3_RX_SOURCE                   GPIO_PinSource11

	#define USART3_TX_GPIO_PORT                GPIOB
	#define USART3_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOB
	#define USART3_TX_PIN                      GPIO_Pin_10
	#define USART3_TX_SOURCE                   GPIO_PinSource10
	
	#ifdef BSP_USING_USART3_DMA
		#define USART3_DR_BASE                 (USART3_BASE+0x04)
		#define USART3_DMA_CLK                 RCC_AHB1Periph_DMA1
		
		#define USART3_DMA_RX_CHANNEL          DMA_Channel_4
		#define USART3_DMA_RX_STREAM           DMA1_Stream1
		#define USART3_DMA_RX_IRQHandler       DMA1_Stream1_IRQHandler
		#define USART3_DMA_RX_IRQn             DMA1_Stream1_IRQn
		#define USART3_DMA_RX_IT_TC            DMA_IT_TCIF1
		
		#define USART3_DMA_TX_CHANNEL          DMA_Channel_4
		#define USART3_DMA_TX_STREAM           DMA1_Stream3
		#define USART3_DMA_TX_IRQHandler       DMA1_Stream3_IRQHandler
		#define USART3_DMA_TX_IRQn             DMA1_Stream3_IRQn
		#define USART3_DMA_TX_IT_TC            DMA_IT_TCIF3
	#endif
#endif

#ifdef BSP_USING_UART4
	#define UART4_BAUDRATE                     115200

	#define UART4_RX_GPIO_PORT                 GPIOA
	#define UART4_RX_GPIO_CLK                  RCC_AHB1Periph_GPIOA
	#define UART4_RX_PIN                       GPIO_Pin_1
	#define UART4_RX_SOURCE                    GPIO_PinSource1

	#define UART4_TX_GPIO_PORT                 GPIOA
	#define UART4_TX_GPIO_CLK                  RCC_AHB1Periph_GPIOA
	#define UART4_TX_PIN                       GPIO_Pin_0
	#define UART4_TX_SOURCE                    GPIO_PinSource0
	
	#ifdef BSP_USING_UART4_DMA
		#define UART4_DR_BASE                  (UART4_BASE+0x04)
		#define UART4_DMA_CLK                  RCC_AHB1Periph_DMA1
		
		#define UART4_DMA_RX_CHANNEL           DMA_Channel_4
		#define UART4_DMA_RX_STREAM            DMA1_Stream2
		#define UART4_DMA_RX_IRQHandler        DMA1_Stream2_IRQHandler
		#define UART4_DMA_RX_IRQn              DMA1_Stream2_IRQn
		#define UART4_DMA_RX_IT_TC             DMA_IT_TCIF2
		
		#define UART4_DMA_TX_CHANNEL           DMA_Channel_4
		#define UART4_DMA_TX_STREAM            DMA1_Stream4
		#define UART4_DMA_TX_IRQHandler        DMA1_Stream4_IRQHandler
		#define UART4_DMA_TX_IRQn              DMA1_Stream4_IRQn
		#define UART4_DMA_TX_IT_TC             DMA_IT_TCIF4
	#endif
#endif

#ifdef BSP_USING_UART5
	#define UART5_BAUDRATE                     115200

	#define UART5_RX_GPIO_PORT                 GPIOD
	#define UART5_RX_GPIO_CLK                  RCC_AHB1Periph_GPIOD
	#define UART5_RX_PIN                       GPIO_Pin_2
	#define UART5_RX_SOURCE                    GPIO_PinSource2

	#define UART5_TX_GPIO_PORT                 GPIOC
	#define UART5_TX_GPIO_CLK                  RCC_AHB1Periph_GPIOC
	#define UART5_TX_PIN                       GPIO_Pin_12
	#define UART5_TX_SOURCE                    GPIO_PinSource12
#endif

#ifdef BSP_USING_USART6
	#define USART6_BAUDRATE                    115200

	#define USART6_RX_GPIO_PORT                GPIOG
	#define USART6_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOG
	#define USART6_RX_PIN                      GPIO_Pin_9
	#define USART6_RX_SOURCE                   GPIO_PinSource9

	#define USART6_TX_GPIO_PORT                GPIOG
	#define USART6_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOG
	#define USART6_TX_PIN                      GPIO_Pin_14
	#define USART6_TX_SOURCE                   GPIO_PinSource14
	
	#ifdef BSP_USING_USART6_DMA
		#define USART6_DR_BASE                 (USART6_BASE+0x04)
		#define USART6_DMA_CLK                 RCC_AHB1Periph_DMA2
		
		#define USART6_DMA_RX_CHANNEL          DMA_Channel_5
		#define USART6_DMA_RX_STREAM           DMA2_Stream2
		#define USART6_DMA_RX_IRQHandler       DMA2_Stream2_IRQHandler
		#define USART6_DMA_RX_IRQn             DMA2_Stream2_IRQn
		#define USART6_DMA_RX_IT_TC            DMA_IT_TCIF2
		
		#define USART6_DMA_TX_CHANNEL          DMA_Channel_5
		#define USART6_DMA_TX_STREAM           DMA2_Stream6
		#define USART6_DMA_TX_IRQHandler       DMA2_Stream6_IRQHandler
		#define USART6_DMA_TX_IRQn             DMA2_Stream6_IRQn
		#define USART6_DMA_TX_IT_TC            DMA_IT_TCIF6
	#endif
#endif

extern u8 Is_USART_Key_Receive;

extern volatile u8 Key_RxBuffer[];
extern volatile u8 Handle_RxBuffer[];
extern volatile u8 Camera_RxBuffer[];
extern volatile u8 QR_Code_RxBuffer[];
extern volatile u8 WIFI_RxBuffer[];
extern u8 QR_Code_TxBuffer[];
extern volatile u8 GPS_RxBuffer[];
extern u8 GPS_TxBuffer[];
extern u8 PanTilt_TxBuffer[];
extern volatile u8 PanTilt_RxBuffer[];

extern u8 WIFI_RxBuffer_Idx;

void USART_Config(void);
void Handle_USART_DMA_EN(void);
void GPS_USART_DMA_EN(void);
void Color_USART_DMA_EN(void);

void USART_SendByte(USART_TypeDef *USARTx, uint8_t dat);
uint8_t USART_GetByte(USART_TypeDef *USARTx);
void USART_puts(USART_TypeDef * USARTx, char * str);
void USART_printf(USART_TypeDef * USARTx, char *fmt, ...);

#endif
