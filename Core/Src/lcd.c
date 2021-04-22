/**
  ******************************************************************************
  * @file    lcd.c
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

#include "lcd.h"

/******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/

/* ST7735 LCD SPI interface max baudrate is 15MHz for write and 6.66MHz for read
 *        Since the provided driver doesn't use read capability from LCD, only constraint
 *        on write baudrate is considered.
 */

/**
 * @{
 * LCD control signal handling
 */
#define LCD_CS_LOW()      HAL_GPIO_WritePin(LCD_CS_GPIO_PORT, LCD_CS_PIN, GPIO_PIN_RESET)
#define LCD_CS_HIGH()     HAL_GPIO_WritePin(LCD_CS_GPIO_PORT, LCD_CS_PIN, GPIO_PIN_SET)
#define LCD_DC_LOW()      HAL_GPIO_WritePin(LCD_DC_GPIO_PORT, LCD_DC_PIN, GPIO_PIN_RESET)
#define LCD_DC_HIGH()     HAL_GPIO_WritePin(LCD_DC_GPIO_PORT, LCD_DC_PIN, GPIO_PIN_SET)
#define LCD_RST_LOW()		HAL_GPIO_WritePin(LCD_RST_GPIO_PORT, LCD_RST_PIN, GPIO_PIN_RESET);
#define LCD_RST_HIGH()		HAL_GPIO_WritePin(LCD_RST_GPIO_PORT, LCD_RST_PIN, GPIO_PIN_SET);
/**
 * @}
 */

static void SPIx_Init(void);
static void SPIx_DeInit(void);

static void SPIx_Error(void);

void LCD_Delay(uint32_t Delay);

/**
  * @brief  SPI Write a byte to device
  * @param  Value: value to be written
  * @retval None
  */
static void SPIx_Write(uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_SPI_Transmit(hnucleo_Spi, (uint8_t *) &Value, 1, SPIX_TOUT);

  /* Check the communication status */
  if (status != HAL_OK)
  {
    /* Execute user timeout callback */
    SPIx_Error();
  }
}

/**
 * @brief 	SPI initialization function
 */
static void SPIx_Init(void)
{
	HAL_SPI_Init(hnucleo_Spi);
}

/**
 * @brief 	SPI deinitialization function
 */
static void SPIx_DeInit(void)
{
	HAL_SPI_DeInit(hnucleo_Spi);
}

/**
  * @brief  SPI error treatment function
  */
static void SPIx_Error(void)
{
  SPIx_DeInit();
  SPIx_Init();
}

/******************************************************************************
                            LINK OPERATIONS
*******************************************************************************/

/********************************* LINK LCD ***********************************/
/**
  * @brief  Initialize the LCD
  */
void LCD_IO_Init(void)
{
  /* Reset cycle */
  LCD_RST_HIGH();
  LCD_Delay(100);
  LCD_RST_LOW();
  LCD_Delay(100);
  LCD_RST_HIGH();
  LCD_Delay(100);

  /* LCD chip select high */
  LCD_CS_HIGH();

  /* LCD SPI Config */
  SPIx_Init();
}

/**
  * @brief  Send command to select the LCD register.
  *
  * @param  LCDReg: Address of the selected register.
  */
void LCD_IO_WriteReg(uint8_t LCDReg)
{
  LCD_CS_LOW();
  LCD_DC_LOW();

  /* Send Command */
  SPIx_Write(LCDReg);

  /* Deselect : Chip Select high */
  LCD_CS_HIGH();
}

/**
* @brief  Transmit data to the LCD.
*
* @param  pData: Pointer to the register transmission buffer
* @param  Size: Number of bytes to transmit to the LCD
*/
void LCD_IO_WriteMultipleData(uint8_t *pData, uint32_t Size)
{
  uint32_t counter = 0;
  __IO uint32_t data = 0;

  LCD_CS_LOW();
  LCD_DC_HIGH();

  if (Size == 1)
  {
    /* Only 1 byte to be sent to LCD - general interface can be used */
    /* Send Data */
    SPIx_Write(*pData);
  }
  else
  {
    /* Several data should be sent in a row */
    /* Direct SPI accesses for optimization */
    for (counter = Size; counter != 0; counter--)
    {
      while (((hnucleo_Spi->Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE)
      {
      }
      /* Need to invert bytes for LCD*/
      *((__IO uint8_t *)&hnucleo_Spi->Instance->DR) = *(pData + 1);

      while (((hnucleo_Spi->Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE)
      {
      }
      *((__IO uint8_t *)&hnucleo_Spi->Instance->DR) = *pData;
      counter--;
      pData += 2;
    }

    /* Wait until the bus is ready before releasing Chip select */
    while (((hnucleo_Spi->Instance->SR) & SPI_FLAG_BSY) != RESET)
    {
    }
  }

  /* Empty the Rx fifo */
  data = *(&hnucleo_Spi->Instance->DR);
  UNUSED(data);  /* Remove GNU warning */

  /* Deselect : Chip Select high */
  LCD_CS_HIGH();
}

/**
  * @brief  Blocking delay in ms.
  *
  * This function executes the @b HAL_Delay function.
  *
  * @param  Delay: delay in ms.
  * @retval None
  */
void LCD_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}
