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

/* USER CODE BEGIN PV */

I2C_HandleTypeDef *hi2cflick = &hi2c1;

SPI_HandleTypeDef *hnucleo_Spi = &hspi2;

int pulse_cnt; //zmienna liczba impulsów

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


void Pulse_Counter(void) //proces do zliczania impulsów
{
	if (pulse_cnt > 0) pulse_cnt--;
	else
	{
		HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_2); //odliczamy ilosć impulsów wygenerowanych w PWM timera 2 (ma przerwanie co jeden impuls)
		__HAL_TIM_SET_COUNTER(&htim2, 2000); //długość cyklu (licznik który określa nam jak długie są impulsy)

		//Można zmienić COUNTER aby było wolniej szybciej (zmienia tylko czas), ale ogólnie tak jak jest to jest spoko

		//zegar to 1000000 impulsów na sekundę (wartość 2000 w ustawieniach timera ma zwiazek z tym co tutaj w funkcji ustawiamy)

		//licznik "ładujemy do 2000 impulsów i liczymy w dół => 2000*1/1000000s = 0,002 s

		//2000 nie ustawione jest bez znaczenia
		//w liczniku ustawiamy też wartosć 1000 i to ma zwiazek z przebiegiem (jak długie i o jakim wypełnieniu impulsy otrzymamy)

	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */


/**
 * Informacje wstępne
 *
 * przełożenie przekładni i=10
 * mikrokroki 1/16
 * na pełen obrót stołu nalezy wykonać 32000 mikrokroków
 */



int main(void)
{
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

	BSP_LCD_DisplayStringAtLine(2, (uint8_t *) "testTestTest");

	BSP_LCD_Clear(LCD_COLOR_YELLOW);

	BSP_LCD_DisplayStringAtLine(3, (uint8_t *) "test");

	/* Sensors */
	HAL_I2C_Init(&hi2c1);
	HAL_I2C_Init(&hi2c2);

	/* Flick */
	flick_reset();
	flick_set_param(0x90, 0x20, 0x20);

	/* IMU */
	uint8_t i2c2_buf[10];
	HAL_I2C_Mem_Read(&hi2c2, ACC_GYRO_ADDR, WHO_AM_I, I2C_MEMADD_SIZE_8BIT, i2c2_buf, 1, 1);
	HAL_I2C_Mem_Read(&hi2c2, 0x1e<<1, 0x0f, I2C_MEMADD_SIZE_8BIT, i2c2_buf+1, 1, 1);

	char str[40];
	sprintf(str, "Who? A/G:%02x M:%02x", i2c2_buf[0], i2c2_buf[1]);
	BSP_LCD_DisplayStringAtLine(10, (uint8_t *) str);

	/* cfg gyro */
	i2c2_buf[0] = 0x38;		// enable X,Y,Z axes
	HAL_I2C_Mem_Write(&hi2c2, ACC_GYRO_ADDR, CTRL10_C, I2C_MEMADD_SIZE_8BIT, i2c2_buf, 1, 1);
	i2c2_buf[0] = 0x14;		// 13 Hz ODR, 500 dps
	HAL_I2C_Mem_Write(&hi2c2, ACC_GYRO_ADDR, CTRL2_G, I2C_MEMADD_SIZE_8BIT, i2c2_buf, 1, 1);

	// cfg acc
	i2c2_buf[0] = 0x38;		// enable X,Y,Z axes
	HAL_I2C_Mem_Write(&hi2c2, ACC_GYRO_ADDR, CTRL9_XL, I2C_MEMADD_SIZE_8BIT, i2c2_buf, 1, 1);
	i2c2_buf[0] = 0x10;		// 13 Hz ODR, +/- 2 g
	HAL_I2C_Mem_Write(&hi2c2, ACC_GYRO_ADDR, CTRL1_XL, I2C_MEMADD_SIZE_8BIT, i2c2_buf, 1, 1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	while (1)
	{
    /* USER CODE END WHILE */


	  /* USER CODE BEGIN 3 */


		uint32_t gesture, touch;
		airwheel_data_t airwheel;
		char str[20];

		flick_poll_data(&gesture, &touch, &airwheel);

		if(airwheel.new_data == FLICK_NEW_DATA)
		{
			BSP_LCD_Clear(LCD_COLOR_YELLOW);
			BSP_LCD_DrawCircle(50, 110, 22);
			BSP_LCD_FillCircle(50, 110, 12);

			sprintf(str, "pos: %02d cnt: %02d", airwheel.position, airwheel.count);
			BSP_LCD_DisplayStringAtLine(4, (uint8_t *) str);

			uint8_t circy = 110 - 12 * sin(2*3.1416*airwheel.position/32);
			uint8_t circx = 50 - 12 * cos(2*3.1416*airwheel.position/32);

			BSP_LCD_FillCircle(circx, circy, 3);

			airwheel.new_data = FLICK_NO_DATA;
		}

		sprintf(str, "g:%lx             ", gesture);
		BSP_LCD_DisplayStringAtLine(1, (uint8_t *) str);
		sprintf(str, "gest:%d           ", (uint8_t) gesture);
		BSP_LCD_DisplayStringAtLine(2, (uint8_t *) str);
		sprintf(str, "t:%lx             ", touch);
		BSP_LCD_DisplayStringAtLine(3, (uint8_t *) str);

		if ((uint8_t) gesture == 2)
			HAL_GPIO_TogglePin(MOT_DIR1_GPIO_Port, MOT_DIR1_Pin); //zmiana kierunku obrotu silnika na przeciwny_MW

		/* IMU */
		HAL_I2C_Mem_Read(&hi2c2, ACC_GYRO_ADDR, STATUS_REG, I2C_MEMADD_SIZE_8BIT, i2c2_buf, 1, 1);
		uint8_t tmp_stat = i2c2_buf[0];
		if (tmp_stat & SR_XLDA)
		{
			HAL_I2C_Mem_Read(&hi2c2, ACC_GYRO_ADDR, OUTX_L_XL, I2C_MEMADD_SIZE_8BIT, i2c2_buf, 6, 1);
			sprintf(str, "acc %+4hi%+4hi%+4hi",
					(int8_t)*(i2c2_buf+1), (int8_t)*(i2c2_buf+3), (int8_t)*(i2c2_buf+5));
			BSP_LCD_DisplayStringAtLine(12, (uint8_t *) str);
		}
		if (tmp_stat & SR_GDA)
		{
			HAL_I2C_Mem_Read(&hi2c2, ACC_GYRO_ADDR, OUTX_L_G, I2C_MEMADD_SIZE_8BIT, i2c2_buf, 6, 1);
			sprintf(str, "gyro %+4hi%+4hi%+4hi",
					(int8_t)*(i2c2_buf+1), (int8_t)*(i2c2_buf+3), (int8_t)*(i2c2_buf+5));
			BSP_LCD_DisplayStringAtLine(11, (uint8_t *) str);
		}

		HAL_Delay(100);

		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
		{
			//		  float cnt = (float)__HAL_TIM_GetCounter(&htim4) / 10;
			//
			//		  uint8_t str[20];
			//		  sprintf((char*)str, "mot %.1f\r", cnt);
			//		  BSP_LCD_DisplayStringAtLine(5, (uint8_t *) str);

			pulse_cnt = 500;	//ilość impulsów o jaki silnik ma się poruszyć (ruch zależy od ustawień stepsticka)_MW
			HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2); //uruchomienie PWM czyli generowania impulsów i my tu nie zostajemy (kroki się wykonują.
			//To jest tylko utuchomienie timera z obsługą przerwania
			//Nie ma potrzeby się tu pokazywać dopóki te kroki się nie wykonają

			//należy zadawać co jakiś czas określoną liczbę kroków i wmiedzy czasie odczytywać inne wartosci (zwolnić moc obliczeniową)


		}









		_Bool tryb = 0; //ogólnie to użytkownik to będzie podawał poprzez GUI
		double kat_start = 30; //ogólnie to użytkownik to będzie podawał poprzez GUI
		double kat_obr = 60; //ogólnie to użytkownik to będzie podawał poprzez GUI
		double czas = 120; //chyba nie będzie potrzebna ta zmienna bo wymagałaby zmiany wartości w liczniku tim2 (będziemy poruszać sie z stałą prędkością)
		double kat_obecny; //dane z funkci IMU
		HAL_GPIO_WritePin(GPIOA, MOT_WARUNEK_OPUSZCZENIA, GPIO_PIN_RESET);




		if(tryb == 0) //Wejście do trybu 0, poruszamy się z kierunka A do kierunku B
		{

			euler();
			kat_obecny = eulerAngles[2] * 180 / 3,14; //odczytanie bieżącego kąta, GUI pobira tą wartość


			while((kat_start - 2) <= kat_obecny && kat_obecny <= (kat_start + 2)) //ustawienie na pozycje startową
			{

				euler();
				kat_obecny = eulerAngles[2] * 180 / 3,14; //odczytanie bieżącego kąta, GUI pobira tą wartość

				if(0 <= (kat_obecny - kat_start))
				{

					HAL_GPIO_WritePin(GPIOA, MOT_DIR1_Pin, GPIO_PIN_SET); //ustawienie obrotów w lewo
					pulse_cnt = (abs(kat_obecny - kat_start)) * 32000 / 360; //2000
					HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2);

				}
				if(0 >= (kat_obecny - kat_start))
				{
					HAL_GPIO_WritePin(GPIOA, MOT_DIR1_Pin, GPIO_PIN_RESET); //ustawienie obrotów w prawo
					pulse_cnt = (abs(kat_obecny - kat_start)) * 32000 / 360;
					HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2);
				}


			}

			while((kat_start + kat_obr - 1) <= kat_obecny && kat_obecny <= (kat_start + kat_obr + 1)) //przemieszczanie sie z kierunku A na kierunek B
			{

				euler();
				kat_obecny = eulerAngles[2] * 180 / 3,14; //odczytanie bieżącego kąta, GUI pobira tą wartość

				if(kat_start <= (kat_start + kat_obr))
				{
					HAL_GPIO_WritePin(GPIOA, MOT_DIR1_Pin, GPIO_PIN_SET); //ustawienie obrotów w lewo
					pulse_cnt = (abs(kat_obr)) * 32000 / 360;
					HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2);
				}

				if(kat_start <= (kat_start + kat_obr))
				{
					HAL_GPIO_WritePin(GPIOA, MOT_DIR1_Pin, GPIO_PIN_RESET); //ustawienie obrotów w prawo
					pulse_cnt = (abs(kat_obr)) * 32000 / 360;
					HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2);
				}


			}

		}


		if(tryb == 1)
		{
			while(MOT_WARUNEK_OPUSZCZENIA == 1) //podążanie za pozycją startową z stałą prędkością
			{

				euler();
				kat_obecny = eulerAngles[2] * 180 / 3,14; //odczytanie bieżącego kąta, GUI pobira tą wartość

				if(0 <= kat_obecny - kat_start)
				{
					HAL_GPIO_WritePin(GPIOA, MOT_DIR1_Pin, GPIO_PIN_SET); //ustawienie obrotów w lewo
					pulse_cnt = (abs(kat_obecny - kat_start)) * 32000 / 360;
					HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2);
					//dodać sprawdzenie czy użytkownik nie chce opuścić trybu 1
				}
				if(0 >= kat_obecny - kat_start)
				{
					HAL_GPIO_WritePin(GPIOA, MOT_DIR1_Pin, GPIO_PIN_RESET); //ustawienie obrotów w prawo
					pulse_cnt = (abs(kat_obecny - kat_start)) * 32000 / 360;
					HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2);
					//dodać sprawdzenie czy użytkownik nie chce opuścić trybu 1
				}

//				if(sprawdzenie czy opuścić funkcje od flicka)
//				{
//					HAL_GPIO_WritePin(GPIOA, MOT_WARUNEK_OPUSZCZENIA, GPIO_PIN_SET);
//				}


			}

		}





  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_I2C2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

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
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
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
static void MX_I2C2_Init(void)
{

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
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
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
static void MX_SPI2_Init(void)
{

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
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
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
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 80;
  htim2.Init.CounterMode = TIM_COUNTERMODE_DOWN;
  htim2.Init.Period = 2000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 1000;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
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
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 8000;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_GATED;
  sSlaveConfig.InputTrigger = TIM_TS_TI2FP2;
  sSlaveConfig.TriggerPolarity = TIM_TRIGGERPOLARITY_FALLING;
  sSlaveConfig.TriggerFilter = 15;
  if (HAL_TIM_SlaveConfigSynchro(&htim4, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_ENABLE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
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
static void MX_USART2_UART_Init(void)
{

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
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
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
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LCD_DC_Pin|LCD_RST_Pin|LCD_CS_Pin|FLICK_TS_Pin
                          |FLICK_RESET_Pin|MOT_REF_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|MOT_DIR1_Pin|MOT_RESET_Pin|MOT_WARUNEK_OPUSZCZENIA_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, MOT_MODE1_Pin|MOT_MODE2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_DC_Pin LCD_CS_Pin */
  GPIO_InitStruct.Pin = LCD_DC_Pin|LCD_CS_Pin;
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

  /*Configure GPIO pins : LD2_Pin MOT_DIR1_Pin MOT_RESET_Pin MOT_WARUNEK_OPUSZCZENIA_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|MOT_DIR1_Pin|MOT_RESET_Pin|MOT_WARUNEK_OPUSZCZENIA_Pin;
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
  GPIO_InitStruct.Pin = FLICK_RESET_Pin|MOT_REF_Pin;
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
  GPIO_InitStruct.Pin = MOT_MODE1_Pin|MOT_MODE2_Pin;
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
void Error_Handler(void)
{
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
