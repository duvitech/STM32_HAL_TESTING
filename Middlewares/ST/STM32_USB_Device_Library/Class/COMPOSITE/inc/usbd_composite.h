/**
  ******************************************************************************
  * @file    usbd_COMPOSITE_core.h
  * @author  MCD Application Team
  * @brief   Header file for the usbd_COMPOSITE_core.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __USB_COMPOSITE_CORE_H
#define __USB_COMPOSITE_CORE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include  "usbd_ioreq.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */
  
/** @defgroup USBD_TEMPLATE
  * @brief This file is the header file for usbd_COMPOSITE_core.c
  * @{
  */ 


/** @defgroup USBD_COMPOSITE_Exported_Defines
  * @{
  */ 
#define MAX_CLASSES 0x09

#define USBD_MSC_INTERFACE_IDX 0x00
#define USBD_CDC_INTERFACE_IDX 0x01

#define USB_COMPOSITE_CONFIG_DESC_SIZ       9

/**
  * @}
  */ 


/** @defgroup USBD_CORE_Exported_TypesDefinitions
  * @{
  */

/**
  * @}
  */ 

USBD_StatusTypeDef  USBD_COMPOSITE_RegisterClass(USBD_ClassTypeDef *pclass, void *fops);

/** @defgroup USBD_CORE_Exported_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup USBD_CORE_Exported_Variables
  * @{
  */ 

extern USBD_ClassTypeDef  USBD_COMPOSITE;
/**
  * @}
  */ 

/** @defgroup USB_CORE_Exported_Functions
  * @{
  */ 
/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif  /* __USB_COMPOSITE_CORE_H */
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
