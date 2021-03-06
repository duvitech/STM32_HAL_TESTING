/**
  ******************************************************************************
  * @file    usbd_composite.c
  * @author  MCD Application Team
  * @brief   This file provides the HID core functions.
  *
  * @verbatim
  *      
  *          ===================================================================      
  *                                TEMPLATE Class  Description
  *          ===================================================================
  *          
  *
  *
  *
  *           
  *      
  * @note     In HS mode and when the DMA is used, all variables and data structures
  *           dealing with the DMA during the transaction process should be 32-bit aligned.
  *           
  *      
  *  @endverbatim
  *
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

/* Includes ------------------------------------------------------------------*/
#include "usbd_composite.h"
#include "usbd_desc.h"
#include "usbd_ctlreq.h"

#include "usbd_msc.h"
#include "usbd_cdc.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup usbd_composite 
  * @brief usbd core module
  * @{
  */ 

/** @defgroup usbd_composite_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup usbd_composite_Private_Defines
  * @{
  */ 

/**
  * @}
  */ 


/** @defgroup usbd_composite_Private_Macros
  * @{
  */ 
                                         
/**
  * @}
  */ 




/** @defgroup usbd_composite_Private_FunctionPrototypes
  * @{
  */


static uint8_t  usbd_composite_Init (USBD_HandleTypeDef *pdev, 
                               uint8_t cfgidx);

static uint8_t  usbd_composite_DeInit (USBD_HandleTypeDef *pdev, 
                                 uint8_t cfgidx);

static uint8_t  usbd_composite_Setup (USBD_HandleTypeDef *pdev, 
                                USBD_SetupReqTypedef *req);

static uint8_t  *usbd_composite_GetCfgDesc (uint16_t *length);

static uint8_t  *usbd_composite_GetDeviceQualifierDesc (uint16_t *length);

static uint8_t  usbd_composite_DataIn (USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t  usbd_composite_DataOut (USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t  usbd_composite_EP0_RxReady (USBD_HandleTypeDef *pdev);

static uint8_t  usbd_composite_EP0_TxReady (USBD_HandleTypeDef *pdev);

static uint8_t  usbd_composite_SOF (USBD_HandleTypeDef *pdev);

static uint8_t  usbd_composite_IsoINIncomplete (USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t  usbd_composite_IsoOutIncomplete (USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint16_t usbd_composite_CfgDesc_len = 0;
static uint8_t*  usbd_composite_CfgDesc = NULL;


static int classes = 0;
static USBD_ClassTypeDef *USBD_Classes[MAX_CLASSES];
static void *USBD_Userdata[MAX_CLASSES];
static void *USBD_Classdata[MAX_CLASSES];
static void *USBD_Data[MAX_CLASSES];

/**
  * @}
  */ 

/** @defgroup usbd_composite_Private_Variables
  * @{
  */ 

USBD_ClassTypeDef  USBD_COMPOSITE = 
{
  usbd_composite_Init,
  usbd_composite_DeInit,
  usbd_composite_Setup,
  usbd_composite_EP0_TxReady,  
  usbd_composite_EP0_RxReady,
  usbd_composite_DataIn,
  usbd_composite_DataOut,
  usbd_composite_SOF,
  usbd_composite_IsoINIncomplete,
  usbd_composite_IsoOutIncomplete,      
  usbd_composite_GetCfgDesc,
  usbd_composite_GetCfgDesc, 
  usbd_composite_GetCfgDesc,
  usbd_composite_GetDeviceQualifierDesc,
};

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4   
#endif
/* USB Base device Configuration Descriptor */
static uint8_t usbd_base_CfgDesc[USB_COMPOSITE_CONFIG_DESC_SIZ] =
{
  0x09, /* bLength: Configuation Descriptor size */
  USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION, /* bDescriptorType: Configuration */
  USB_COMPOSITE_CONFIG_DESC_SIZ + USB_MSC_CONFIG_DESC_SIZ + USB_CDC_CONFIG_DESC_SIZ,
  /* wTotalLength: Bytes returned */
  0x00,
  0x03,         /*bNumInterfaces: 3 interface*/
  0x01,         /*bConfigurationValue: Configuration value*/
  0x02,         /*iConfiguration: Index of string descriptor describing the configuration*/
  0xC0,         /*bmAttributes: bus powered and Supports Remote Wakeup */
  0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/
  /* 09 */
  
	/* each composit device */
	
};
  
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4   
#endif
/* USB Standard Device Descriptor */
static uint8_t usbd_composite_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};

/**
  * @}
  */ 

/** @defgroup usbd_composite_Private_Functions
  * @{
  */ 

/**
  * @brief  usbd_composite_Init
  *         Initialize the TEMPLATE interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  usbd_composite_Init (USBD_HandleTypeDef *pdev, 
                               uint8_t cfgidx)
{
	// printf("%s cfgidx: %d\r\n", __func__, cfgidx);
  uint8_t ret = 0;

  return ret;
}

USBD_StatusTypeDef  USBD_COMPOSITE_RegisterClass(USBD_ClassTypeDef *pclass, void *fops)
{
  USBD_StatusTypeDef   status = USBD_OK;
	USBD_Classes[classes] = pclass;
	USBD_Classdata[classes] = NULL;
	USBD_Userdata[classes] = fops;
	USBD_Data[classes] = NULL;
	classes++;
	
  return status;
}


/**
  * @brief  usbd_composite_Init
  *         DeInitialize the TEMPLATE layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  usbd_composite_DeInit (USBD_HandleTypeDef *pdev, 
                                 uint8_t cfgidx)
{
	// printf("%s cfgidx: %d\r\n", __func__, cfgidx);

  return USBD_OK;
}

/**
  * @brief  usbd_composite_Setup
  *         Handle the TEMPLATE specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t  usbd_composite_Setup (USBD_HandleTypeDef *pdev, 
                                USBD_SetupReqTypedef *req)
{
	// printf("%s\r\n", __func__);
 
  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {
  case USB_REQ_TYPE_CLASS :  
    switch (req->bRequest)
    {
      
    default:
      USBD_CtlError (pdev, req);
      return USBD_FAIL; 
    }
    break;
    
  case USB_REQ_TYPE_STANDARD:
    switch (req->bRequest)
    {
    
    default:
      USBD_CtlError (pdev, req);
      return USBD_FAIL;     
    }
  }
  return USBD_OK;
}


/**
  * @brief  usbd_composite_GetCfgDesc 
  *         return configuration descriptor
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *usbd_composite_GetCfgDesc (uint16_t *length)
{	
	// printf("%s\r\n", __func__);
	if( usbd_composite_CfgDesc == NULL ){
		uint8_t* ptr = NULL;
		uint8_t* pCfg = NULL;
		usbd_composite_CfgDesc_len = USB_COMPOSITE_CONFIG_DESC_SIZ + USB_MSC_CONFIG_DESC_SIZ + USB_CDC_CONFIG_DESC_SIZ;
		usbd_composite_CfgDesc = (uint8_t*) malloc(usbd_composite_CfgDesc_len);
		ptr = usbd_composite_CfgDesc;
		/* add base descriptor */
		memcpy(ptr, usbd_base_CfgDesc, USB_COMPOSITE_CONFIG_DESC_SIZ);
		
		ptr += USB_COMPOSITE_CONFIG_DESC_SIZ;
		uint16_t size = 0;
		
		pCfg = MSC_GetCfgDesc(&size);
		memcpy(ptr, pCfg, size);
		ptr += size;
		
		size = 0;
		pCfg = NULL;
		pCfg = CDC_GetCfgDesc(&size);
		memcpy(ptr, pCfg, size);
		ptr+=size;
		
		// printf("Length: %d Actual: %d\r\n", usbd_composite_CfgDesc_len, (ptr - usbd_composite_CfgDesc));
		
	}
	
  *length = usbd_composite_CfgDesc_len;
  return usbd_composite_CfgDesc;
}

/**
* @brief  DeviceQualifierDescriptor 
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t  *usbd_composite_DeviceQualifierDescriptor (uint16_t *length)
{
  *length = sizeof (usbd_composite_DeviceQualifierDesc);
  return usbd_composite_DeviceQualifierDesc;
}


/**
  * @brief  usbd_composite_DataIn
  *         handle data IN Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  usbd_composite_DataIn (USBD_HandleTypeDef *pdev, 
                              uint8_t epnum)
{
	// printf("%s epnum: %d\r\n", __func__, epnum);

  return USBD_OK;
}

/**
  * @brief  usbd_composite_EP0_RxReady
  *         handle EP0 Rx Ready event
  * @param  pdev: device instance
  * @retval status
  */
static uint8_t  usbd_composite_EP0_RxReady (USBD_HandleTypeDef *pdev)
{
	// printf("%s\r\n", __func__);

  return USBD_OK;
}
/**
  * @brief  usbd_composite_EP0_TxReady
  *         handle EP0 TRx Ready event
  * @param  pdev: device instance
  * @retval status
  */
static uint8_t  usbd_composite_EP0_TxReady (USBD_HandleTypeDef *pdev)
{
	// printf("%s\r\n", __func__);

  return USBD_OK;
}
/**
  * @brief  usbd_composite_SOF
  *         handle SOF event
  * @param  pdev: device instance
  * @retval status
  */
static uint8_t  usbd_composite_SOF (USBD_HandleTypeDef *pdev)
{

	// printf("%s\r\n", __func__);
  return USBD_OK;
}
/**
  * @brief  usbd_composite_IsoINIncomplete
  *         handle data ISO IN Incomplete event
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  usbd_composite_IsoINIncomplete (USBD_HandleTypeDef *pdev, uint8_t epnum)
{
	// printf("%s epnum: %d\r\n", __func__, epnum);

  return USBD_OK;
}
/**
  * @brief  usbd_composite_IsoOutIncomplete
  *         handle data ISO OUT Incomplete event
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  usbd_composite_IsoOutIncomplete (USBD_HandleTypeDef *pdev, uint8_t epnum)
{

	// printf("%s epnum: %d\r\n", __func__, epnum);
  return USBD_OK;
}
/**
  * @brief  usbd_composite_DataOut
  *         handle data OUT Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  usbd_composite_DataOut (USBD_HandleTypeDef *pdev, 
                              uint8_t epnum)
{
	// printf("%s epnum: %d\r\n", __func__, epnum);

  return USBD_OK;
}

/**
* @brief  DeviceQualifierDescriptor 
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t  *usbd_composite_GetDeviceQualifierDesc (uint16_t *length)
{
  *length = sizeof (usbd_composite_DeviceQualifierDesc);
  return usbd_composite_DeviceQualifierDesc;
}

/**
  * @}
  */ 


/**
  * @}
  */ 


/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
