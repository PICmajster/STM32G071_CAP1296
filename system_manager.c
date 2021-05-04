#include <stm32g071xx.h>
#include "clock_manager.h"
#include "pin_manager.h"
#include "system_manager.h"
#include "i2c_manager.h"
#include "interrupt_manager.h"


void SYSTEM_MANAGER_Initialize(void){

CLOCK_MANAGER_Initialize();
PIN_MANAGER_Initialize();
I2C2_MANAGER_Initialize();
INTERRUPT_MANAGER_Initialize();


}