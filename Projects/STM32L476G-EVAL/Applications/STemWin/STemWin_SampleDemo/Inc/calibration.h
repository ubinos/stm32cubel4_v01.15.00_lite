/**
  ******************************************************************************
  * @file    calibration.h
  * @author  MCD Application Team
  * @brief   Header for CALIBRATION.c module
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
#ifndef __CALIBRATION_H
#define __CALIBRATION_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 
void CALIBRATION_Check(void);
uint8_t  CALIBRATION_IsDone(void);
uint16_t CALIBRATION_GetX(uint16_t x);
uint16_t CALIBRATION_GetY(uint16_t y);

#ifdef __cplusplus
}
#endif

#endif /*__CALIBRATION_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
