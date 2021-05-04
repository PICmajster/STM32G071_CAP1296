/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

File    : clock_manager.c
Autor   : strefapic.blogspot.com
MCU     : STM32G071KBT6

*/

#include <stm32g071xx.h>
#include "clock_manager.h"

void CLOCK_MANAGER_Initialize(void){

RCC->IOPENR |= RCC_IOPENR_GPIOAEN; //Open clock for GPIOA
RCC->IOPENR |= RCC_IOPENR_GPIOBEN; //Open clock for GPIOB

RCC->APBENR1 |= RCC_APBENR1_I2C2EN ; //Open clock for I2C2



}