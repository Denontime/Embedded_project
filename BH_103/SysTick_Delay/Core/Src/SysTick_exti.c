/**
  ******************************************************************************
  * @file    SysTick_exti.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "SysTick_exti.h"

uint8_t SysTick_Interrupt_Flag = 0;
int led_delay_ms = 1000;

void HAL_SYSTICK_Callback(void)
{
    SysTick_Interrupt_Flag = 1; // �����жϺ��жϱ�־��1
    LED_Blink();
}


