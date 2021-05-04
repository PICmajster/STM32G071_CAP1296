/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

File    : interrupt_manager.c
Autor   : strefapic.blogspot.com
MCU     : STM32G071KBT6

*/

#include <stm32g071xx.h>
#include "interrupt_manager.h"

void INTERRUPT_MANAGER_Initialize(void){
/* EXTI interrupt init*/
 NVIC_SetPriority(EXTI0_1_IRQn, 0);
 NVIC_EnableIRQ(EXTI0_1_IRQn);

}