#ifndef IMU_H
#define IMU_H

#include "stm32l4xx_hal.h"
#include "string.h"
#include "lsm6ds33_reg.h"
#include "lis3_reg.h"
#include "math.h"

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

/**
 * \brief inicjalizacja czujnika IMU
 *
 * funkcja inicjalizująca działanie czujnika. ustawienie odpowiednich adresow i dokładności odczytu dla akcelerometru, magnetometru i żyroskopu.
 *  \param hi2c2 - handle do i2c
 * \author Karol Zalewski i Łukasz Nowicki
 */
void init_IMU(I2C_HandleTypeDef hi2c2);

/**
 * \brief wczytywanie zmiennych IMU
 *
 * funkcja ma na celu wczytanie wszystkich 9 wartosci z żyroskopu, magnetometru i akcelerometru. Nastepnie wartosci
 przeliczane są na odpowiedni zakres i wstawiane są do tablicy IMU_raw.
 * \param IMU_raw - wskaźnik na tablice gdzie przechwywane są przeskalowane wartosci z czujnika
 * \param hi2c2 - handle do i2c
 * \author Karol Zalewski i Łukasz Nowicki
 */
void wczytywanie_IMU(float *IMU_raw, I2C_HandleTypeDef hi2c2);

/**
 * \brief Obliczenie kątów Eulera
 *
 *  Wpisane wartości kątów Eulera do tablicy globalnej eulerAngels
 *  \param IMU_raw - wskaźnik na tablice gdzie przechwywane są przeskalowane wartosci z czujnika
 *  \param  eulerAngles - wskaźnik na tablice gdzie przechowywane są wartości kątów Eulera.
 *  \author Filip Budny
 */
void Euler(float *IMU_raw, int8_t *eulerAngles);

#endif /* IMU_H */
