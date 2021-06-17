/**
  ******************************************************************************
  * @file    flick.c
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 Mateusz Szumilas @ WUT Faculty of Mechatronics.<br>
  * All rights reserved.
  *
  * This software component is licensed under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

#include "./Inc/flick.h"

static uint8_t flick_payload[255];	/**< local buffer for reception of messages from the Flick board */

/**
 * @{
 * Flick control signal handling
 */
#define FLICK_TS_LOW()      HAL_GPIO_WritePin(FLICK_TS_GPIO_PORT, FLICK_TS_PIN, GPIO_PIN_RESET)
#define FLICK_TS_HIGH()     HAL_GPIO_WritePin(FLICK_TS_GPIO_PORT, FLICK_TS_PIN, GPIO_PIN_SET)
#define FLICK_TS_GET()     	HAL_GPIO_ReadPin(FLICK_TS_GPIO_PORT, FLICK_TS_PIN)

#define FLICK_RESET_LOW()      HAL_GPIO_WritePin(FLICK_RESET_GPIO_PORT, FLICK_RESET_PIN, GPIO_PIN_RESET)
#define FLICK_RESET_HIGH()     HAL_GPIO_WritePin(FLICK_RESET_GPIO_PORT, FLICK_RESET_PIN, GPIO_PIN_SET)
/**
 * @}
 */

/**
 * @brief This function checks the Flick board for data availability (TS line)
 * and if available, receives it to the @b flick_payload buffer.
 *
 * @return Type of the message received
 */
flick_msg_t flick_receive(void)
{
	flick_msg_t ret = FLICK_MSG_NO_MSG;

	// only if the TS is asserted by the MGC3X30
	if (FLICK_TS_GET() == GPIO_PIN_RESET)
	{
		FLICK_TS_LOW();

		// get header
		HAL_I2C_Master_Receive(hi2cflick, FLICK_ADDR, flick_payload, 255, 10);

		switch (flick_payload[3])
		{
			case 0x15:
				ret = FLICK_MSG_SYSTEM_STATUS;
				break;
			case 0x83:
				ret = FLICK_MSG_FW_VERSION_INFO;
				break;
			case 0x91:
				ret = FLICK_MSG_SENSOR_DATA;
				break;
			default:
				ret = FLICK_MSG_UNKNOWN;
				break;
		}

		FLICK_TS_HIGH();
	}

	return ret;
}

void flick_reset(void)
{
	FLICK_RESET_LOW();
	HAL_Delay(10);
	FLICK_RESET_HIGH();
	HAL_Delay(10);

	//flick_msg_t msg_type = flick_receive();
}

void flick_set_param(uint16_t param_ID, uint32_t arg0, uint32_t arg1)
{
	uint8_t msg[16] = {0};

	msg[0] = 0x10;
	msg[3] = 0xA2;
	msg[4] = param_ID & 0xFF;
	msg[5] = param_ID >> 8;
	msg[8] = arg0 & 0xFF;
	msg[9] = (arg0>>8) & 0xFF;
	msg[10] = (arg0>>16) & 0xFF;
	msg[11] = (arg0>>24) & 0xFF;
	msg[12] = arg1 & 0xFF;
	msg[13] = (arg1>>8) & 0xFF;
	msg[14] = (arg1>>16) & 0xFF;
	msg[15] = (arg1>>24) & 0xFF;

	HAL_I2C_Master_Transmit(hi2cflick, FLICK_ADDR, msg, 16, 10);
}

flick_data_t flick_poll_data(uint32_t* gest_info, uint32_t* touch_info, airwheel_data_t* airwheel)
{
	flick_data_t ret = FLICK_NO_DATA;

	if (flick_receive() == FLICK_MSG_SENSOR_DATA)
	{
		uint16_t data_out_mask = (flick_payload[5] << 8) + flick_payload[4]; //strona 42 w dokumentacji
		uint8_t sys_info = flick_payload[7];

		uint8_t data_ptr = 8;

		// check DSPStatus field
		if (data_out_mask & (1<<0))
		{
			data_ptr += 2;
		}

		// check GestureInfo field
		if (data_out_mask & (1<<1))
		{
			*gest_info = (flick_payload[3+data_ptr] << 24) +
					(flick_payload[2+data_ptr] << 16) +
					(flick_payload[1+data_ptr] << 8) +
					flick_payload[data_ptr];

			data_ptr += 4;
			ret = FLICK_NEW_DATA;
		}

		// check TouchInfo field
		if (data_out_mask & (1<<2))
		{
			*touch_info = (flick_payload[3+data_ptr] << 24) +
					(flick_payload[2+data_ptr] << 16) +
					(flick_payload[1+data_ptr] << 8) +
					flick_payload[data_ptr];

			data_ptr += 4;
			ret = FLICK_NEW_DATA;
		}

		// check AirWheelInfo field
		if ((data_out_mask & (1<<3)) && (sys_info & (1<<1)))
		{
			airwheel->position = flick_payload[data_ptr] & 0x1F;
			airwheel->count = flick_payload[data_ptr] >>5;
			airwheel->new_data = FLICK_NEW_DATA;

			data_ptr += 2;
			ret = FLICK_NEW_DATA;
		}

		//check XYZPosition field
		if ((data_out_mask & (1<<4))&&(sys_info & (1<<0)))
		{
			airwheel->Z = (flick_payload[5+data_ptr] << 8) +
					(flick_payload[4+data_ptr]);
			airwheel->Y = (flick_payload[3+data_ptr] << 8) +
					(flick_payload[2+data_ptr]);
			airwheel->X = (flick_payload[1+data_ptr] << 8) +
					(flick_payload[data_ptr]);


			data_ptr += 6;
			ret = FLICK_NEW_DATA;
		}

	}

	return ret;
}

void flick_gesture_set(void)
{
	//ustawienie odpowiednich parametrow do wlaczenia airwheela
	flick_set_param(0x90, 0x20, 0x20);
	//ustawienie odpowiednich parametrow do wlaczenia dotyku
	flick_set_param(0x97, 0x08, 0x08);
	//ustawienie odpowiednich parametrow do wlaczenia przesunięcia nad flickiem
	flick_set_param(0x85, 0x66, 0x66);
	//ustawiony został bit 1, 2, 5, 6. 37 strona w dokumentacji tlumaczy co oznaczaja odpowiednie bity
}

uint8_t old_angular_position = 0;
uint8_t flick_airwheel_direction(airwheel_data_t airwheel)
{
	uint8_t gesture_rot_direction = 0;

	//obrót w prawo zwraca 1 (za GUI)
	if(airwheel.position>old_angular_position)
		gesture_rot_direction=1;
	//obrót w lewo zwraca
	else if(airwheel.position<old_angular_position)
		gesture_rot_direction=2;

	old_angular_position=airwheel.position;
	airwheel.new_data = FLICK_NO_DATA;
	return gesture_rot_direction;
}

uint8_t flick_gesture_value(uint32_t gesture)
{
	uint8_t gesture_number = 0;
	//West to East
	if((gesture & 0xFF)==2)
		gesture_number = 1;
	//East to West
	if ((gesture & 0xFF)==3)
		gesture_number = 2;
	//South to North
	if ((gesture & 0xFF)==4)
		gesture_number = 3;
	//North to South
	if ((gesture & 0xFF)==5)
		gesture_number = 4;
	return gesture_number;
}
uint8_t flick_touch_position (airwheel_data_t airwheel)
{
	uint8_t touch_q = 0;
	if(airwheel.Z == 0)
	{
		if (airwheel.X < 32500 && airwheel.Y > 32500)
			touch_q = 1;
		if (airwheel.X > 32500 && airwheel.Y > 32500)
			touch_q = 2;
		if (airwheel.X < 32500 && airwheel.Y < 32500)
			touch_q = 3;
		if (airwheel.X > 32500 && airwheel.Y < 32500)
			touch_q = 4;
		}
	return touch_q;
}
