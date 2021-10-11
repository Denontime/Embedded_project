/**
  ******************************************************************************
  * @file    exti.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "exti.h"

/* USER CODE BEGIN 0 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch(GPIO_Pin)
  {
    case KEY1_Pin: Led_Set(LED_GPIO_Port,Led_Next_Color()); break;
    case KEY2_Pin: Led_Set(LED_GPIO_Port,Led_Prev_Color()); break;
    default: break;
  }
}
/* USER CODE END 0 */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
