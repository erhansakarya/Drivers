/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HTU21D_H
#define __HTU21D_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

#define HTU21D_ADDR			(0x40 << 1)	/* NOTE: 0x40 is 7-bit address */

#define HTU21D_TEMP_HOLD	0xE3	/* NOTE: Trigger temperature measurement in hold master */
#define HTU21D_HUM_HOLD		0xE5	/* NOTE: Trigger humidity measurement in hold master */
#define HTU21D_TEMP_NOHOLD	0xF3	/* NOTE: Trigger temperature measurement in no-hold master */
#define HTU21D_HUM_NOHOLD	0xF5	/* NOTE: Trigger humidity measurement in no-hold master */
#define HTU21D_WR_USRREG	0xE6	/* NOTE: Write user register */
#define HTU21D_RD_USRREG	0xE7	/* NOTE: Read user register */
#define HTU21D_SOFT_RESET	0xFE	/* NOTE: Soft reset */

typedef enum{
	RH12TEMP14 	= 0x00,
	RH8TEMP12	= 0x01,
	RH10TEMP13 	= 0x80,
	RH11TEMP11 	= 0x81
}HTU21D_measRes_e;

typedef struct{
	float temperature;
	float humidity;
}HTU21D_s;

extern HTU21D_s htu21d;

uint8_t HTU21D_init(void);
void HTU21D_handler(void *htu21d);

#ifdef __cplusplus
}
#endif

#endif /* __HTU21D_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
