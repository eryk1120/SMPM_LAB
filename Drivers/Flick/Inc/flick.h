/**
  ******************************************************************************
  * @file    flick.h
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

#ifndef INC_FLICK_H_
#define INC_FLICK_H_

/**
 * @addtogroup Flick
 *
 * @brief A module for the Flick board.
 *
 * The Flick interface board is based on the MGC3130 IC, which is an 3D motion
 * tracking and gesture recognition controller based on the electrical
 * near-field sensing technology.
 *
 * Flick supplier page: https://uk.pi-supply.com/products/flick-large-standalone-3d-tracking-gesture-breakout
 *
 * @{
 */

#include "stm32l4xx_hal.h"

#define FLICK_ADDR		(0x42 << 1)		///< The I2C address of the Flick board.

#define FLICK_TS_GPIO_PORT 	GPIOC			///< The GPIO PORT of the TS signal.
#define FLICK_TS_PIN 		GPIO_PIN_5		///< The GPIO PIN of the TS signal.

#define FLICK_RESET_GPIO_PORT 	GPIOC		///< The GPIO PORT of the RESET signal.
#define FLICK_RESET_PIN 		GPIO_PIN_6	///< The GPIO PIN of the RESET signal.

/**
 * @brief Data type for reporting the types of the Flick board messages
 */
typedef enum {
	FLICK_MSG_SYSTEM_STATUS,  /**< 0 */
	FLICK_MSG_FW_VERSION_INFO,/**< 1 */
	FLICK_MSG_SENSOR_DATA,    /**< 2 */
	FLICK_MSG_UNKNOWN,        /**< 3 */
	FLICK_MSG_NO_MSG          /**< 4 */
} flick_msg_t;

/**
 * @brief Data type for reporting availability of new data
 */
typedef enum {
	FLICK_NO_DATA,	/**< 0 */
	FLICK_NEW_DATA	/**< 1 */
} flick_data_t;

/**
 * @brief Data type for reporting AirWheel status
 */
typedef struct {
	flick_data_t new_data;	/**< is new valid data reported? */
	uint8_t position;		/**< the current angular position with a resolution of 32 counts for a full revolution */
	uint8_t count;			/**< counts of full rotations */
} airwheel_data_t;


typedef struct {
	flick_data_t new_data;	/**< is new valid data reported? */
	uint32_t gesture, touch;
	uint16_t X;
	uint16_t Y;
	uint16_t Z;
} gest_touch_xyz_data_t;

/**
 * A handle for the I2C control structure (as used in the STM32 HAL library).
 * The structure should be initialized in the main user code
 * and assigned to this pointer.
 */
extern I2C_HandleTypeDef *hi2cflick;

/**
 * @brief This function resets the Flick board.
 */
void flick_reset(void);

/**
 * @brief This function sets a specifed run-time parameter.
 *
 * @param param_ID		ID of run-time parameter
 * @param arg0			first argument, depending on the run-time parameter
 * 						(if not used, should be provided as '0')
 * @param arg1			second argument, depending on the run-time parameter
 * 						(if not used, should be provided as '0')
 */
void flick_set_param(uint16_t param_ID, uint32_t arg0, uint32_t arg1);

/**
 * @brief This function polls the Flick board for new data.
 *
 * An avalability of new gesture, touch or airwheel data is checked.
 *
 * @param gest_info		the 32-bit gesture information (GestureInfo field of the SENSOR_DATA_OUTPUT message)
 * @param touch_info	the 32-bit gesture information (TouchInfo field of the SENSOR_DATA_OUTPUT message)
 * @param airwheel		the @b airwheel_data_t structure, updated according to the received data (if any)
 * @return FLICK_NEW_DATA: if any data is available
 */
flick_data_t flick_poll_data(gest_touch_xyz_data_t* gest_touch_xyz, airwheel_data_t* airwheel);

int  pozycja (gest_touch_xyz_data_t* gest_touch_xyz);

/**
 * @}
 */

#endif /* INC_FLICK_H_ */
