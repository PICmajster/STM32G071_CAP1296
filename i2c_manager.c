/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

File    : i2c_manager.c
Autor   : strefapic.blogspot.com
MCU     : STM32G071KBT6

*/

#include <stm32g071xx.h>
#include "i2c_manager.h"

void I2C2_MANAGER_Initialize(void){

I2C2->CR1 &= ~I2C_CR1_PE ; //I2C2 OFF
asm("nop");
I2C2->CR1 |= I2C_CR1_ANFOFF ; //Analog filter ON
I2C2->TIMINGR = 0x00303D5B ; //get from STM32Cube, FCY - 16MHz
I2C2->CR1 |= I2C_CR1_TCIE; //Transfer Complete interrupt enable TCIE = 1
I2C2->CR1 |= I2C_CR1_TXIE; // Transmit (TXIS) interrupt enabled TXIE = 1
I2C2->CR1 |= I2C_CR1_RXIE; // Receive (RXNE) interrupt enabled RXIE = 1
I2C2->CR1 |= I2C_CR1_STOPIE; // STOP (STOPF) interrupt enabled STOPIE = 1
I2C2->CR1 |= I2C_CR1_PE ; //I2C2 ON
asm("nop");
}