/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : signal_process.h
  * @brief          : Header for signal_process.c file.
  *                   This file contains the signal processing functions.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SIGNAL_PROCESS_H__
#define __SIGNAL_PROCESS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

typedef struct {
  float frequency;
  float vpp;
  float threshold;
  float vmin;
  float vmax;
  uint16_t zero_crossings;
} SignalAnalysisResult;

SignalAnalysisResult Analyze_Signal_ZC(uint16_t *buffer, uint32_t size, float sampling_rate_hz, float vref);

#ifdef __cplusplus
}
#endif

#endif /* __SIGNAL_PROCESS_H__ */
