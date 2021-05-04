/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

File    : pin_manager.c
Autor   : strefapic.blogspot.com
MCU     : STM32G071KBT6

*/

#include <stm32g071xx.h>
#include "pin_manager.h"

void PIN_MANAGER_Initialize(void){

/********** PA11 and PA12 set for I2C2*****************/
/*set Alternate fuction mode (0b10)*/
GPIOA->MODER |= (GPIO_MODER_MODE11_1 | GPIO_MODER_MODE12_1); 
GPIOA->MODER &= ~(GPIO_MODER_MODE11_0 | GPIO_MODER_MODE12_0); 
/*set Open Drain*/
GPIOA->OTYPER |= (GPIO_OTYPER_OT11 | GPIO_OTYPER_OT12) ;
/*set Pull-Up (0b01)*/
GPIOA->PUPDR |= (GPIO_PUPDR_PUPD11_0 | GPIO_PUPDR_PUPD12_0) ;
GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD11_1 | GPIO_PUPDR_PUPD12_1);
/*set low speed (0b01)*/
GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED11_0 | GPIO_OSPEEDR_OSPEED12_0) ;
GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED11_1 | GPIO_OSPEEDR_OSPEED12_1) ;
/*set for I2C (0b0110)*/
GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL11 | GPIO_AFRH_AFSEL12) ; // clear
GPIOA->AFR[1] |= (GPIO_AFRH_AFSEL11_1 | GPIO_AFRH_AFSEL11_2) ; //set
GPIOA->AFR[1] |= (GPIO_AFRH_AFSEL12_1 | GPIO_AFRH_AFSEL12_2) ; //set

/********** PA8 set Out for LED **********************/
GPIOA->MODER &= ~GPIO_MODER_MODE8_1 ;  //MODE8 -> 0b01

/********** PB1 set for EXTI ************/
/*set Input (0b00)*/
GPIOB->MODER &= ~(GPIO_MODER_MODE1_0 | GPIO_MODER_MODE1_1); 
/*set low speed (0b01)*/
GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED1_0 ;
GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED1_1 ;
/*set Pull-Up (0b01)*/
GPIOB->PUPDR |= GPIO_PUPDR_PUPD1_0 ;
GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD1_1;
/*set EXTI for PB1*/
EXTI->EXTICR[0] |= EXTI_EXTICR1_EXTI1_0 ;
/*set EXTI Falling triger for PB1*/
EXTI->FTSR1 |= EXTI_FTSR1_FT1 ;
/*set EXTI Interrupt no-masked for PB1*/
EXTI->IMR1 |= EXTI_IMR1_IM1 ;
}