/**
  @page RNG_GenerateRandomNumbers RNG : Random Number Generation
  
  @verbatim
  ******************************************************************************
  * @file    Examples_LL/RNG/RNG_GenerateRandomNumbers/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the RNG_GenerateRandomNumbers example.
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

Configuration of the RNG to generate 32-bit long random numbers. The peripheral initialization uses LL unitary service
functions for optimization purposes (performance and size).

Example execution:
After startup from reset and system configuration, RNG configuration is performed.
(Configure PLLSA11 to enable 48M domain, then enable PLLSAI1 output mapped on 48MHz domain clock
and configure PLLSAI as RNG clock source).

User is then asked to press key button (LED blinking fast).
On user button press, several (8) Random 32bit numbers are generated
(DRDY flag is polled until 1, indicating a random number has been generated and could be retrieved from DR register).
Corresponding generated values are available and stored in a u32 array (aRandom32bit), 
whose content could be displayed using debugger (Watch or LiveWatch features).
After successful Random numbers generation, LED is turned On. 
In case of errors, LED is slowly blinking (1sec period).

@par Directory contents 

  - RNG/RNG_GenerateRandomNumbers/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - RNG/RNG_GenerateRandomNumbers/Inc/main.h                  Header for main.c module
  - RNG/RNG_GenerateRandomNumbers/Inc/stm32_assert.h          Template file to include assert_failed function
  - RNG/RNG_GenerateRandomNumbers/Src/stm32l4xx_it.c          Interrupt handlers
  - RNG/RNG_GenerateRandomNumbers/Src/main.c                  Main program
  - RNG/RNG_GenerateRandomNumbers/Src/system_stm32l4xx.c      STM32L4xx system source file


@par Hardware and Software environment

  - This example runs on STM32L476xx devices.
    
  - This example has been tested with NUCLEO-L476RG Rev C board and can be
    easily tailored to any other supported device and development board.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example
 - Push User button and use Variable watch window from debugger to access to values of generated numbers.
   (A break point could be set on LED_On() call, at end of RandomNumbersGeneration() function).

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
