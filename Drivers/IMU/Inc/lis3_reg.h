/*
 * lis3mdl_reg.h
 *      Author: Karol Zalewski
 *
 * sources:
 https://github.com/STMicroelectronics/lis3mdl/blob/f037f39466143fd9535a9e7fcee79c02cafd0114/lis3mdl_reg.h
 https://github.com/STMicroelectronics/STMems_Standard_C_drivers/tree/master/lsm6ds3_STdC/examples
 */


#ifndef IMU_INC_LIS3MDL_REG_H_
#define IMU_INC_LIS3MDL_REG_H_

#define		MAG_ADDR		(0x1E << 1) //adres czujnika

#define		SR_ZYXOR			(1 << 8) // 8 bit STATUS_REG = ZYXOR
#define		SR_ZYXDA			(1 << 4) //4 bit STATUS_REG = ZYXDA

#define		WHO_AM_I_M 			0x0F //Device identification register

#define		CTRL_REG1 			0x20 //power mode i frequency
#define		CTRL_REG2			0x21 //zakres pomiarowy
#define		CTRL_REG3			0x22
#define		CTRL_REG4			0x23
#define		CTRL_REG5			0x24

#define		STATUS_REG_mag			0x27   //  ZXXOR (data has overiten) ZYXDA (data is available)

// wartosci wyjsciowe sk�adajace sie z dwuch bajtow
#define		OUT_X_L			0x28  
#define		OUT_X_H			0x29
#define		OUT_Y_L			0x2A
#define		OUT_Y_H			0x2B
#define		OUT_Z_L			0x2C  
#define		OUT_Z_H			0x2D
#define		TEMP_OUT_L		0x2E
#define		TEMP_OUT_H		0x2F

#define		INT_CFG			0x30 //konfiguracja przerwan
#define		INT_SRC			0x31
#define		INT_THS_L		0x32
#define		INT_THS_H		0x33

#endif 
