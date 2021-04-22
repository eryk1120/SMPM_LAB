/**
  ******************************************************************************
  * @file    lcd.h
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2015 STMicroelectronics.<br>
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

#ifndef INC_LCD_H_
#define INC_LCD_H_

/**
 * @addtogroup LCD_ST7735
 *
 * @brief A module for an ST7735-based LCD.
 *
 * @{
 */

#include "stm32l4xx_hal.h"

#define SPIX_TOUT 5			///< SPI transmission timeout for HAL-based @b SPIx_Write

#define LCD_CS_PIN                 GPIO_PIN_2	///< The GPIO PORT of the CS signal.
#define LCD_CS_GPIO_PORT           GPIOC		///< The GPIO PIN of the CS signal.

#define LCD_RST_PIN                GPIO_PIN_1	///< The GPIO PORT of the RST signal.
#define LCD_RST_GPIO_PORT          GPIOC		///< The GPIO PIN of the RST signal.

#define LCD_DC_PIN                 GPIO_PIN_0	///< The GPIO PORT of the DC signal.
#define LCD_DC_GPIO_PORT           GPIOC		///< The GPIO PIN of the DC signal.

/**
 * A handle for the SPI control structure (as used in the STM32 HAL library).
 * The structure should be initialized in the main user code
 * and assigned to this pointer.
 */
extern SPI_HandleTypeDef *hnucleo_Spi;

/**
 * @}
 */

#endif /* INC_LCD_H_ */
