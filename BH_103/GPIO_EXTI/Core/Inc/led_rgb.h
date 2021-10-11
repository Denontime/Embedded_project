/**
  ******************************************************************************
  * @file    led_rgb.h
  * @brief   This file contains all the function prototypes for
  *          the led_rgb.c file
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _LED_RGB_H
#define _LED_RGB_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
typedef enum
{
  LED_RED           = 1,
  LED_GREEN         = 2,
  LED_BLUE          = 3,
  LED_YELLOW        = 4,
  LED_PURPLE        = 5,
  LED_CYAN          = 6,
  LED_WHITE         = 7
} LED_Color_TypeDef;

extern LED_Color_TypeDef Led_Color;

/* USER CODE END Private defines */

void Led_On(GPIO_TypeDef* GPIOx,uint16_t Led_Pin);
void Led_Off(GPIO_TypeDef* GPIOx,uint16_t Led_Pin);
void Led_All_Off(void);
void Led_Toggle(GPIO_TypeDef* GPIOx,uint16_t Led_Pin);
void Led_Set(GPIO_TypeDef* GPIOx,uint16_t Led_Pin);
uint16_t Led_SetColor(LED_Color_TypeDef Led_Color);
uint16_t Led_Next_Color(void);
uint16_t Led_Prev_Color(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
