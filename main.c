/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

File    : main.c
Autor   : strefapic.blogspot.com
MCU     : STM32G071KBT6

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stm32g071xx.h>
#include "cap1296.h"
#include "system_manager.h"

//#define debug

uint8_t I2C2_ReadRegister_CAP1296(uint8_t slaveAdress, uint8_t registerAdress);
void I2C2_WriteRegister_CAP1296(uint8_t slaveAdress, uint8_t registerAdress, uint8_t data);
volatile uint8_t intFlag = 0;

int main(void) {

SystemInit();
SYSTEM_MANAGER_Initialize();

//SysTick_Config(16000000 * 0.5); //ok 0.5 s

I2C2_WriteRegister_CAP1296(CAP1296_ADDR, CAP1296_SENSINPUTENABLE, 0x03);   
I2C2_WriteRegister_CAP1296(CAP1296_ADDR, CAP1296_SENSITIVITY , 0x4F);
I2C2_WriteRegister_CAP1296(CAP1296_ADDR, CAP1296_INTENABLE , 0x03);
I2C2_WriteRegister_CAP1296(CAP1296_ADDR, CAP1296_CALIBRATE, 0x03); 

while(1){

if(intFlag){ //flaga aktywowana w przerwaniu INT0
     
      intFlag = 0; //zeruj flage ustawiana w przerwaniu EXTI0_1
      if(I2C2_ReadRegister_CAP1296(CAP1296_ADDR, CAP1296_SENSTATUS) == 1) GPIOA->ODR |= GPIO_ODR_OD8 ;  //dotyk pierwszego pola wykryty LED ON
      if(I2C2_ReadRegister_CAP1296(CAP1296_ADDR, CAP1296_SENSTATUS) == 2) GPIOA->ODR &= ~GPIO_ODR_OD8 ; //dotyk drugiego pola wykryty LED OFF
            
      I2C2_WriteRegister_CAP1296(CAP1296_ADDR, CAP1296_MAIN, (I2C2_ReadRegister_CAP1296(CAP1296_ADDR, CAP1296_MAIN) & ~CAP1296_MAIN_INT)); //clear main interrupt in CAP1296
                  
     }

}
}


uint8_t I2C2_ReadRegister_CAP1296(uint8_t slaveAdress, uint8_t registerAdress){

uint8_t data ;
while(I2C2->ISR & I2C_ISR_BUSY); //wait for I2C not busy

I2C2->CR2 &= ~I2C_CR2_NBYTES ; //clear NBYTES
I2C2->CR2 |= 1 << I2C_CR2_NBYTES_Pos; //set NBYTES = 1

I2C2->CR2 &= ~I2C_CR2_AUTOEND; //set AUTOEND = 0

I2C2->CR2 &= ~I2C_CR2_SADD; //clear SADD
I2C2->CR2 |= ((uint32_t)(slaveAdress) << I2C_CR2_SADD_Pos); //set SADD = slaveAdress
I2C2->CR2 &= ~I2C_CR2_RD_WRN; // Master requests a write transfer RD_WRN = 0

I2C2->CR2 |=I2C_CR2_START ; //set START = 1
while(!(I2C2->ISR & I2C_ISR_TXIS)); //wait for data to be transmitted TXIS = 1
I2C2->TXDR = (uint32_t)registerAdress ; //write to buf TXDR , registerAdress
while(!(I2C2->ISR & I2C_ISR_TC)); //wait for transfer complete TC = 1
/*RESTART*/
I2C2->CR2 |= I2C_CR2_AUTOEND; //set AUTOEND = 1
I2C2->CR2 |= I2C_CR2_RD_WRN; // Master requests a read transfer RD_WRN = 1
I2C2->CR2 |=I2C_CR2_START ; //set START = 1
while(!(I2C2->ISR & I2C_ISR_RXNE)); //wait for data to be received RXNE = 1
data = I2C2->RXDR ; //read receive bufer
while(!(I2C2->ISR & I2C_ISR_STOPF)); //wait for STOP complete STOPF = 1

#ifdef debug 
printf("data %d!\n", data);
#endif

return data ; 

}



void I2C2_WriteRegister_CAP1296(uint8_t slaveAdress, uint8_t registerAdress, uint8_t data){

while(I2C2->ISR & I2C_ISR_BUSY); //wait for I2C not busy

I2C2->CR2 &= ~I2C_CR2_NBYTES ; //clear NBYTES
I2C2->CR2 |= 2 << I2C_CR2_NBYTES_Pos; //set NBYTES = 2

I2C2->CR2 |= I2C_CR2_AUTOEND; //set AUTOEND = 1

I2C2->CR2 &= ~I2C_CR2_SADD; //clear SADD
I2C2->CR2 |= ((uint32_t)(slaveAdress) << I2C_CR2_SADD_Pos); //set SADD = slaveAdress

I2C2->CR2 &= ~I2C_CR2_RD_WRN; // Master requests a write transfer RD_WRN = 0

I2C2->CR2 |=I2C_CR2_START ; //set START = 1
while(!(I2C2->ISR & I2C_ISR_TXIS)); //wait for data to be transmitted TXIS = 1

I2C2->TXDR = (uint32_t)registerAdress ; //write to buf TXDR , registerAdress
while(!(I2C2->ISR & I2C_ISR_TXIS)); //wait for data to be transmitted TXIS = 1

I2C2->TXDR = (uint32_t)data ; //write to buf TXDR , registerAdress

while(!(I2C2->ISR & I2C_ISR_STOPF)); //wait for STOP complete STOPF = 1


}





/*Interrupt Handler for SysTick*/
/*
void SysTick_Handler(void){

}
*/

void EXTI0_1_IRQHandler(void){
intFlag = 1;
if(EXTI->FPR1 & EXTI_FPR1_FPIF1)
EXTI->FPR1 |= EXTI_FPR1_FPIF1; //clear pending

}