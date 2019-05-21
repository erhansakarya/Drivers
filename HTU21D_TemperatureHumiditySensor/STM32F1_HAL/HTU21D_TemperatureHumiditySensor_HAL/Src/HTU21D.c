#include <math.h>
#include <string.h>

#include "main.h"
#include "HTU21D.h"

static uint8_t HTU21D_softReset(void);
static uint8_t HTU21D_configUserRegister(HTU21D_measRes_e measRes);
static void calculateTempHum(uint16_t *rawValues, void *htu21d);

uint8_t HTU21D_init(void){

	uint8_t error = 0;

	HTU21D_softReset();
	HTU21D_configUserRegister(RH12TEMP14);

	return error;

}

static uint8_t HTU21D_softReset(void){

	uint8_t error = 0;
	uint8_t pData = 0;

	HAL_Delay(15);

	/* NOTE: Send soft reset command */
	pData = HTU21D_SOFT_RESET;
	if(HAL_I2C_Master_Transmit(&hi2c1, HTU21D_ADDR, &pData,
					1, HAL_MAX_DELAY) != HAL_OK ){

		Error_Handler();
	}

	HAL_Delay(15);

	return error;

}

static uint8_t HTU21D_configUserRegister(HTU21D_measRes_e measRes){

	uint8_t status = 0;
	uint8_t pData[2];

	/* NOTE: Send Read User Register Command */
	memset(pData, 0, sizeof(pData) / sizeof(pData[0]));
	pData[0] = HTU21D_RD_USRREG;
	if(HAL_I2C_Master_Transmit(&hi2c1, HTU21D_ADDR, pData,
					1, HAL_MAX_DELAY) != HAL_OK ){

		Error_Handler();
	}

	/* NOTE: Read User Register */
	memset(pData, 0, sizeof(pData) / sizeof(pData[0]));
	if(HAL_I2C_Master_Receive(&hi2c1, HTU21D_ADDR, &pData[1],
					1, HAL_MAX_DELAY) != HAL_OK ){

		Error_Handler();
	}

	/* NOTE: Manipulate User Register Value */
	pData[1] |= measRes;

	/* NOTE: Send Write User Register Command and Write Manipulated Value */
	pData[0] = HTU21D_WR_USRREG;
	if(HAL_I2C_Master_Transmit(&hi2c1, HTU21D_ADDR, pData,
					2, HAL_MAX_DELAY) != HAL_OK ){

		Error_Handler();
	}

	/* NOTE: Read again user register value for verify */

	return status;

}

void HTU21D_handler(void *htu21d){

	uint8_t pData[2];
	uint8_t temp[3];
	uint8_t hum[3];
	uint16_t rawValues[2];

	memset(pData, 0, sizeof(pData) / sizeof(pData[0]));
	memset(temp, 0, sizeof(temp) / sizeof(temp[0]));
	memset(hum, 0, sizeof(hum) / sizeof(hum[0]));
	memset(rawValues, 0, sizeof(rawValues) / sizeof(uint8_t));

	for(;;){

		HAL_Delay(50);

		/* NOTE: Send Trigger temperature measurement in hold master Command */
		memset(pData, 0, sizeof(pData) / sizeof(pData[0]));
		pData[0] = HTU21D_TEMP_HOLD;
		if(HAL_I2C_Master_Transmit(&hi2c1, HTU21D_ADDR, pData,
						1, HAL_MAX_DELAY) != HAL_OK ){

			Error_Handler();
		}

		/* NOTE: Read Temperature(MSB+LSB+CRC) */
		if(HAL_I2C_Master_Receive(&hi2c1, HTU21D_ADDR, temp,
						3, HAL_MAX_DELAY) != HAL_OK ){

			Error_Handler();
		}

		rawValues[0] = (temp[0] << 8) | (temp[1] & ~0x03);

		HAL_Delay(20);

		/* NOTE: Send Trigger humidity measurement in hold master Command */
		memset(pData, 0, sizeof(pData) / sizeof(pData[0]));
		pData[0] = HTU21D_HUM_HOLD;
		if(HAL_I2C_Master_Transmit(&hi2c1, HTU21D_ADDR, pData,
						1, HAL_MAX_DELAY) != HAL_OK ){

			Error_Handler();
		}

		/* NOTE: Read Humidity(MSB+LSB+CRC) */
		if(HAL_I2C_Master_Receive(&hi2c1, HTU21D_ADDR, hum,
						3, HAL_MAX_DELAY) != HAL_OK ){

			Error_Handler();
		}

		rawValues[1] = (hum[0] << 8) | (hum[1] & ~0x03);

		calculateTempHum(rawValues, htu21d);

	}

}

static void calculateTempHum(uint16_t *rawValues, void *htu21d){

	HTU21D_s *HTU21D_temporary = (HTU21D_s *) htu21d;

	HTU21D_temporary->temperature = ( -46.85 + (175.72 * (rawValues[0] / pow(2, 16))) );
	HTU21D_temporary->humidity = ( -6 + (125 * (rawValues[1] / pow(2, 16))) );

}
