#include <string.h>

#include "main.h"
#include "TSL2561.h"

/*
 * NOTES:
 * Conversation cycle sürei boyunca beklemek gerekiyor.
 * threshold above and below değerlerinin dışına çıkınca interrupt oluşturur.
 * ADDR SEL pininin durumu bizde nedir?
 ** GND 0101001
 ** FLOAT 0111001
 ** VDD 1001001
 * INT pini, input open drain(active low), INT pininde direnç var mı?
 * Figure 8'deki değerlere bakmam gerekebilir.
 * Conversation time 100ms. max 400ms.
 *
 * power up olduktan sonra default integration time olan 400ms sonra adc değerleri hazır.
 * */

static uint8_t TSL2561_calculateLux(uint16_t *adcData);

uint8_t TSL2561_init(void){

	uint8_t pData[2];
	uint8_t error = 0;

	memset(pData, 0, (sizeof(pData) / sizeof(pData[0])));

	/* NOTE: Power up the device */
	pData[0] = TSL2561_COMMAND_REG | TSL2561_CONTROL;
	pData[1] = TSL2561_POWER_UP;
	if(HAL_I2C_Master_Transmit(&hi2c1, TSL2561_ADDR_FLOAT, pData,
			(sizeof(pData) / sizeof(pData[0])), HAL_MAX_DELAY) != HAL_OK){

		Error_Handler();
	}

//	/* NOTE: Get power state */
//	memset(pData, 0, (sizeof(pData) / sizeof(pData[0])));
//	if(HAL_I2C_Master_Receive(&hi2c1, TSL2561_ADDR_FLOAT, pData,
//			1, HAL_MAX_DELAY) != HAL_OK ){
//
//		Error_Handler();
//	}
//
//	if(pData[0] != 0x03){
//
//		error = 1;
//
//	}

	/* NOTE: Get Device ID */
	memset(pData, 0, (sizeof(pData) / sizeof(pData[0])));
	pData[0] = TSL2561_COMMAND_REG | TSL2561_ID;
	if(HAL_I2C_Master_Transmit(&hi2c1, TSL2561_ADDR_FLOAT, pData,
			1, HAL_MAX_DELAY) != HAL_OK ){

		Error_Handler();
	}

	memset(pData, 0, (sizeof(pData) / sizeof(pData[0])));
	if(HAL_I2C_Master_Receive(&hi2c1, TSL2561_ADDR_FLOAT, pData,
			1, HAL_MAX_DELAY) != HAL_OK ){

		Error_Handler();
	}

	if((pData[0] & 0xF0) != TSL2561_DEV_ID){
		error = 1;
	}

	/* NOTE: Configure Timing Register */
	memset(pData, 0, (sizeof(pData) / sizeof(pData[0])));
	pData[0] = TSL2561_COMMAND_REG | TSL2561_TIMING;
	pData[1] = 0x00;	/* NOTE: integration time is 13.7ms */
	if(HAL_I2C_Master_Transmit(&hi2c1, TSL2561_ADDR_FLOAT, pData,
			(sizeof(pData) / sizeof(pData[0])), HAL_MAX_DELAY) != HAL_OK){

		Error_Handler();
	}


	/* NOTE: Configure Interrupt Threshold registers */

	/* NOTE: Set interrupt control register */

	return error;

}

void TSL2561_handler(void *pvParameters){

	uint8_t pData[2];
	uint16_t adcData[2];

	memset(adcData, 0, 2);

	/* NOTE: Get ADC channel 0 lower byte */
	memset(pData, 0, (sizeof(pData) / sizeof(pData[0])));
	pData[0] = TSL2561_COMMAND_REG | TSL2561_DATA0LOW;
	if(HAL_I2C_Master_Transmit(&hi2c1, TSL2561_ADDR_FLOAT, pData,
			1, HAL_MAX_DELAY) != HAL_OK ){

		Error_Handler();
	}

	memset(pData, 0, (sizeof(pData) / sizeof(pData[0])));
	if(HAL_I2C_Master_Receive(&hi2c1, TSL2561_ADDR_FLOAT, pData,
			1, HAL_MAX_DELAY) != HAL_OK ){

		Error_Handler();
	}

	adcData[0] |= pData[0];

	/* NOTE: Get ADC channel 0 higher byte */
	memset(pData, 0, (sizeof(pData) / sizeof(pData[0])));
	pData[0] = TSL2561_COMMAND_REG | TSL2561_DATA0HIGH;
	if(HAL_I2C_Master_Transmit(&hi2c1, TSL2561_ADDR_FLOAT, pData,
			1, HAL_MAX_DELAY) != HAL_OK ){

		Error_Handler();
	}

	memset(pData, 0, (sizeof(pData) / sizeof(pData[0])));
	if(HAL_I2C_Master_Receive(&hi2c1, TSL2561_ADDR_FLOAT, pData,
			1, HAL_MAX_DELAY) != HAL_OK ){

		Error_Handler();
	}

	adcData[0] |= pData[0] << 8;

	/* NOTE: Get ADC channel 1 lower byte */
	memset(pData, 0, (sizeof(pData) / sizeof(pData[0])));
	pData[0] = TSL2561_COMMAND_REG | TSL2561_DATA1LOW;
	if(HAL_I2C_Master_Transmit(&hi2c1, TSL2561_ADDR_FLOAT, pData,
			1, HAL_MAX_DELAY) != HAL_OK ){

		Error_Handler();
	}

	memset(pData, 0, (sizeof(pData) / sizeof(pData[0])));
	if(HAL_I2C_Master_Receive(&hi2c1, TSL2561_ADDR_FLOAT, pData,
			1, HAL_MAX_DELAY) != HAL_OK ){

		Error_Handler();
	}

	adcData[1] |= pData[0];

	/* NOTE: Get ADC channel 1 higher byte */
	memset(pData, 0, (sizeof(pData) / sizeof(pData[0])));
	pData[0] = TSL2561_COMMAND_REG | TSL2561_DATA1HIGH;
	if(HAL_I2C_Master_Transmit(&hi2c1, TSL2561_ADDR_FLOAT, pData,
			1, HAL_MAX_DELAY) != HAL_OK ){

		Error_Handler();
	}

	memset(pData, 0, (sizeof(pData) / sizeof(pData[0])));
	if(HAL_I2C_Master_Receive(&hi2c1, TSL2561_ADDR_FLOAT, pData,
			1, HAL_MAX_DELAY) != HAL_OK ){

		Error_Handler();
	}

	adcData[1] |= pData[0] << 8;

	TSL2561_calculateLux(adcData);

}

static uint8_t TSL2561_calculateLux(uint16_t *adcData){

	/* NOTE: Calculate Lux */

}
