/**
  @page HID_Standalone_LPM USB Device Human Interface (HID) example with LPM 
  
  @verbatim
  ******************************************************************************
  * @file    USB_Device/HID_Standalone_LPM/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the USB HID LPM example.
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
Link Power Management Protocol (LPM).

This example is part of the USB Device Library package using STM32Cube firmware.

STM32L4xx USB device supports the Link Power Management Protocol (LPM-L1) and complies with the USB 2.0
LPM-L1 ECN. The hpcd.Init.lpm_enable in the usbd_conf.c should be set to 1 to enable the support for LPM-L1
protocol in the USB stack.

LPM-L1 allows a USB host to configure the USB device into inactive state much faster than the normal 
USB suspend mode (L2).
It also provides much faster wake-up times in the order of micro-seconds compared to the generic resume 
by host or upstream resume by device.

When LPM packet is received from Host, STM32 USB will Acknowledge the LPM packet
and it will enter in L1 suspend mode. During USB L1 suspend mode ,system will be
in STOP low power mode.

On Host L1 resume, STM32 will wakeup from STOP and USB resumes operations.

You can test L1 suspend/resume, by running the USBCV3.0 chapter9 for USB2.0 devices 
and select (in debug mode) test "TD9.21: LPM L1 Suspend Resume Test".
Please note that for running USBCV3.0, you'll need a PC with a USB3.0 (xHCI)
host controller (please refer to USBCV3.0 documentation for more informations).

You can find in folder \Projects\USBCV3.0 , the full USBCV3.0 chapter9
test report.

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

  - USB_Device/HID_Standalone_LPM/Src/main.c                  Main program
  - USB_Device/HID_Standalone_LPM/Src/system_stm32l4xx.c      STM32L4xx system clock configuration file
  - USB_Device/HID_Standalone_LPM/Src/stm32l4xx_it.c          Interrupt handlers
  - USB_Device/HID_Standalone_LPM/Src/usbd_conf.c             General low level driver configuration
  - USB_Device/HID_Standalone_LPM/Src/usbd_desc.c             USB device HID descriptor
  - USB_Device/HID_Standalone_LPM/Inc/main.h                  Main program header file
  - USB_Device/HID_Standalone_LPM/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - USB_Device/HID_Standalone_LPM/Inc/stm32l4xx_hal_conf.h    HAL configuration file
  - USB_Device/HID_Standalone_LPM/Inc/usbd_conf.h             USB device driver Configuration file
  - USB_Device/HID_Standalone_LPM/Inc/usbd_desc.h             USB device MSC descriptor header file  

	
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
  