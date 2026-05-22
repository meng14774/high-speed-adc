/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : signal_process.c
  * @brief          : This file provides code for signal processing.
  *                   Zero-crossing based frequency analysis and signal statistics.
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

/* Includes ------------------------------------------------------------------*/
#include "signal_process.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

SignalAnalysisResult Analyze_Signal_ZC(uint16_t *buffer, uint32_t size, float sampling_rate_hz, float vref)
{
  SignalAnalysisResult result = {0};
  uint32_t i;
  uint16_t adc_min = 4095;
  uint16_t adc_max = 0;
  uint32_t sum = 0;

  for(i = 0; i < size; i++)
  {
    if(buffer[i] < adc_min) adc_min = buffer[i];
    if(buffer[i] > adc_max) adc_max = buffer[i];
    sum += buffer[i];
  }

  result.vmin = (float)adc_min * vref / 4095.0f;
  result.vmax = (float)adc_max * vref / 4095.0f;
  result.vpp = result.vmax - result.vmin;

  float threshold = (float)sum / size;
  result.threshold = threshold * vref / 4095.0f;

  int32_t last_crossing_idx = -1;
  int32_t first_crossing_idx = -1;
  float crossing_intervals[256];
  uint16_t crossing_count = 0;

  for(i = 1; i < size; i++)
  {
    int16_t prev_sample = (int16_t)buffer[i-1] - (int16_t)threshold;
    int16_t curr_sample = (int16_t)buffer[i] - (int16_t)threshold;

    if(prev_sample < 0 && curr_sample >= 0)
    {
      if(first_crossing_idx == -1)
        first_crossing_idx = i;

      if(last_crossing_idx != -1 && crossing_count < 256)
      {
        crossing_intervals[crossing_count++] = (float)(i - last_crossing_idx) / sampling_rate_hz;
      }
      last_crossing_idx = i;
    }
  }

  result.zero_crossings = crossing_count;

  if(crossing_count > 0)
  {
    float avg_period = 0;
    for(i = 0; i < crossing_count; i++)
    {
      avg_period += crossing_intervals[i];
    }
    avg_period /= crossing_count;

    if(avg_period > 0)
      result.frequency = 1.0f / avg_period;
  }

  return result;
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
