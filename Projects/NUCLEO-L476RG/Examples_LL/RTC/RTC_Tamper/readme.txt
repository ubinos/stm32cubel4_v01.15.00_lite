/**
  @page RTC_Tamper RTC example
  
  @verbatim
  ******************************************************************************
  * @file    Examples_LL/RTC/RTC_Tamper/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the RTC example.
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

Configuration of the Tamper using the RTC LL API. The peripheral initialization 
uses LL unitary service functions for optimization purposes (performance and size).

In this example, after start-up, SYSCLK is configured to the max frequency using the PLL with
MSI as clock source.

The RTC peripheral configuration is ensured by the Configure_RTC() function 
(configure of the needed RTC resources according to the used hardware CLOCK, 
PWR, RTC clock source and BackUp). You may update this function to change RTC configuration.

The associated firmware performs the following:
1. It configures the Tamper pin to be falling edge, and enables the Tamper 
   interrupt.
2. It writes the data to all RTC Backup data registers, then check whether the
   data were correctly written. If yes, LED2 toggles with a fast period,
   otherwise LED2 toggles with a period of 1s.
3. Applying a low level on the USER_BUTTON_PIN (PC.13) by pressing User push-button,
   the RTC backup data registers are reset and the Tamper interrupt is generated. 
   The corresponding ISR then checks whether the RTC Backup data registers are cleared.
   If yes LED2 turns on, otherwise LED2 toggles with a period of 1s.
      
@par Directory contents 

  - RTC/RTC_Tamper/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - RTC/RTC_Tamper/Inc/main.h                  Header for main.c module
  - RTC/RTC_Tamper/Inc/stm32_assert.h          Template file to include assert_failed function
  - RTC/RTC_Tamper/Src/stm32l4xx_it.c          Interrupt handlers
  - RTC/RTC_Tamper/Src/main.c                  Main program
  - RTC/RTC_Tamper/Src/system_stm32l4xx.c      STM32L4xx system source file


@par Hardware and Software environment

  - This example runs on STM32L476xx devices.
    
  - This example has been tested with NUCLEO-L476RG Rev C board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
