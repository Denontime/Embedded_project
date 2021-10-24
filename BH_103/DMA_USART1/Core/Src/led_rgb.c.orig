/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "led_rgb.h"

int Led_Color = 0;

void Led_On(GPIO_TypeDef* GPIOx,uint16_t Led_Pin)
{
    HAL_GPIO_WritePin(GPIOx, Led_Pin,GPIO_PIN_RESET);
}

void Led_Off(GPIO_TypeDef* GPIOx,uint16_t Led_Pin)
{
    HAL_GPIO_WritePin(GPIOx, Led_Pin,GPIO_PIN_SET);
}

void Led_All_Off()
{
    HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_R_Pin|LED_G_Pin|LED_B_Pin,GPIO_PIN_SET);
}

void Led_Toggle(GPIO_TypeDef* GPIOx,uint16_t Led_Pin)
{
    HAL_GPIO_TogglePin(GPIOx,Led_Pin);  // HAL_GPIO_TogglePin 电平翻转函数
}

void Led_Set(GPIO_TypeDef* GPIOx,uint16_t Led_Pin)
    {
    HAL_GPIO_WritePin(GPIOx, LED_R_Pin|LED_G_Pin|LED_B_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOx, Led_Pin,GPIO_PIN_RESET);
}

uint16_t Led_SetColor(int led_color)
{
    uint16_t Color = 0x00;
    switch(led_color)
    {
        case 1:
            Color = LED_R_Pin;
            break;
        case 2:
            Color = LED_G_Pin;
            break;
        case 3:
            Color = LED_B_Pin;
            break;
        case 4:
            Color = LED_R_Pin|LED_G_Pin;
            break;
        case 5:
            Color = LED_R_Pin|LED_B_Pin;
            break;
        case 6:
            Color = LED_G_Pin|LED_B_Pin;
            break;
        case 7:
            Color = LED_R_Pin|LED_G_Pin|LED_B_Pin;
            break;
        default:
            Color = LED_R_Pin|LED_G_Pin|LED_B_Pin;
            break;
    }
    return Color;
    
}

uint16_t Led_Next_Color()
{
    Led_Color++;
    if(Led_Color > LED_WHITE) Led_Color = LED_RED;
    return Led_SetColor(Led_Color);
}

uint16_t Led_Prev_Color()
{
    Led_Color--;
	if(Led_Color < LED_RED) Led_Color = LED_WHITE;
	return Led_SetColor(Led_Color);
}
