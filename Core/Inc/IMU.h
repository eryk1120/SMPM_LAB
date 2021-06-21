#ifndef IMU_H
#define IMU_H

#include "stm32l4xx_hal.h"
#include "string.h"
#include "lsm6ds33_reg.h"
#include "lis3_reg.h"
#include "math.h"

// Floats for raw values: pitch, theta gathered only from acceleroemter
float phiRAW_a; /**< Float for raw pitch/phi value gathered only from acceleroemter */
float thetaRAW_a; /**< Float for raw roll/theta value gathered only from acceleroemter */

// Floats for filtered values: pitch, theta gathered only from acceleroemter
float phiFIL_a; /**<  Float for low-pass filtered pitch/phi gathered only from acceleroemter */
float phiFIL_a_old;  /**< Float used for low-pass filtering pitch/phi gathered only from acceleroemter */
float thetaFIL_a;  /**< Float for low-pass filtered roll/theta gathered only from acceleroemter */
float thetaFIL_a_old;  /**< Float used for low-pass filtering roll/theta gathered only from acceleroemter  */

// Floats for raw values: pitch, theta gathered only from gyroscope
float phiRAW_g;  /**< Float for raw pitch/phi value gathered only from gyroscope */
float thetaRAW_g; /**< Float for raw roll/theta value gathered only from gyroscope */
float uwTickOld;  /**< Float for time used in complementary filtering pitch/phi and roll/theta value gathered from accelerometer and gyroscope */

// Floats for compensated final values: pitch, theta gathered from accelerometer and gyroscope
float phiGLOBAL;  /**< Float for complementary filtered final pitch/phi gathered from accelerometer and gyroscope in degrees per second */
float phiGLOBAL_rad;  /**< Float for complementary filtered final pitch/phi gathered from accelerometer and gyroscope in radians per second */
float thetaGLOBAL;  /**< Float for complementary filtered final roll/theta gathered from accelerometer and gyroscope in degrees per second */
float thetaGLOBAL_rad;  /**< Float for complementary filtered final roll/theta gathered from accelerometer and gyroscope in radians per second */

// Floats for compensated final values: yaw gathered from accelerometer, gyroscope and magnetometer
float yawX;  /**<  Float used for calculating tilt compensated yaw/psi gathered from accelerometer, gyroscope and magnetometer  */
float yawY;  /**< Float used for calculating tilt compensated yaw/psi gathered from accelerometer, gyroscope and magnetometer */
float psiGLOBAL_rad;  /**< Float for tilt compensated final yaw/psi gathered from accelerometer and gyroscope in radians per second */

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
