/**
  ******************************************************************************
  * @file    st7735.h
  * @brief   LSM6DS33 3D acc/gyro registers
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 Mateusz Szumilas @ WUT Faculty of Mechatronics.<br>
  * All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LSM6DS33_REG_H
#define __LSM6DS33_REG_H

// Default address
#define		ACC_GYRO_ADDR		(0x6B << 1)

// Embedded functions configuration register
#define		FUNC_CFG_ACCESS 	0x01

// FIFO configuration registers
#define		FIFO_CTRL1 			0x06
#define		FIFO_CTRL2 			0x07
#define		FIFO_CTRL3 			0x08
#define		FIFO_CTRL4 			0x09
#define		FIFO_CTRL5 			0x0A

#define		ORIENT_CFG_G 		0x0B

// INTx pin control
#define		INT1_CTRL 			0x0D
#define		INT2_CTRL 			0x0E

// Who I am ID
#define		WHO_AM_I 			0x0F

// Accelerometer and gyroscope control registers
#define		CTRL1_XL 			0x10
#define		CTRL2_G				0x11
#define		CTRL3_C				0x12
#define		CTRL4_C				0x13
#define		CTRL5_C				0x14
#define		CTRL6_C				0x15
#define		CTRL7_G				0x16
#define		CTRL8_XL			0x17
#define		CTRL9_XL			0x18
#define		CTRL10_C			0x19

// Interrupts registers
#define		WAKE_UP_SRC 		0x1B
#define		TAP_SRC 			0x1C
#define		D6D_SRC 			0x1D

// Status data register
#define		STATUS_REG			0x1E
// STATUS register bits
#define		SR_EV_BOOT			(1 << 3)
#define		SR_TDA				(1 << 2)
#define		SR_GDA				(1 << 1)
#define		SR_XLDA				(1 << 0)

// Temperature output data register
#define		OUT_TEMP_L			0x20
#define		OUT_TEMP_H			0x21

// Gyroscope output register
#define		OUTX_L_G			0x22
#define		OUTX_H_G			0x23
#define		OUTY_L_G			0x24
#define		OUTY_H_G			0x25
#define		OUTZ_L_G			0x26
#define		OUTZ_H_G			0x27

// Accelerometer output register
#define		OUTX_L_XL			0x28
#define		OUTX_H_XL			0x29
#define		OUTY_L_XL			0x2A
#define		OUTY_H_X			0x2B
#define		OUTZ_L_XL			0x2C
#define		OUTZ_H_XL			0x2D

// FIFO status registers
#define		FIFO_STATUS1		0x3A
#define		FIFO_STATUS2		0x3B
#define		FIFO_STATUS3		0x3C
#define		FIFO_STATUS4		0x3D

// FIFO data output registers
#define		FIFO_DATA_OUT_L		0x3E 
#define		FIFO_DATA_OUT_H		0x3F

// Timestamp output registers
#define		TIMESTAMP0_REG		0x40
#define		TIMESTAMP1_REG		0x41
#define		TIMESTAMP2_REG		0x42

// Step counter timestamp registers
#define		STEP_TIMESTAMP_L	0x49
#define		STEP_TIMESTAMP_H	0x4A

// Step counter output registers
#define		STEP_COUNTER_L		0x4B
#define		STEP_COUNTER_H		0x4C

// Interrupt register
#define		FUNC_SRC			0x53

// Interrupt registers
#define		TAP_CFG				0x58
#define		TAP_THS_6D			0x59
#define		INT_DUR2			0x5A
#define		WAKE_UP_THS			0x5B
#define		WAKE_UP_DUR			0x5C
#define		FREE_FALL			0x5D
#define		MD1_CFG				0x5E
#define		MD2_CFG				0x5F

#endif // __LSM6DS33_REG_H
