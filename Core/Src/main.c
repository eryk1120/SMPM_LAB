/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
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
#include "main.h"

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
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart2;

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
int8_t eulerAngles[3] = { 0 };

//dane XYZ z IMU: acc 0-2, gyr 3-5, mag 6-8; jednostki: [m/s^2], [dps], [Gs]
float IMU_raw[9] = { 0 };

/* USER CODE BEGIN PV */

I2C_HandleTypeDef *hi2cflick = &hi2c1;

SPI_HandleTypeDef *hnucleo_Spi = &hspi2;

int pulse_cnt;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM2_Init(void);
static void MX_SPI2_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void Pulse_Counter(void) {
	if (pulse_cnt > 0)
		pulse_cnt--;
	else {
		HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_2);
		__HAL_TIM_SET_COUNTER(&htim2, 2000);
	}
}
/**  
* \brief inicjalizacja czujnika IMU
*
* funkcja inicjalizująca działanie czujnika. ustawienie odpowiednich adresow i dokładności odczytu dla akcelerometru, magnetometru i żyroskopu. 
* \author Karol Zalewski i Łukasz Nowicki
 */
void init_IMU() {
	uint8_t i2c2_buf[10]; /*!< T tablica buforów do których są wczytywane dane z kolejnych wybranych rejestrów czujnika */
	HAL_I2C_Mem_Read(&hi2c2, ACC_GYRO_ADDR, WHO_AM_I, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1); /** konfiguracja odczytu po magistrali I2C */
	HAL_I2C_Mem_Read(&hi2c2, 0x1e << 1, 0x0f, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf + 1, 1, 1); /** konfiguracja odczytu po magistrali I2C */

	char str[40];
	sprintf(str, "Who? A/G:%02x M:%02x", i2c2_buf[0], i2c2_buf[1]);
	BSP_LCD_DisplayStringAtLine(10, (uint8_t*) str);

	/** konfiguracja żyroskopu */
	i2c2_buf[0] = 0x38;		/** uruchomienie odczytu kątów X,Y,Z */
	HAL_I2C_Mem_Write(&hi2c2, ACC_GYRO_ADDR, CTRL10_C, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1);

	i2c2_buf[0] = 0x14;		/** ustawienie częstotliwości i zakresu: 13 Hz ODR, 500 dps */
	HAL_I2C_Mem_Write(&hi2c2, ACC_GYRO_ADDR, CTRL2_G, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1);

	/** konfiguracja akcelerometru */ 
	i2c2_buf[0] = 0x38;		/** uruchomienie odczytu kątów X,Y,Z */
	HAL_I2C_Mem_Write(&hi2c2, ACC_GYRO_ADDR, CTRL9_XL, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1);

	i2c2_buf[0] = 0x10;		/** ustawienie częstotliwości i zakresu: 13 Hz ODR, +/- 2 g */
	HAL_I2C_Mem_Write(&hi2c2, ACC_GYRO_ADDR, CTRL1_XL, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1);

	/** konfiguracja magnetometru */
	i2c2_buf[0] = 0xE0;     //11100000,  /** uruchomienie generowania przerwań X,Y,Z */
	HAL_I2C_Mem_Write(&hi2c2, MAG_ADDR, INT_CFG, I2C_MEMADD_SIZE_8BIT, i2c2_buf,
			1, 1);

	i2c2_buf[0] = 0x70; /**   01110000, ustawienie czestotliwosci 10 Hz, i trybu  High-power mode, brak odczytu temperatury, self test wyłączony */
	HAL_I2C_Mem_Write(&hi2c2, MAG_ADDR, CTRL_REG1, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1);

	i2c2_buf[0] = 0x00;         /** 00000000 ustawienie zakresu pomiarowego +-4 gauss */
	HAL_I2C_Mem_Write(&hi2c2, MAG_ADDR, CTRL_REG2, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1);

	i2c2_buf[0] = 0x00;   /*00000000 ustawienie trybu Low-power mode, oraz Continuous-conversion mode */
	HAL_I2C_Mem_Write(&hi2c2, MAG_ADDR, CTRL_REG3, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1);
**/
}
/**  
* \brief wczytywanie zmiennych IMU
*
* funkcja ma na celu wczytanie wszystkich 9 wartosci z żyroskopu, magnetometru i akcelerometru. Nastepnie wartosci
przeliczane są na odpowiedni zakres.
* \author Karol Zalewski i Łukasz Nowicki
*/   
void wczytywanie_IMU() {

	int16_t odczyt[9] = { 0 }; 	/*tablica z odczytywanymi zmiennymi */
	char str[40];
	uint8_t i2c2_buf[10]; tablica buforów do których są wczytywane dane z kolejnych wybranych rejestrów czujnika */
	uint16_t pom; /** zmienna pomocnicza 16 bitowa typu int */

	HAL_I2C_Mem_Read(&hi2c2, ACC_GYRO_ADDR, STATUS_REG, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf, 1, 1);
	uint8_t tmp_stat_acc = i2c2_buf[0];

	if (tmp_stat_acc & SR_XLDA) /** dostępne nowe dane z akcelerometru */
	{
		HAL_I2C_Mem_Read(&hi2c2, ACC_GYRO_ADDR, OUTX_L_XL, I2C_MEMADD_SIZE_8BIT,
				i2c2_buf, 6, 1); /** odczytwartosci z czujnika */
		/* dodanie bajtu starszego z mlodszym, starszy bajt przesuwam o 8 bitów w lewo, */
		pom = i2c2_buf[1] << 8;
		odczyt[0] = i2c2_buf[0] + pom;
		pom = i2c2_buf[3] << 8;
		odczyt[1] = i2c2_buf[2] + pom;
		pom = i2c2_buf[5] << 8;
		odczyt[2] = i2c2_buf[4] + pom;

		//	  sprintf(str, "acc %+4hi%+4hi%+4hi",
		//			  (int16_t)*(odczyt + 1), (int16_t)*(odczyt + 2), (int16_t)*(odczyt + 3));
		//	 BSP_LCD_DisplayStringAtLine(12, (uint16_t *) str);
	}

	if (tmp_stat_acc & SR_GDA) /** dostępne nowe dane gyroscope */
	{
		HAL_I2C_Mem_Read(&hi2c2, ACC_GYRO_ADDR, OUTX_L_G, I2C_MEMADD_SIZE_8BIT,
				i2c2_buf, 6, 1); /** odczytwartosci z czujnika */
		/** polaczenie bajtu starszego z mlodszym, starszy bajt przesuwam o 8 bitów lewo, dodaje bajty */
		pom = i2c2_buf[1] << 8;
		odczyt[3] = i2c2_buf[0] + pom;
		pom = i2c2_buf[3] << 8;
		odczyt[4] = i2c2_buf[2] + pom;
		pom = i2c2_buf[5] << 8;
		odczyt[5] = i2c2_buf[4] + pom;

		//	  sprintf(str, "acc %+4hi%+4hi%+4hi",
		//			  (int16_t)*(odczyt + 4), (int16_t)*(odczyt + 5), (int16_t)*(odczyt + 6));
		//	 BSP_LCD_DisplayStringAtLine(12, (uint16_t *) str);
	}

	HAL_I2C_Mem_Read(&hi2c2, MAG_ADDR, STATUS_REG_mag, I2C_MEMADD_SIZE_8BIT,
			i2c2_buf + 1, 1, 1);
	uint8_t tmp_stat_mag = i2c2_buf[1];

	if (tmp_stat_mag & SR_ZYXDA) /** dostępne nowe dane magnetometr */
	{
		HAL_I2C_Mem_Read(&hi2c2, MAG_ADDR, OUT_X_L, I2C_MEMADD_SIZE_8BIT,
				i2c2_buf, 6, 1); //odczytwartosci z czujnika
		/** polaczenie bajtu starszego z mlodszym, starszy bajt przesuwam o 8 bitów lewo, dodaje bajty */
		pom = i2c2_buf[1] << 8;
		odczyt[6] = i2c2_buf[0] + pom;
		pom = i2c2_buf[3] << 8;
		odczyt[7] = i2c2_buf[2] + pom;
		pom = i2c2_buf[5] << 8;
		odczyt[8] = i2c2_buf[4] + pom;

		//	  sprintf(str, "acc %+4hi%+4hi%+4hi",
		//			  (int16_t)*(odczyt + 7), (int16_t)*(odczyt + 8), (int16_t)*(odczyt + 9));
		//	 BSP_LCD_DisplayStringAtLine(12, (uint16_t *) str);
	}

	/**zamiana jednostek z int16_t na odpowiednie jednostki fizyczne
	acc dla zakresu +-2g, wynikw [m/s^2]
	*/
	IMU_raw[0] = (float) odczyt[0] * 2 * 9.81 / 32768;
	IMU_raw[1] = (float) odczyt[1] * 2 * 9.81 / 32768;
	IMU_raw[2] = (float) odczyt[2] * 2 * 9.81 / 32768;

	/** gyro dla zakresu 500dps, [degress per second] */
	IMU_raw[3] = (float) odczyt[3] * 500 / 32768;
	IMU_raw[4] = (float) odczyt[4] * 500 / 32768;
	IMU_raw[5] = (float) odczyt[5] * 500 / 32768;

	/** magnetometr dla zakresu +-4Gs, wynikw [Gs] */
	IMU_raw[6] = (float) odczyt[6] * 4 / 32768;
	IMU_raw[7] = (float) odczyt[7] * 4 / 32768;
	IMU_raw[8] = (float) odczyt[8] * 4 / 32768;

	//	  sprintf(str, "acc %+4hi%+4hi%+4hi",
	//			  (float)*(IMU_raw + 1), (float)*(IMU_raw + 2), (float)*(IMU_raw + 3));
	//	  sprintf(str, "acc %+4hi%+4hi%+4hi",
	//			  (float)*(IMU_raw + 4), (float)*(IMU_raw + 5), (float)*(IMU_raw + 6));
	//	  sprintf(str, "acc %+4hi%+4hi%+4hi",
	//			  (float)*(IMU_raw + 7), (float)*(IMU_raw + 8), (float)*(IMU_raw + 9));
}
/**
 * \brief Obliczenie kątów Eulera
 *
 *  Wpisane wartości kątów Eulera do tablicy globalnej eulerAngels
 *  \author Filip Budny
 */
void Euler() {

	/** Calculating raw values: pitch, theta gathered only from acceleroemter */
	thetaRAW_a = -atan2(IMU_raw[0] / 9.8, IMU_raw[2] / 9.8) / 2 / 3.141592654
			* 360;
	phiRAW_a = -atan2(IMU_raw[1] / 9.8, IMU_raw[2] / 9.8) / 2 / 3.141592654
			* 360;

	/** Calculating low-pass filtered values: pitch, theta gathered only from acceleroemter */
	phiFIL_a = .93 * phiFIL_a_old + .07 * phiRAW_a;
	thetaFIL_a = .93 * thetaFIL_a_old + .07 * thetaRAW_a;

	/** Timer values for calculating raw values: pitch, theta gathered only from gyroscope */
	uwTick = (uwTick - uwTickOld);
	uwTickOld = uwTick;

	/** Calculating raw values: pitch, theta gathered only from gyroscope */
	thetaRAW_g = thetaRAW_g + IMU_raw[4] * uwTick;
	phiRAW_g = phiRAW_g - IMU_raw[3] * uwTick;

	/** Calculating complementary filtred final values: pitch, theta gatheredfrom accelerometer and gyroscope */
	thetaGLOBAL = (thetaGLOBAL + IMU_raw[4] * uwTick) * .93 + thetaFIL_a * .07;
	phiGLOBAL = (phiGLOBAL - IMU_raw[3] * uwTick) * .93 + phiFIL_a * .07;
	phiGLOBAL_rad = phiGLOBAL / 360 * (2 * 3.141592654);
	thetaGLOBAL_rad = thetaGLOBAL / 360 * (2 * 3.141592654);

	/* Calculating complementary filtered final values: yaw from accelerometer, gyroscope and magnetometer */
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

	/** Getting old values for compensated filtering pitch, roll and yaw */
	phiFIL_a_old = phiFIL_a;
	thetaFIL_a_old = thetaFIL_a;

}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	MX_TIM4_Init();
	MX_TIM2_Init();
	MX_SPI2_Init();
	MX_I2C1_Init();
	MX_I2C2_Init();
	/* USER CODE BEGIN 2 */

	/* Stepstick */
	HAL_TIM_Base_Start(&htim4);

	HAL_GPIO_WritePin(MOT_RESET_GPIO_Port, MOT_RESET_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOT_MODE1_GPIO_Port, MOT_MODE1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOT_MODE2_GPIO_Port, MOT_MODE2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOT_RESET_GPIO_Port, MOT_RESET_Pin, GPIO_PIN_SET);

	/* LCD */
	BSP_LCD_Init();
	BSP_LCD_DisplayOn();

	BSP_LCD_DisplayStringAtLine(2, (uint8_t*) "testTestTest");

	BSP_LCD_Clear(LCD_COLOR_YELLOW);

	BSP_LCD_DisplayStringAtLine(3, (uint8_t*) "test");

	/* Sensors */
	HAL_I2C_Init(&hi2c1);
	HAL_I2C_Init(&hi2c2);

	/* Flick */
	flick_reset();
	flick_set_param(0x90, 0x20, 0x20);

	/* IMU */
	init_IMU();

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

		uint32_t gesture, touch;
		airwheel_data_t airwheel;
		char str[20];

		flick_poll_data(&gesture, &touch, &airwheel);

		if (airwheel.new_data == FLICK_NEW_DATA) {
			BSP_LCD_Clear(LCD_COLOR_YELLOW);
			BSP_LCD_DrawCircle(50, 110, 22);
			BSP_LCD_FillCircle(50, 110, 12);

			sprintf(str, "pos: %02d cnt: %02d", airwheel.position,
					airwheel.count);
			BSP_LCD_DisplayStringAtLine(4, (uint8_t*) str);

			uint8_t circy = 110 - 12 * sin(2 * 3.1416 * airwheel.position / 32);
			uint8_t circx = 50 - 12 * cos(2 * 3.1416 * airwheel.position / 32);

			BSP_LCD_FillCircle(circx, circy, 3);

			airwheel.new_data = FLICK_NO_DATA;
		}

		sprintf(str, "g:%lx             ", gesture);
		BSP_LCD_DisplayStringAtLine(1, (uint8_t*) str);
		sprintf(str, "gest:%d           ", (uint8_t) gesture);
		BSP_LCD_DisplayStringAtLine(2, (uint8_t*) str);
		sprintf(str, "t:%lx             ", touch);
		BSP_LCD_DisplayStringAtLine(3, (uint8_t*) str);

		if ((uint8_t) gesture == 2)
			HAL_GPIO_TogglePin(MOT_DIR1_GPIO_Port, MOT_DIR1_Pin);

		/* IMU */
		wczytywanie_IMU();
		Euler();

	//	sprintf(str, "euler %+4hi%+4hi%+4hi", (int8_t) *(eulerAngles + 1),
	//			(int8_t) *(eulerAngles + 2), (int8_t) *(eulerAngles + 3));

	}

	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 10;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2
			| RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_I2C2;
	PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
	PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
	PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		Error_Handler();
	}
	/** Configure the main internal regulator output voltage
	 */
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1)
			!= HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief I2C1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C1_Init(void) {

	/* USER CODE BEGIN I2C1_Init 0 */

	/* USER CODE END I2C1_Init 0 */

	/* USER CODE BEGIN I2C1_Init 1 */

	/* USER CODE END I2C1_Init 1 */
	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0x00702991;
	hi2c1.Init.OwnAddress1 = 132;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
		Error_Handler();
	}
	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE)
			!= HAL_OK) {
		Error_Handler();
	}
	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN I2C1_Init 2 */

	/* USER CODE END I2C1_Init 2 */

}

/**
 * @brief I2C2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C2_Init(void) {

	/* USER CODE BEGIN I2C2_Init 0 */

	/* USER CODE END I2C2_Init 0 */

	/* USER CODE BEGIN I2C2_Init 1 */

	/* USER CODE END I2C2_Init 1 */
	hi2c2.Instance = I2C2;
	hi2c2.Init.Timing = 0x00702991;
	hi2c2.Init.OwnAddress1 = 0;
	hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c2.Init.OwnAddress2 = 0;
	hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c2) != HAL_OK) {
		Error_Handler();
	}
	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE)
			!= HAL_OK) {
		Error_Handler();
	}
	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN I2C2_Init 2 */

	/* USER CODE END I2C2_Init 2 */

}

/**
 * @brief SPI2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI2_Init(void) {

	/* USER CODE BEGIN SPI2_Init 0 */

	/* USER CODE END SPI2_Init 0 */

	/* USER CODE BEGIN SPI2_Init 1 */

	/* USER CODE END SPI2_Init 1 */
	/* SPI2 parameter configuration*/
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 7;
	hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi2.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
	if (HAL_SPI_Init(&hspi2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI2_Init 2 */

	/* USER CODE END SPI2_Init 2 */

}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void) {

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };
	TIM_OC_InitTypeDef sConfigOC = { 0 };

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 80;
	htim2.Init.CounterMode = TIM_COUNTERMODE_DOWN;
	htim2.Init.Period = 2000;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim2) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 1000;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */
	HAL_TIM_MspPostInit(&htim2);

}

/**
 * @brief TIM4 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM4_Init(void) {

	/* USER CODE BEGIN TIM4_Init 0 */

	/* USER CODE END TIM4_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_SlaveConfigTypeDef sSlaveConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM4_Init 1 */

	/* USER CODE END TIM4_Init 1 */
	htim4.Instance = TIM4;
	htim4.Init.Prescaler = 8000;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = 65535;
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim4) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sSlaveConfig.SlaveMode = TIM_SLAVEMODE_GATED;
	sSlaveConfig.InputTrigger = TIM_TS_TI2FP2;
	sSlaveConfig.TriggerPolarity = TIM_TRIGGERPOLARITY_FALLING;
	sSlaveConfig.TriggerFilter = 15;
	if (HAL_TIM_SlaveConfigSynchro(&htim4, &sSlaveConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_ENABLE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM4_Init 2 */

	/* USER CODE END TIM4_Init 2 */

}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void) {

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */

	/* USER CODE END USART2_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC,
			LCD_DC_Pin | LCD_RST_Pin | LCD_CS_Pin | FLICK_TS_Pin
					| FLICK_RESET_Pin | MOT_REF_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, LD2_Pin | MOT_DIR1_Pin | MOT_RESET_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, MOT_MODE1_Pin | MOT_MODE2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : B1_Pin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : LCD_DC_Pin LCD_CS_Pin */
	GPIO_InitStruct.Pin = LCD_DC_Pin | LCD_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : LCD_RST_Pin */
	GPIO_InitStruct.Pin = LCD_RST_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_RST_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : LD2_Pin MOT_DIR1_Pin MOT_RESET_Pin */
	GPIO_InitStruct.Pin = LD2_Pin | MOT_DIR1_Pin | MOT_RESET_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : FLICK_TS_Pin */
	GPIO_InitStruct.Pin = FLICK_TS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(FLICK_TS_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : FLICK_RESET_Pin MOT_REF_Pin */
	GPIO_InitStruct.Pin = FLICK_RESET_Pin | MOT_REF_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : MOT_FAULT_Pin */
	GPIO_InitStruct.Pin = MOT_FAULT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(MOT_FAULT_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : MOT_MODE1_Pin MOT_MODE2_Pin */
	GPIO_InitStruct.Pin = MOT_MODE1_Pin | MOT_MODE2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
