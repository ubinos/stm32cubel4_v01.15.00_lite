/**
  ******************************************************************************
  * @file    Examples_LL/COMP/COMP_CompareGpioVsVrefInt_OutputGpio/Src/main.c
  * @author  MCD Application Team
  * @brief   This example shows how to use a comparator peripheral
  *          to compare a voltage level applied on a GPIO pin
  *          versus the internal voltage reference (VrefInt),
  *          comparator output is connected to a GPIO.
  *          This example is based on the STM32L4xx COMP LL API;
  *          Peripheral initialization done using LL unitary services functions.
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

/** @addtogroup STM32L4xx_LL_Examples
  * @{
  */

/** @addtogroup COMP_CompareGpioVsVrefInt_OutputGpio
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void     SystemClock_Config(void);
void     Configure_COMP(void);
void     Activate_COMP(void);
void     LED_Init(void);
void     LED_On(void);
void     LED_Off(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* Configure the system clock to 80 MHz */
  SystemClock_Config();
  
  /* Initialize LED2 */
  LED_Init();
  
  /* Configure comparator */
  Configure_COMP();
  
  /* Activate comparator */
  Activate_COMP();
  
  /* Lock comparator instance */
  //LL_COMP_Lock(COMP1);
  
  /* Infinite loop */
  while (1)
  {
    /* Set LED state in function of state of GPIO connected to                */
    /* comparator output.                                                     */
    /* Note: State of GPIO is monitored for the purpose of this example.      */
    /*       An alternate solution is to monitor directly comparator output   */
    /*       using function "LL_COMP_ReadOutputLevel()".                      */
    if (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_0) != 0)
    {
      LED_On();
    }
    else
    {
      LED_Off();
    }
    
  }
}

/**
  * @brief  Configure comparator (COMP instance: COMP1), GPIO and EXTI line
  *         used by comparator.
  * @note   This function configures the comparator but does not enable it,
  *         in order to optimize power consumption (comparator enabled only
  *         when needed).
  * @note   Peripheral configuration is minimal configuration from reset values.
  *         Thus, some useless LL unitary functions calls below are provided as
  *         commented examples - setting is default configuration from reset.
  * @param  None
  * @retval None
  */
void Configure_COMP(void)
{
  __IO uint32_t wait_loop_index = 0;
  
  /*## Configuration of GPIO used by comparator ##############################*/
  
  /* Configure GPIO connected to the selected comparator input plus */
  /* Enable GPIO clock */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
  
  /* Configure GPIO in analog mode to be used as COMP input */
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_5, LL_GPIO_MODE_ANALOG);
  
  /* Configure GPIO connected to the comparator output */
  /* Note: Other GPIO are available as comparator output,                     */
  /*       refer to device datasheet.                                         */
  /* Enable GPIO clock */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  
  /* Configure GPIO output type */
  LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_0, LL_GPIO_OUTPUT_PUSHPULL);
  
  /* Configure GPIO speed */
  LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_0, LL_GPIO_SPEED_FREQ_HIGH);
  
  /* Configure GPIO in alternate function mode to be used as COMP output */
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_0, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_0, LL_GPIO_AF_12);
  
  /*## Configuration of NVIC #################################################*/
  /* Note: Comparator interruption is not enabled                             */
  /*       in this example.                                                   */
  
  /*## Configuration of comparator ###########################################*/
  
  /* Enable COMP clock */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  
  /*## Configuration of comparator common instance ###########################*/
  
  /* Set comparator common instance window mode */
  /* Note: Window mode is common to 2 COMP instances, and therefore must      */
  /*       with a COMP common instance (COMP12_COMMON, ...)                   */
  //LL_COMP_SetCommonWindowMode(__LL_COMP_COMMON_INSTANCE(COMP1), LL_COMP_WINDOWMODE_DISABLE);
  
  /*## Configuration of comparator instance ##################################*/
  
  /* Set comparator instance operating mode to adjust power and speed */
  LL_COMP_SetPowerMode(COMP1, LL_COMP_POWERMODE_ULTRALOWPOWER);
  
  /* Set comparator inputs */
  LL_COMP_ConfigInputs(COMP1, LL_COMP_INPUT_MINUS_VREFINT, LL_COMP_INPUT_PLUS_IO1);
  
  /* Note: Call of the functions below are commented because they are         */
  /*       useless in this example:                                           */
  /*       settings corresponding to default configuration from reset state.  */
  
  /* Set comparator instance hysteresis mode of the input minus */
  //LL_COMP_SetInputHysteresis(COMP1, LL_COMP_HYSTERESIS_NONE);
  
  /* Set comparator instance output polarity */
  //LL_COMP_SetOutputPolarity(COMP1, LL_COMP_OUTPUTPOL_NONINVERTED);
  
  /* Set comparator instance blanking source */
  //LL_COMP_SetOutputBlankingSource(COMP1, LL_COMP_BLANKINGSRC_NONE);
  
  /* Delay for COMP voltage scaler stabilization time.                        */
  /* Compute number of CPU cycles to wait for, from delay in us.              */
  /* Note: Variable divided by 2 to compensate partially                      */
  /*       CPU processing cycles (depends on compilation optimization).       */
  /* Note: If system core clock frequency is below 200kHz, wait time          */
  /*       is only a few CPU processing cycles.                               */
  wait_loop_index = ((LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US * (SystemCoreClock / (100000 * 2))) / 10);
  while(wait_loop_index != 0)
  {
    wait_loop_index--;
  }
  
  /*## Configuration of EXTI line used by comparator #########################*/
  /* Note: Comparator interruption through EXTI line is not enabled           */
  /*       in this example.                                                   */
  
}

/**
  * @brief  Perform comparator activation procedure
  *         (COMP instance: COMP1).
  * @note   Operations:
  *         - Enable comparator instance
  *         - Wait for comparator startup time
  *           (required to reach propagation delay specification)
  * @param  None
  * @retval None
  */
void Activate_COMP(void)
{
  __IO uint32_t wait_loop_index = 0;
  
  /* Enable comparator */
  LL_COMP_Enable(COMP1);
  
  /* Delay for comparator startup time.                                       */
  /* Compute number of CPU cycles to wait for, from delay in us.              */
  /* Note: Variable divided by 2 to compensate partially                      */
  /*       CPU processing cycles (depends on compilation optimization).       */
  /* Note: If system core clock frequency is below 200kHz, wait time          */
  /*       is only a few CPU processing cycles.                               */
  wait_loop_index = ((LL_COMP_DELAY_STARTUP_US * (SystemCoreClock / (100000 * 2))) / 10);
  while(wait_loop_index != 0)
  {
    wait_loop_index--;
  }
  
}

/**
  * @brief  Initialize LED2.
  * @param  None
  * @retval None
  */
void LED_Init(void)
{
  /* Enable the LED2 Clock */
  LED2_GPIO_CLK_ENABLE();

  /* Configure IO in output push-pull mode to drive external LED2 */
  LL_GPIO_SetPinMode(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_MODE_OUTPUT);
  /* Reset value is LL_GPIO_OUTPUT_PUSHPULL */
  //LL_GPIO_SetPinOutputType(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  /* Reset value is LL_GPIO_SPEED_FREQ_LOW */
  //LL_GPIO_SetPinSpeed(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_SPEED_FREQ_LOW);
  /* Reset value is LL_GPIO_PULL_NO */
  //LL_GPIO_SetPinPull(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_PULL_NO);
}

/**
  * @brief  Turn-on LED2.
  * @param  None
  * @retval None
  */
void LED_On(void)
{
  /* Turn LED2 on */
  LL_GPIO_SetOutputPin(LED2_GPIO_PORT, LED2_PIN);
}

/**
  * @brief  Turn-off LED2.
  * @param  None
  * @retval None
  */
void LED_Off(void)
{
  /* Turn LED2 off */
  LL_GPIO_ResetOutputPin(LED2_GPIO_PORT, LED2_PIN);
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (MSI)
  *            SYSCLK(Hz)                     = 80000000
  *            HCLK(Hz)                       = 80000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            MSI Frequency(Hz)              = 4000000
  *            PLL_M                          = 1
  *            PLL_N                          = 40
  *            PLL_R                          = 2
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  /* MSI configuration and activation */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);
  LL_RCC_MSI_Enable();
  while(LL_RCC_MSI_IsReady() != 1) 
  {
  };
  
  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_MSI, LL_RCC_PLLM_DIV_1, 40, LL_RCC_PLLR_DIV_2);
  LL_RCC_PLL_Enable();
  LL_RCC_PLL_EnableDomain_SYS();
  while(LL_RCC_PLL_IsReady() != 1) 
  {
  };
  
  /* Sysclk activation on the main PLL */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) 
  {
  };
  
  /* Set APB1 & APB2 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  /* Set systick to 1ms in using frequency set to 80MHz */
  /* This frequency can be calculated through LL RCC macro */
  /* ex: __LL_RCC_CALC_PLLCLK_FREQ(__LL_RCC_CALC_MSI_FREQ(LL_RCC_MSIRANGESEL_RUN, LL_RCC_MSIRANGE_6), 
                                  LL_RCC_PLLM_DIV_1, 40, LL_RCC_PLLR_DIV_2)*/
  LL_Init1msTick(80000000);
  
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(80000000);
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
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */

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
