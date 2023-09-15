/*
 * am2302.c
 *
 *  Created on: Nov 11, 2022
 *      Author: andre
 */

#include <stdint.h>

#include "main.h"
#include "systemfunctions.h"
#include "ports.h"
#include "projectconf.h"

#include "am2302.h"

static void am2302_Start(void);
static void am2302_Convert_Raw_Data(uint8_t *dataBuff, float *temp, float *humi);


void am2302_Read(float *temp, float *humi)
{

	uint8_t dataBuff[40] = {0};

	uint32_t timeStampAM2302 = 0;

	am2302_Start();

	while(Get_Port_Pin_State(DATA_PORT, DATA_PIN)); // Sensor pull down

	while(!(Get_Port_Pin_State(DATA_PORT, DATA_PIN))); // Sensor pull up

	// Sensor sends data

	while(Get_Port_Pin_State(DATA_PORT, DATA_PIN)); // Sensor pull down to start sending data

	// Read 40 bit from the sensor

	for(int i = 39 ; i >= 0 ; i--)
	{

		while(!(Get_Port_Pin_State(DATA_PORT, DATA_PIN))); // Sensor pull up

		timeStampAM2302 = Get_SystemTimeUs();

		while(Get_Port_Pin_State(DATA_PORT, DATA_PIN)); // Sensor pull down

		dataBuff[i] = (Compare_SystemTimeUs(timeStampAM2302) < 5) ? 0 : 1;

	}

	// Convert raw data into engineering values of humidity and temperature

	am2302_Convert_Raw_Data(dataBuff, temp, humi);


}


void am2302_Start(void)
{

	uint32_t timeStampAM2302 = 0;

	uint32_t *pGPIOMODER = (uint32_t *)0x40023800U;

	// set as an Output

	*pGPIOMODER |= ( 0x1 << (8 * 2) ); // GPIOB_8 output mode


	Port_Pin_Toggle(DATA_PORT, DATA_PIN);

	timeStampAM2302 = Get_SystemTimeUs();

	while(Compare_SystemTimeUs(timeStampAM2302) < 200); // 2Ms delay

	Port_Pin_Toggle(DATA_PORT, DATA_PIN);

	// set as an input

	*pGPIOMODER &= ~( 0x00 << (8 * 2) ); // GPIOB_8 input mode

}

void am2302_Convert_Raw_Data(uint8_t *dataBuff, float *temp, float *humi)
{

	uint16_t humiRawData = 0;
	uint16_t tempRawData = 0;

	for(int i = 0 ; i < 16 ; i++)
	{

		humiRawData |= ( dataBuff[AM2302_HUMI_START_INDEX - i] << ( 15 - i ) );
		tempRawData |= ( dataBuff[AM2302_TEMP_START_INDEX - i] << ( 15 - i ) );

	}

	*temp = ( tempRawData / 10 );
	*humi = ( humiRawData / 10 );

}
