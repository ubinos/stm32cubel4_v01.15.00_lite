/**
  ******************************************************************************
  * @file    lcd_log_conf.h
  * @author  MCD Application Team
  * @brief   lcd_log configuration template file.
  *          This file should be copied to the application folder and modified 
  *          as follows:
  *            - Rename it to 'lcd_log_conf.h'.
  *            - Update the name of the LCD driver's header file, depending on
  *               the EVAL board you are using, see line40 below (be default this  
  *               file will generate compile error unless you do this modification).
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license SLA0044,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        http://www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef  __LCD_LOG_CONF_H__
#define  __LCD_LOG_CONF_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32l476g_eval_lcd.h" 
#include <stdio.h>


/** @addtogroup LCD_LOG
  * @{
  */
  
/** @defgroup LCD_LOG
  * @brief This file is the 
  * @{
  */ 


/** @defgroup LCD_LOG_CONF_Exported_Defines
  * @{
  */ 

/* Define the LCD default text color */
#define     LCD_LOG_DEFAULT_COLOR    LCD_COLOR_WHITE

/* Comment the line below to disable the scroll back and forward features */
#define     LCD_SCROLL_ENABLED      1
   

/* Define the Fonts  */
#define     LCD_LOG_HEADER_FONT                   Font16
#define     LCD_LOG_FOOTER_FONT                   Font12
#define     LCD_LOG_TEXT_FONT                     Font12

/* Define the LCD LOG Color  */
#define     LCD_LOG_BACKGROUND_COLOR              LCD_COLOR_BLACK
#define     LCD_LOG_TEXT_COLOR                    LCD_COLOR_WHITE

#define     LCD_LOG_SOLID_BACKGROUND_COLOR        LCD_COLOR_BLUE
#define     LCD_LOG_SOLID_TEXT_COLOR              LCD_COLOR_WHITE

/* Define the cache depth */
#define     CACHE_SIZE              100
#define     YWINDOW_SIZE            12

#if (YWINDOW_SIZE > 14)
  #error "Wrong YWINDOW SIZE"
#endif

/* Redirect the printf to the LCD */
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define LCD_LOG_PUTCHAR int __io_putchar(int ch)
#else
#define LCD_LOG_PUTCHAR int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/** @defgroup LCD_LOG_CONF_Exported_TypesDefinitions
  * @{
  */ 

/**
  * @}
  */ 


/** @defgroup LCD_LOG_Exported_Macros
  * @{
  */ 


/**
  * @}
  */ 

/** @defgroup LCD_LOG_CONF_Exported_Variables
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup LCD_LOG_CONF_Exported_FunctionsPrototype
  * @{
  */ 

/**
  * @}
  */ 


#endif //__LCD_LOG_CONF_H__

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
