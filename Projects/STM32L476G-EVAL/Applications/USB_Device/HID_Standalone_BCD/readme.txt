/**
  @page HID_Standalone_BCD USB Device Humain Interface (HID + BCD) example
  
  @verbatim
  ******************************************************************************
  * @file    USB_Device/HID_Standalone_BCD/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the USB HID BCD example.
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license SLA0044,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       http://www.st.com/SLA0044
  *
  ******************************************************************************
  @endverbatim

@par Application Description 

Use of the USB device application based on the Human Interface (HID) with 
Battery Charger Detection (BCD).

The STM32L4xx device integrated battery charger detection circuitry supports USB-IF Battery 
Charger Detection, BCD,(revision 1.2). The hpcd.Init.battery_charging_enable in the usbd_conf.c 
should be set to 1 to enable the support for BCD.

This example is part of the USB Device Library package using STM32Cube firmware.

This is a typical example on how to use the STM32L4xx USB OTG Device peripheral where the STM32 MCU is
enumerated as a HID device using the native PC Host HID driver to which the STM32L476G-EVAL
board is connected, the Mouse directions are controlled using Joystick buttons mounted on the 
STM32L476G-EVAL board.

Battery charger detection will begin automatically when VBUS is detected. The STM32FL4xx include the 
capability to detect various USB battery chargers and can detect a range of USB battery chargers including a Standard Downstream
Port (SDP), a Charging Downstream Port (CDP), and a Dedicated Charging Port (DCP). For more information
on USB battery charger detection, please see the USB Battery Charging Specification, Revision 1.2 (Note 1).

In this example, we use STM32L476G-EVAL board LEDs to indicate the following connection status events:
-	Green LED for DCD 
-	Orange LED for detection of Standard Downstream port (host port without charging capability)
-	Blue LED for detection of a Charging Downstream port (host port with charging capability)
-	Red LED for detection of Dedicated Charging port (Charger with  short circuit between D+ and D-)

If a DCP is connected (D+/D- are shorted or connected through 200 ohm resistor)
In CDP case we used a HP dock Station: charging port


At the beginning of the main program the HAL_Init() function is called to reset all the peripherals,
initialize the Flash interface and the systick. The user is provided with the SystemClock_Config()
function to configure the system clock (SYSCLK) to run at 80 MHz. The Full Speed (FS) USB module uses
internally a 48-MHz clock which is coming from a specific output of two PLLs (PLL or PLL SAI) or from MSI

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.
      
For more details about the STM32Cube USB Device library, please refer to UM1734 
"STM32Cube USB Device library".
      
@par Directory contents

  - USB_Device/HID_Standalone_BCD/Src/main.c                  Main program
  - USB_Device/HID_Standalone_BCD/Src/system_stm32l4xx.c      STM32L4xx system clock configuration file
  - USB_Device/HID_Standalone_BCD/Src/stm32l4xx_it.c          Interrupt handlers
  - USB_Device/HID_Standalone_BCD/Src/usbd_conf.c             General low level driver configuration
  - USB_Device/HID_Standalone_BCD/Src/usbd_desc.c             USB device HID descriptor
  - USB_Device/HID_Standalone_BCD/Inc/main.h                  Main program header file
  - USB_Device/HID_Standalone_BCD/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - USB_Device/HID_Standalone_BCD/Inc/stm32l4xx_hal_conf.h    HAL configuration file
  - USB_Device/HID_Standalone_BCD/Inc/usbd_conf.h             USB device driver Configuration file
  - USB_Device/HID_Standalone_BCD/Inc/usbd_desc.h             USB device MSC descriptor header file  

	
@par Hardware and Software environment

  - This example runs on STM32L476xx devices.
    
  - This example has been tested with STMicroelectronics STM32L476G-EVAL 
    evaluation boards and can be easily tailored to any other supported device 
    and development board.

  - STM32L476G-EVAL Set-up
    - Make sure that LCD Glass is in position IO
    - Connect the STM32L476G-EVAL board to the PC through 'USB micro A-Male 
      to A-Male' cable to the connector CN1 (OTG-FS)     
    - Make sure jumper JP1 is in connected in position 3V3.
      
@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
  