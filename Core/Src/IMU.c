/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : IMU.c
  * @brief          : STM32L476 Nucleo-64 Workbench Tests @ WUT Mchtr
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.<br>
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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "IMU.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
#include "stm32_adafruit_lcd.h"
#include "flick.h"
#include "lsm6ds33_reg.h"
#include "lis3_reg.h"
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

// Floats for raw values: pitch, theta gathered only from acceleroemter 
  float phiRAW_a;
  float thetaRAW_a;
  
  // Floats for filtered values: pitch, theta gathered only from acceleroemter 
  float phiFIL_a;
  float phiFIL_a_old;
  float thetaFIL_a;
  float thetaFIL_a_old;

  // Floats for raw values: pitch, theta gathered only from gyroscope
  float phiRAW_g;
  float thetaRAW_g;
  float uwTickOld;  

  // Floats for compensated final values: pitch, theta gathered from accelerometer and gyroscope
  float phiGLOBAL;
  float phiGLOBAL_rad;
  float thetaGLOBAL;
  float thetaGLOBAL_rad;

  // Floats for compensated final values: yaw gathered from accelerometer, gyroscope and magnetometer 
  float yawX;
  float yawY;
  float psiGLOBAL_rad;

  // int8_t table for eulerAngles [0] for pitch, [1] for roll, [2] for yaw
  int8_t eulerAngles[3] = {0};

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void Euler();

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/

/* USER CODE BEGIN 0 */

void Euler()
{

  // Calculating raw values: pitch, theta gathered only from acceleroemter 
  thetaRAW_a=-atan2(odczyt[0]/9.8,odczyt[2]/9.8)/2/3.141592654*360;
  phiRAW_a=-atan2(odczyt[1]/9.8,odczyt[2]/9.8)/2/3.141592654*360;

  // Calculating low-pass filtered values: pitch, theta gathered only from acceleroemter 
  phiFIL_a=.93*phiFIL_a_old+.07*phiRAW_a;
  thetaFIL_a=.93*thetaFIL_a_old+.07*thetaRAW_a;

  // Timer values for calculating raw values: pitch, theta gathered only from gyroscope
  uwTick=(uwTick-uwTickOld);
  uwTickOld=uwTick;

  // Calculating raw values: pitch, theta gathered only from gyroscope
  thetaRAW_g=thetaRAW_g+odczyt[4]*uwTick;
  phiRAW_g=phiRAW_g-odczyt[3]*uwTick;

  // Calculating complementary filtred final values: pitch, theta gatheredfrom accelerometer and gyroscope
  thetaGLOBAL=(thetaGLOBAL+odczyt[4]*uwTick)*.93+thetaFIL_a*.07;
  phiGLOBAL=(phiGLOBAL-odczyt[3]*uwTick)*.93+ phiFIL_a*.07;
  phiGLOBAL_rad=phiGLOBAL/360*(2*3.141592654);
  thetaGLOBAL_rad=thetaGLOBAL/360*(2*3.141592654);
  
  // Calculating complementary filtered final values: yaw from accelerometer, gyroscope and magnetometer
  yawX=odczyt[6]*cos(thetaGLOBAL_rad)-odczyt[7]*sin(phiGLOBAL_rad)*sin(thetaGLOBAL_rad)+odczyt[8]*cos(phiGLOBAL_rad)*sin(thetaGLOBAL_rad);
  yawY=odczyt[7]*cos(phiGLOBAL_rad)+odczyt[8]*sin(phiGLOBAL_rad);
  psiGLOBAL_rad=atan2(yawY,yawX)/(2*3.141592654)*360;

  // phi = roll (around X axis)
  eulerAngles[0]=phiGLOBAL_rad;

  // theta = pitch (around Y axis)
  eulerAngles[1]=thetaGLOBAL_rad;

  // psi = yaw (around Z axis)
  eulerAngles[2]=psiGLOBAL_rad

  // Getting old values for compensated filtering pitch, roll and yaw
  phiFIL_a_old=phiFIL_a;
  thetaFIL_a_old=thetaFIL_a;

}


/* USER CODE END 0 */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
