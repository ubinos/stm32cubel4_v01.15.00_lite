/**
  @page I2C_EEPROM I2C EEPROM DMA example
  
  @verbatim
  ******************************************************************************
  * @file    I2C/I2C_EEPROM/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the I2C EEPROM DMA example.
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  @endverbatim

@par Example Description 

How to handle I2C data buffer transmission/reception with DMA. In the example, 
the device communicates with an I2C EEPROM memory.

#if defined(USE_STM32L476G_EVAL_REVA)
SCL Pin: PG.14
SDA Pin: PG.13

#elif defined(USE_STM32L476G_EVAL_REVB)

SCL Pin: PB.10
SDA Pin: PB.11
#endif
   __________________________________________________________________________                        
  |           ______________                        ______________           |
#if defined(USE_STM32L476G_EVAL_REVA)
  |          | I2C1         |                      |    I2C_EEPROM|          |
#elif defined(USE_STM32L476G_EVAL_REVB)
  |          | I2C2         |                      |    I2C_EEPROM|          |
#endif
  |          |              |                      |              |          |
  |          |           SCL|______________________|CLOCK         |          |
  |          |              |                      |              |          |
  |          |              |                      |              |          |
  |          |              |                      |              |          |
  |          |           SDA|______________________|DATA          |          |
  |          |              |                      |              |          |
  |          |______________|                      |______________|          |
  |                                                                          |
  |__________________________________________________________________________|
      STM32L476G-EVAL

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 80 MHz.

The I2C peripheral configuration is ensured by the HAL_I2C_Init() function.
This later is calling the HAL_I2C_MspInit()function which core is implementing
the configuration of the needed I2C resources according to the used hardware (CLOCK, 
GPIO, DMA and NVIC). You may update this function to change I2C configuration.

The I2C/EEPROM communication is then initiated.
The HAL_I2C_Mem_Read_DMA() and the HAL_I2C_Mem_Write_DMA() functions allow respectively 
the reception of Data from EEPROM and the transmission of a predefined data 
buffer.

For this example the TxBuffer is predefined and the aRxBuffer size is same as aTxBuffer.

In a first step the I2C writes the aTxBuffer by group of 64 bytes (EEPROM M24128
Page size) using HAL_I2C_Mem_Write_DMA() then read back the data through aRxBuffer
using HAL_I2C_Mem_Read_DMA(). 
The end of this two steps are monitored through the HAL_I2C_GetState() function
result.
Finally, aTxBuffer and aRxBuffer are compared through Buffercmp() in order to 
check buffers correctness.  

STM32 Eval board's LEDs can be used to monitor the transfer status:
 - LED1 is ON when the transmission process is complete.
 - LED2 is ON when the reception process is complete.
 - LED3 is ON when there is an error in transmission/reception process.  

@note I2Cx instance used and associated resources can be updated in "main.h"
file depending hardware configuration used.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - I2C/I2C_EEPROM/Inc/stm32l4xx_hal_conf.h    HAL configuration file
  - I2C/I2C_EEPROM/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - I2C/I2C_EEPROM/Inc/main.h                  Header for main.c module  
  - I2C/I2C_EEPROM/Src/stm32l4xx_it.c          Interrupt handlers
  - I2C/I2C_EEPROM/Src/main.c                  Main program
  - I2C/I2C_EEPROM/Src/system_stm32l4xx.c      STM32L4xx system source file
  - I2C/I2C_EEPROM/Src/stm32l4xx_hal_msp.c     HAL MSP file    


@par Hardware and Software environment

  - This example runs on STM32L476xx devices.
    
  - This example has been tested with STM32L476G-EVAL board and can be
    easily tailored to any other supported device and development board.    

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files: Project->Rebuild all
 - Load project image: Project->Download and Debug
 - Run program: Debug->Go(F5) 


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
