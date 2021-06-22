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

#include "IMU.h"

void init_IMU(I2C_HandleTypeDef hi2c2) {
	uint8_t i2c2_buf[10]; // T tablica buforów do których są wczytywane dane z kolejnych wybranych rejestrów czujnika
	HAL_I2C_Mem_Read(&hi2c2, ACC_GYRO_ADDR, WHO_AM_I, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1); // konfiguracja odczytu po magistrali I2C
	HAL_I2C_Mem_Read(&hi2c2, 0x1e << 1, 0x0f, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf + 1, 1, 1); // konfiguracja odczytu po magistrali I2C

	char str[40];
	sprintf(str, "Who? A/G:%02x M:%02x", i2c2_buf[0], i2c2_buf[1]);
	BSP_LCD_DisplayStringAtLine(10, (uint8_t*) str);

	// konfiguracja żyroskopu
	i2c2_buf[0] = 0x38; //uruchomienie odczytu kątów X,Y,Z
	HAL_I2C_Mem_Write(&hi2c2, ACC_GYRO_ADDR, CTRL10_C, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1);

	i2c2_buf[0] = 0x14; // ustawienie częstotliwości i zakresu: 13 Hz ODR, 500 dps
	HAL_I2C_Mem_Write(&hi2c2, ACC_GYRO_ADDR, CTRL2_G, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1);

	// konfiguracja akcelerometru
	i2c2_buf[0] = 0x38; // uruchomienie odczytu kątów X,Y,Z
	HAL_I2C_Mem_Write(&hi2c2, ACC_GYRO_ADDR, CTRL9_XL, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1);

	i2c2_buf[0] = 0x10; // ustawienie częstotliwości i zakresu: 13 Hz ODR, +/- 2 g
	HAL_I2C_Mem_Write(&hi2c2, ACC_GYRO_ADDR, CTRL1_XL, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1);

	// konfiguracja magnetometru
	i2c2_buf[0] = 0xE0; //11100000,  // uruchomienie generowania przerwań X,Y,Z
	HAL_I2C_Mem_Write(&hi2c2, MAG_ADDR, INT_CFG, I2C_MEMADD_SIZE_8BIT, i2c2_buf,
			1, 1);

	i2c2_buf[0] = 0x70; //   01110000, ustawienie czestotliwosci 10 Hz, i trybu  High-power mode, brak odczytu temperatury, self test wyłączony
	HAL_I2C_Mem_Write(&hi2c2, MAG_ADDR, CTRL_REG1, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1);

	i2c2_buf[0] = 0x00; // 00000000 ustawienie zakresu pomiarowego +-4 gauss
	HAL_I2C_Mem_Write(&hi2c2, MAG_ADDR, CTRL_REG2, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1);

	i2c2_buf[0] = 0x00; //00000000 ustawienie trybu Low-power mode, oraz Continuous-conversion mode
	HAL_I2C_Mem_Write(&hi2c2, MAG_ADDR, CTRL_REG3, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1);
}

void wczytywanie_IMU(float *IMU_raw, I2C_HandleTypeDef hi2c2) {

	int16_t odczyt[9] = { 0 }; //tablica z odczytywanymi zmiennymi
	char str[40];
	uint8_t i2c2_buf[10]; // tablica buforów do których są wczytywane dane z kolejnych wybranych rejestrów czujnika */
	uint16_t pom; // zmienna pomocnicza 16 bitowa typu int

	HAL_I2C_Mem_Read(&hi2c2, ACC_GYRO_ADDR, STATUS_REG, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1);
	uint8_t tmp_stat_acc = i2c2_buf[0];

	if (tmp_stat_acc & SR_XLDA) // dostępne nowe dane z akcelerometru
	{
		HAL_I2C_Mem_Read(&hi2c2, ACC_GYRO_ADDR, OUTX_L_XL, I2C_MEMADD_SIZE_8BIT,
				i2c2_buf, 6, 1); /* odczytwartosci z czujnika
				 dodanie bajtu starszego z mlodszym, starszy bajt przesuwam o 8 bitów w lewo, */
		pom = i2c2_buf[1] << 8;
		odczyt[0] = i2c2_buf[0] + pom;
		pom = i2c2_buf[3] << 8;
		odczyt[1] = i2c2_buf[2] + pom;
		pom = i2c2_buf[5] << 8;
		odczyt[2] = i2c2_buf[4] + pom;

		/* zamiana jednostek z int16_t na odpowiednie jednostki fizyczne
		 acc dla zakresu +-2g, wynikw [m/s^2]
		 */
		IMU_raw[0] = (float) odczyt[0] * 2 * 9.81 / 32768;
		IMU_raw[1] = (float) odczyt[1] * 2 * 9.81 / 32768;
		IMU_raw[2] = (float) odczyt[2] * 2 * 9.81 / 32768;

		//	  sprintf(str, "acc %+4hi%+4hi%+4hi",
		//			  (int16_t)*(odczyt + 1), (int16_t)*(odczyt + 2), (int16_t)*(odczyt + 3));
		//	 BSP_LCD_DisplayStringAtLine(12, (uint16_t *) str);
	}

	if (tmp_stat_acc & SR_GDA) // dostępne nowe dane gyroscope
	{
		HAL_I2C_Mem_Read(&hi2c2, ACC_GYRO_ADDR, OUTX_L_G, I2C_MEMADD_SIZE_8BIT,
				i2c2_buf, 6, 1); /* odczytwartosci z czujnika
				 polaczenie bajtu starszego z mlodszym, starszy bajt przesuwam o 8 bitów lewo, dodaje bajty */
		pom = i2c2_buf[1] << 8;
		odczyt[3] = i2c2_buf[0] + pom;
		pom = i2c2_buf[3] << 8;
		odczyt[4] = i2c2_buf[2] + pom;
		pom = i2c2_buf[5] << 8;
		odczyt[5] = i2c2_buf[4] + pom;

		/*zamiana jednostek z int16_t na odpowiednie jednostki fizyczne
		 gyro dla zakresu 500dps, [radians per second] */
		IMU_raw[3] = (float) odczyt[3] * 500 / 32768 * 0.01745;
		IMU_raw[4] = (float) odczyt[4] * 500 / 32768 * 0.01745;
		IMU_raw[5] = (float) odczyt[5] * 500 / 32768 * 0.01745;

		//	  sprintf(str, "acc %+4hi%+4hi%+4hi",
		//			  (int16_t)*(odczyt + 4), (int16_t)*(odczyt + 5), (int16_t)*(odczyt + 6));
		//	 BSP_LCD_DisplayStringAtLine(12, (uint16_t *) str);
	}

	HAL_I2C_Mem_Read(&hi2c2, MAG_ADDR, STATUS_REG_mag, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf + 1, 1, 1);
	uint8_t tmp_stat_mag = i2c2_buf[1];

	if (tmp_stat_mag & SR_ZYXDA) // dostępne nowe dane magnetometr
	{
		HAL_I2C_Mem_Read(&hi2c2, MAG_ADDR, OUT_X_L, I2C_MEMADD_SIZE_8BIT,
				i2c2_buf, 6, 1); // odczyt wartosci z czujnika
		// polaczenie bajtu starszego z mlodszym, starszy bajt przesuwam o 8 bitów lewo, dodaje bajty
		pom = i2c2_buf[1] << 8;
		odczyt[6] = i2c2_buf[0] + pom;
		pom = i2c2_buf[3] << 8;
		odczyt[7] = i2c2_buf[2] + pom;
		pom = i2c2_buf[5] << 8;
		odczyt[8] = i2c2_buf[4] + pom;

		/* zamiana jednostek z int16_t na odpowiednie jednostki fizyczne
		 magnetometr dla zakresu +-4Gs, wynikw [Gs], korekda doświadczalnie wyznaczona */
		IMU_raw[6] = ((float) odczyt[6] - 2037) * 4 / 32768;
		IMU_raw[7] = ((float) odczyt[7] + 2037) * 4 / 32768;
		IMU_raw[8] = ((float) odczyt[8] + 570) * 4 / 32768;

		//	  sprintf(str, "acc %+4hi%+4hi%+4hi",
		//			  (int16_t)*(odczyt + 7), (int16_t)*(odczyt + 8), (int16_t)*(odczyt + 9));
		//	 BSP_LCD_DisplayStringAtLine(12, (uint16_t *) str);
	}

	//	  sprintf(str, "acc %+4hi%+4hi%+4hi",
	//			  (float)*(IMU_raw + 1), (float)*(IMU_raw + 2), (float)*(IMU_raw + 3));
	//	  sprintf(str, "acc %+4hi%+4hi%+4hi",
	//			  (float)*(IMU_raw + 4), (float)*(IMU_raw + 5), (float)*(IMU_raw + 6));
	//	  sprintf(str, "acc %+4hi%+4hi%+4hi",
	//			  (float)*(IMU_raw + 7), (float)*(IMU_raw + 8), (float)*(IMU_raw + 9));
}

void Euler(float *IMU_raw, int16_t *eulerAngles) {

	// Calculating raw values: pitch, theta gathered only from acceleroemter
	thetaRAW_a = -atan2(IMU_raw[0] / 9.8, IMU_raw[2] / 9.8) / 2 / 3.141592654
			* 360;
	phiRAW_a = -atan2(IMU_raw[1] / 9.8, IMU_raw[2] / 9.8) / 2 / 3.141592654
			* 360;

	// Calculating low-pass filtered values: pitch, theta gathered only from acceleroemter
	phiFIL_a = .93 * phiFIL_a_old + .07 * phiRAW_a;
	thetaFIL_a = .93 * thetaFIL_a_old + .07 * thetaRAW_a;

	// Timer values for calculating raw values: pitch, theta gathered only from gyroscope
	uwTick = (uwTick - uwTickOld);
	uwTickOld = uwTick;

	// Calculating raw values: pitch, theta gathered only from gyroscope
	thetaRAW_g = thetaRAW_g + IMU_raw[4] * uwTick;
	phiRAW_g = phiRAW_g - IMU_raw[3] * uwTick;

	// Calculating complementary filtred final values: pitch, theta gatheredfrom accelerometer and gyroscope
	thetaGLOBAL = (thetaGLOBAL + IMU_raw[4] * uwTick) * .93 + thetaFIL_a * .07;
	phiGLOBAL = (phiGLOBAL - IMU_raw[3] * uwTick) * .93 + phiFIL_a * .07;
	phiGLOBAL_rad = phiGLOBAL / 360 * (2 * 3.141592654);
	thetaGLOBAL_rad = thetaGLOBAL / 360 * (2 * 3.141592654);

	// Calculating complementary filtered final values: yaw from accelerometer, gyroscope and magnetometer
	yawX = IMU_raw[6] * cos(thetaGLOBAL_rad)
			- IMU_raw[7] * sin(phiGLOBAL_rad) * sin(thetaGLOBAL_rad)
			+ IMU_raw[8] * cos(phiGLOBAL_rad) * sin(thetaGLOBAL_rad);
	yawY = IMU_raw[7] * cos(phiGLOBAL_rad) + IMU_raw[8] * sin(phiGLOBAL_rad);
	psiGLOBAL_rad = atan2(yawY, yawX) / (2 * 3.141592654) * 360;

	// phi = roll (around X axis)
	eulerAngles[0] = phiGLOBAL_rad;

	// theta = pitch (around Y axis)
	eulerAngles[1] = thetaGLOBAL_rad;

	// psi = yaw (around Z axis)
	eulerAngles[2] = psiGLOBAL_rad;

	// Getting old values for compensated filtering pitch, roll and yaw
	phiFIL_a_old = phiFIL_a;
	thetaFIL_a_old = thetaFIL_a;

}

