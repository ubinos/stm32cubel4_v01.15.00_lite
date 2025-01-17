/**
  @page QSPI_ExecuteInPlace QSPI execute in place example
  
  @verbatim
  ******************************************************************************
  * @file    QSPI/QSPI_ExecuteInPlace/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the code execution from QSPI memory example.
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

How to execute code from QSPI memory after code loading.

This example describes how to execute a part of the code from a QSPI memory. To do this, 
a section is created where the function is stored.

At the startup, the QSPI memory is erased, then the data are copied from the initialization
section of the flash to the QSPI memory. And finally the QSPI is configured in memory-mapped 
mode and the code in executed in a forever loop.

LED1, LED2, LED3 and LED4 toggle in a forever loop.
LED_RED is on as soon as an error is returned by HAL API, and no more LED toggles.

In this example, HCLK is configured at 80 MHz.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents 

  - QSPI/QSPI_ExecuteInPlace/Inc/stm32l4xx_hal_conf.h HAL configuration file
  - QSPI/QSPI_ExecuteInPlace/Inc/stm32l4xx_it.h       Interrupt handlers header file
  - QSPI/QSPI_ExecuteInPlace/Inc/main.h               Header for main.c module  
  - QSPI/QSPI_ExecuteInPlace/Src/stm32l4xx_it.c       Interrupt handlers
  - QSPI/QSPI_ExecuteInPlace/Src/main.c               Main program
  - QSPI/QSPI_ExecuteInPlace/Src/system_stm32l4xx.c   STM32L4xx system source file
  - QSPI/QSPI_ExecuteInPlace/Src/stm32l4xx_hal_msp.c  HAL MSP file    


@par Hardware and Software environment

  - This example runs on STM32L476xx devices.

    
  - This example has been tested with STM32L476G-EVAL board and can be
    easily tailored to any other supported device and development board.

  - STM32L476G-EVAL Set-up :
    - Make sure that LCD Glass is removed.
    - Make sure that board is configured for QuadSPI memory interface as 
      described in MB1144_UM.pdf :
        - Solder bridges SB8, SB9, SB12, SB14, SB18 and SB21 closed
        - Solder bridges SB13, SB15, SB19 and SB20 opened
        - Resistor R62 removed

  - A specific region for the QSPI memory has been added in the scatter file 
   (STM32L476xx_flash.icf for IAR toolchain, STM32L476G-EVAL.sct for Keil toolchain)
   in order to map functions in this memory

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
