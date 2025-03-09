/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ux_device_cdc_acm.h
  * @author  MCD Application Team
  * @brief   USBX Device CDC ACM interface header file
  ******************************************************************************
    * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#ifndef __UX_DEVICE_CDC_ACM_H__
#define __UX_DEVICE_CDC_ACM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ux_api.h"
#include "ux_device_class_cdc_acm.h"

VOID USBD_CDC_ACM_Activate(VOID *cdc_acm_instance);
VOID USBD_CDC_ACM_Deactivate(VOID *cdc_acm_instance);
VOID USBD_CDC_ACM_ParameterChange(VOID *cdc_acm_instance);

VOID usbx_cdc_acm_write_thread_entry(ULONG thread_input);

#ifdef __cplusplus
}
#endif
#endif  /* __UX_DEVICE_CDC_ACM_H__ */
