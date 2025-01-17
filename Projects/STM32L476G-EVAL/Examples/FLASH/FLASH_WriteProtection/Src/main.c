/**
  ******************************************************************************
  * @file    FLASH/FLASH_WriteProtection/Src/main.c
  * @author  MCD Application Team
  * @brief   This example provides a description of how to set write protection on
  *          STM32L4xx FLASH.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32L4xx_HAL_Examples
  * @{
  */

/** @addtogroup FLASH_WriteProtection
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/

#define FLASH_USER_START_ADDR       ADDR_FLASH_PAGE_24   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR         ADDR_FLASH_PAGE_28   /* End @ of user Flash area */

#define DATA_32                     ((uint32_t)0x12345678)
#define DATA_64                     ((uint64_t)0x1234567812345678)

/* Uncomment this line to program the Flash pages */
#define FLASH_PAGE_PROGRAM

/* Uncomment this line to Enable Write Protection */
/* #define WRITE_PROTECTION_ENABLE */

/* Uncomment this line to Disable Write Protection */
/* #define WRITE_PROTECTION_DISABLE */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t StartPage = 0, EndPage = 0, StartBank = 0, EndBank = 0;
uint32_t Address = 0;
uint32_t PageError = 0;
__IO TestStatus MemoryProgramStatus = PASSED;
/*Variable used for Erase procedure*/
#ifdef FLASH_PAGE_PROGRAM
static FLASH_EraseInitTypeDef EraseInitStruct;
#endif
/*Variable used to handle the Options Bytes*/
static FLASH_OBProgramInitTypeDef OptionsBytesStruct, OptionsBytesStruct2;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static uint32_t GetPage(uint32_t Address);
static uint32_t GetBank(uint32_t Address);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* STM32L4xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the system clock to 80 MHz */
  SystemClock_Config();

  /* Initialize LED1, LED2 and LED3 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);
  
  /* Initialize test status */
  MemoryProgramStatus = PASSED;
  
  /* Unlock the Flash to enable the flash control register access *************/ 
  HAL_FLASH_Unlock();

  /* Clear OPTVERR bit set on virgin samples */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 

  /* Unlock the Options Bytes *************************************************/
  HAL_FLASH_OB_Unlock();

  /* Get the number of the start and end pages */
  StartPage = GetPage(FLASH_USER_START_ADDR);
  EndPage   = GetPage(FLASH_USER_END_ADDR);

  /* Get the bank of the start and end pages */
  StartBank = GetBank(FLASH_USER_START_ADDR);
  EndBank   = GetBank(FLASH_USER_END_ADDR);

  if (StartBank == EndBank)
  {
    /* WRP area is only on one bank */
    if (StartBank == FLASH_BANK_1)
    {
      OptionsBytesStruct.WRPArea  = OB_WRPAREA_BANK1_AREAA;
      OptionsBytesStruct2.WRPArea = OB_WRPAREA_BANK1_AREAB;
    }
    else
    {
      OptionsBytesStruct.WRPArea  = OB_WRPAREA_BANK2_AREAA;
      OptionsBytesStruct2.WRPArea = OB_WRPAREA_BANK2_AREAB;
    }
  }
  else
  {
    /* WRP area is splitted on two banks */
    /* => Error : this case is not treated in this example */
    while (1)
    {
      BSP_LED_On(LED3);
    }
  }

  /* Get pages write protection status ****************************************/
  HAL_FLASHEx_OBGetConfig(&OptionsBytesStruct);
  HAL_FLASHEx_OBGetConfig(&OptionsBytesStruct2);

#ifdef WRITE_PROTECTION_DISABLE
  /* Check if desired pages are already write protected ***********************/
  if ((OptionsBytesStruct.WRPStartOffset == StartPage) && (OptionsBytesStruct.WRPEndOffset == EndPage))
  {
    /* Current area correspond to the area to disable */
    OptionsBytesStruct.OptionType     = OPTIONBYTE_WRP;
    OptionsBytesStruct.WRPStartOffset = 0xFF;
    OptionsBytesStruct.WRPEndOffset   = 0;
  }
  else if ((OptionsBytesStruct.WRPStartOffset == StartPage) && (OptionsBytesStruct.WRPEndOffset > EndPage))
  {
    /* Current area is bigger than the area to disable : */
    /* - End of area is bigger than the last page to un-protect */
    OptionsBytesStruct.OptionType     = OPTIONBYTE_WRP;
    OptionsBytesStruct.WRPStartOffset = EndPage + 1;
  }
  else if ((OptionsBytesStruct.WRPStartOffset < StartPage) && (OptionsBytesStruct.WRPEndOffset == EndPage))
  {
    /* Current area is bigger than the area to disable : */
    /* - Start of area is lower than the first page to un-protect */
    OptionsBytesStruct.OptionType     = OPTIONBYTE_WRP;
    OptionsBytesStruct.WRPEndOffset   = StartPage - 1;
  }
  else if ((OptionsBytesStruct.WRPStartOffset < StartPage) && (OptionsBytesStruct.WRPEndOffset > EndPage))
  {
    /* Current area is bigger than the area to disable */
    /* - Start of area is lower than the first page to un-protect */
    /* - End of area is bigger than the last page to un-protect */
    if (OptionsBytesStruct2.WRPStartOffset > OptionsBytesStruct2.WRPEndOffset)
    {
      /* Second area of the bank can be used */
      OptionsBytesStruct2.OptionType     = OPTIONBYTE_WRP;
      OptionsBytesStruct2.WRPStartOffset = EndPage + 1;
      OptionsBytesStruct2.WRPEndOffset   = OptionsBytesStruct.WRPEndOffset;

      OptionsBytesStruct.OptionType     = OPTIONBYTE_WRP;
      OptionsBytesStruct.WRPEndOffset   = StartPage - 1;
    }
    else
    {
      /* Second area of the bank already used for WRP */
      /* => Error : not possible to deactivate only the pages indicated */
      while (1)
      {
        BSP_LED_On(LED3);
      }
    }
  }
  else if ((OptionsBytesStruct2.WRPStartOffset == StartPage) && (OptionsBytesStruct2.WRPEndOffset == EndPage))
  {
    /* Current area correspond to the area to disable */
    OptionsBytesStruct2.OptionType     = OPTIONBYTE_WRP;
    OptionsBytesStruct2.WRPStartOffset = 0xFF;
    OptionsBytesStruct2.WRPEndOffset   = 0;
  }
  else if ((OptionsBytesStruct2.WRPStartOffset == StartPage) && (OptionsBytesStruct2.WRPEndOffset > EndPage))
  {
    /* Current area is bigger than the area to disable : */
    /* - End of area is bigger than the last page to un-protect */
    OptionsBytesStruct2.OptionType     = OPTIONBYTE_WRP;
    OptionsBytesStruct2.WRPStartOffset = EndPage + 1;
  }
  else if ((OptionsBytesStruct2.WRPStartOffset < StartPage) && (OptionsBytesStruct2.WRPEndOffset == EndPage))
  {
    /* Current area is bigger than the area to disable : */
    /* - Start of area is lower than the first page to un-protect */
    OptionsBytesStruct2.OptionType     = OPTIONBYTE_WRP;
    OptionsBytesStruct2.WRPEndOffset   = StartPage - 1;
  }
  else if ((OptionsBytesStruct2.WRPStartOffset < StartPage) && (OptionsBytesStruct2.WRPEndOffset > EndPage))
  {
    /* Current area is bigger than the area to disable */
    /* - Start of area is lower than the first page to un-protect */
    /* - End of area is bigger than the last page to un-protect */
    if (OptionsBytesStruct.WRPStartOffset > OptionsBytesStruct.WRPEndOffset)
    {
      /* Second area of the bank can be used */
      OptionsBytesStruct.OptionType     = OPTIONBYTE_WRP;
      OptionsBytesStruct.WRPStartOffset = EndPage + 1;
      OptionsBytesStruct.WRPEndOffset   = OptionsBytesStruct2.WRPEndOffset;

      OptionsBytesStruct2.OptionType     = OPTIONBYTE_WRP;
      OptionsBytesStruct2.WRPEndOffset   = StartPage - 1;
    }
    else
    {
      /* Second area of the bank already used for WRP */
      /* => Error : not possible to deactivate only the pages indicated */
      while (1)
      {
        BSP_LED_On(LED3);
      }
    }
  }

#elif defined WRITE_PROTECTION_ENABLE
  /* Check if desired pages are not yet write protected ***********************/
  if ((OptionsBytesStruct.WRPStartOffset <= StartPage) && (OptionsBytesStruct.WRPEndOffset >= (StartPage - 1)))
  {
    /* Current area is adjacent to pages to be write protected */
    if (OptionsBytesStruct.WRPEndOffset < EndPage)
    {
      /* Current area will be extended to include the pages to be write protected */
      OptionsBytesStruct.OptionType     = OPTIONBYTE_WRP;
      OptionsBytesStruct.WRPEndOffset   = EndPage;
    }
  }
  else if ((OptionsBytesStruct.WRPStartOffset <= (EndPage + 1)) && (OptionsBytesStruct.WRPEndOffset >= EndPage))
  {
    /* Current area is adjacent to pages to be write protected */
    if (OptionsBytesStruct.WRPStartOffset > StartPage)
    {
      /* Current area will be extended to include the pages to be write protected */
      OptionsBytesStruct.OptionType     = OPTIONBYTE_WRP;
      OptionsBytesStruct.WRPStartOffset = StartPage;
    }
  }
  else if ((OptionsBytesStruct.WRPStartOffset > StartPage) && (OptionsBytesStruct.WRPEndOffset < EndPage))
  {
    /* Current area is included in pages to be write protected */
    OptionsBytesStruct.OptionType     = OPTIONBYTE_WRP;
    OptionsBytesStruct.WRPStartOffset = StartPage;
    OptionsBytesStruct.WRPEndOffset   = EndPage;
  }
  else if ((OptionsBytesStruct2.WRPStartOffset <= StartPage) && (OptionsBytesStruct2.WRPEndOffset >= (StartPage - 1)))
  {
    /* Current area is adjacent to pages to be write protected */
    if (OptionsBytesStruct2.WRPEndOffset < EndPage)
    {
      /* Current area will be extended to include the pages to be write protected */
      OptionsBytesStruct2.OptionType     = OPTIONBYTE_WRP;
      OptionsBytesStruct2.WRPEndOffset   = EndPage;
    }
  }
  else if ((OptionsBytesStruct2.WRPStartOffset <= (EndPage + 1)) && (OptionsBytesStruct2.WRPEndOffset >= EndPage))
  {
    /* Current area is adjacent to pages to be write protected */
    if (OptionsBytesStruct2.WRPStartOffset > StartPage)
    {
      /* Current area will be extended to include the pages to be write protected */
      OptionsBytesStruct2.OptionType     = OPTIONBYTE_WRP;
      OptionsBytesStruct2.WRPStartOffset = StartPage;
    }
  }
  else if ((OptionsBytesStruct2.WRPStartOffset > StartPage) && (OptionsBytesStruct2.WRPEndOffset < EndPage))
  {
    /* Current area is included in pages to be write protected */
    OptionsBytesStruct2.OptionType     = OPTIONBYTE_WRP;
    OptionsBytesStruct2.WRPStartOffset = StartPage;
    OptionsBytesStruct2.WRPEndOffset   = EndPage;
  }
  else if (OptionsBytesStruct.WRPStartOffset > OptionsBytesStruct.WRPEndOffset)
  {
    /* Current area is not used => it will be configured to protect the pages */
    OptionsBytesStruct.OptionType     = OPTIONBYTE_WRP;
    OptionsBytesStruct.WRPStartOffset = StartPage;
    OptionsBytesStruct.WRPEndOffset   = EndPage;
  }
  else if (OptionsBytesStruct2.WRPStartOffset > OptionsBytesStruct2.WRPEndOffset)
  {
    /* Current area is not used => it will be configured to protect the pages */
    OptionsBytesStruct2.OptionType     = OPTIONBYTE_WRP;
    OptionsBytesStruct2.WRPStartOffset = StartPage;
    OptionsBytesStruct2.WRPEndOffset   = EndPage;
  }
  else
  {
    /* No more area available to protect the pages */
    /* => Error : not possible to activate the pages indicated */
    while (1)
    {
      BSP_LED_On(LED3);
    }
  }

#endif /* WRITE_PROTECTION_DISABLE */

  /* Configure write protected pages */
  if (OptionsBytesStruct.OptionType == OPTIONBYTE_WRP)
  {
    if(HAL_FLASHEx_OBProgram(&OptionsBytesStruct) != HAL_OK)
    {
      /* Error occurred while options bytes programming. **********************/
      while (1)
      {
        BSP_LED_On(LED3);
      }
    }
  }

  if (OptionsBytesStruct2.OptionType == OPTIONBYTE_WRP)
  {
    if(HAL_FLASHEx_OBProgram(&OptionsBytesStruct2) != HAL_OK)
    {
      /* Error occurred while options bytes programming. **********************/
      while (1)
      {
        BSP_LED_On(LED3);
      }
    }
  }

  /* Generate System Reset to load the new option byte values ***************/
  if ((OptionsBytesStruct.OptionType == OPTIONBYTE_WRP) || (OptionsBytesStruct2.OptionType == OPTIONBYTE_WRP))
  {
    HAL_FLASH_OB_Launch();
  }

  /* Lock the Options Bytes *************************************************/
  HAL_FLASH_OB_Lock();

#ifdef FLASH_PAGE_PROGRAM  
  /* The selected pages are write protected *******************************/
  if (((OptionsBytesStruct.WRPStartOffset  <= StartPage) && (OptionsBytesStruct.WRPEndOffset  >= EndPage)) || 
      ((OptionsBytesStruct2.WRPStartOffset <= StartPage) && (OptionsBytesStruct2.WRPEndOffset >= EndPage)))
  {
    /* The desired pages are write protected */ 
    /* Check that it is not allowed to write in this page */
    Address = FLASH_USER_START_ADDR;
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, DATA_64) != HAL_OK)
    {
      /* Error returned during programming. */
      /* Check that WRPERR flag is well set */
      if ((HAL_FLASH_GetError() & HAL_FLASH_ERROR_WRP) != 0) 
      {
        MemoryProgramStatus = FAILED;
      }
      else
      {
        /* Another error occurred.
           User can add here some code to deal with this error */
        while (1)
        {
          BSP_LED_On(LED3);
        }
      }
    }
    else
    {
      /* Write operation is successful. Should not occur
         User can add here some code to deal with this error */
      while (1)
      {
        BSP_LED_On(LED3);
      }
    }
  }
  else
  {
    /* The desired pages are not write protected */ 
    /* Fill EraseInit structure************************************************/
    EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.Banks       = StartBank;
    EraseInitStruct.Page        = StartPage;
    EraseInitStruct.NbPages     = EndPage - StartPage + 1;

    if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK)
    {
      /* 
        Error occurred while page erase. 
        User can add here some code to deal with this error. 
        PageError will contain the faulty page and then to know the code error on this page,
        user can call function 'HAL_FLASH_GetError()'
      */
      while (1)
      {
        BSP_LED_On(LED3);
      }
    }

    /* FLASH Word program of DATA_32 at addresses defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR */
    Address = FLASH_USER_START_ADDR;
    while (Address < FLASH_USER_END_ADDR)
    {
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, DATA_64) == HAL_OK)
      {
        Address = Address + 8;
      }
      else
      {
        /* Error occurred while writing data in Flash memory. 
           User can add here some code to deal with this error */
        while (1)
        {
          BSP_LED_On(LED3);
        }
      }
    }

    /* Check the correctness of written data */
    Address = FLASH_USER_START_ADDR;

    while (Address < FLASH_USER_END_ADDR)
    {
      if((*(__IO uint32_t*) Address) != DATA_32)
      {
        MemoryProgramStatus = FAILED;
      }
      Address += 4;
    }
  }
#endif /* FLASH_PAGE_PROGRAM */

  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  HAL_FLASH_Lock();

  /*Check if there is an issue to program data*/
  if (MemoryProgramStatus == PASSED)
  {
    /* No error detected. Switch on LED1*/
    BSP_LED_On(LED1);
  }
  else
  {
    /* Error detected. Switch on LED2*/
    BSP_LED_On(LED2);
  }

  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  Gets the page of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The page of a given address
  */
static uint32_t GetPage(uint32_t Addr)
{
  uint32_t page = 0;
  
  if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
  {
    /* Bank 1 */
    page = (Addr - FLASH_BASE) / FLASH_PAGE_SIZE;
  }
  else
  {
    /* Bank 2 */
    page = (Addr - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_PAGE_SIZE;
  }
  
  return page;
}

/**
  * @brief  Gets the bank of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The bank of a given address
  */
static uint32_t GetBank(uint32_t Addr)
{
  uint32_t bank = 0;
  
  if (READ_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_FB_MODE) == 0)
  {
  	/* No Bank swap */
    if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
    {
      bank = FLASH_BANK_1;
    }
    else
    {
      bank = FLASH_BANK_2;
    }
  }
  else
  {
  	/* Bank swap */
    if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
    {
      bank = FLASH_BANK_2;
    }
    else
    {
      bank = FLASH_BANK_1;
    }
  }
  
  return bank;
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 80000000
  *            HCLK(Hz)                       = 80000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 1
  *            PLL_N                          = 20
  *            PLL_P                          = 7
  *            PLL_Q                          = 4
  *            PLL_R                          = 2
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* Enable HSE Oscillator and activate PLL with HSE as source   */
  /* (Default MSI Oscillator enabled at system reset remains ON) */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 20;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLP = 7;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
