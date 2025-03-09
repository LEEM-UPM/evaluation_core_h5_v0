/**
  ******************************************************************************
  * @file    ux_device_cdc_acm.c
  * @author  MCD Application Team
  * @brief   USBX Device applicative file
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

#include "ux_device_cdc_acm.h"
#include "main.h"
#include "string.h"

UX_SLAVE_CLASS_CDC_ACM *cdc_acm;

UX_SLAVE_CLASS_CDC_ACM_LINE_CODING_PARAMETER CDC_VCP_LineCoding =
{
  115200, // baud rate
  0x00,   // stop bits 1
  0x00,   // parity none
  0x08    // n of bits 8
};

const char Tx_Buffer[] = "Hello World\r\n";

extern TX_SEMAPHORE semaphore;

/**
  * @brief  USBD_CDC_ACM_Activate
  *         This function is called when insertion of a CDC ACM device.
  * @param  cdc_acm_instance: Pointer to the cdc acm class instance.
  * @retval none
  */
VOID USBD_CDC_ACM_Activate(VOID *cdc_acm_instance)
{
  // Save the CDC instance
  cdc_acm = (UX_SLAVE_CLASS_CDC_ACM*) cdc_acm_instance;

  // Set the device class_cdc_acm with default parameters
  if (ux_device_class_cdc_acm_ioctl(cdc_acm, UX_SLAVE_CLASS_CDC_ACM_IOCTL_SET_LINE_CODING,
                                    &CDC_VCP_LineCoding) != UX_SUCCESS)
  {
    Error_Handler();
  }

  return;
}

/**
  * @brief  USBD_CDC_ACM_Deactivate
  *         This function is called when extraction of a CDC ACM device.
  * @param  cdc_acm_instance: Pointer to the cdc acm class instance.
  * @retval none
  */
VOID USBD_CDC_ACM_Deactivate(VOID *cdc_acm_instance)
{
  UX_PARAMETER_NOT_USED(cdc_acm_instance);

  return;
}

/**
  * @brief  USBD_CDC_ACM_ParameterChange
  *         This function is invoked to manage the CDC ACM class requests.
  * @param  cdc_acm_instance: Pointer to the cdc acm class instance.
  * @retval none
  */
VOID USBD_CDC_ACM_ParameterChange(VOID *cdc_acm_instance)
{
  UX_PARAMETER_NOT_USED(cdc_acm_instance);

  ULONG request;
  UX_SLAVE_TRANSFER *transfer_request;
  UX_SLAVE_DEVICE *device;

  // Get the pointer to the device
  device = &_ux_system_slave->ux_system_slave_device;

  // Get the pointer to the transfer request associated with the control endpoint
  transfer_request = &device->ux_slave_device_control_endpoint.ux_slave_endpoint_transfer_request;

  request = *(transfer_request->ux_slave_transfer_request_setup + UX_SETUP_REQUEST);

  switch (request)
  {
    case UX_SLAVE_CLASS_CDC_ACM_GET_LINE_CODING:
      // Get the line coding parameters
      if (ux_device_class_cdc_acm_ioctl(cdc_acm, UX_SLAVE_CLASS_CDC_ACM_IOCTL_GET_LINE_CODING,
                                        &CDC_VCP_LineCoding) != UX_SUCCESS)
      {
        Error_Handler();
      }
      break;

    case UX_SLAVE_CLASS_CDC_ACM_SET_LINE_CODING:
      if (ux_device_class_cdc_acm_ioctl(cdc_acm, UX_SLAVE_CLASS_CDC_ACM_IOCTL_SET_LINE_CODING,
                                        &CDC_VCP_LineCoding) != UX_SUCCESS)
      {
        Error_Handler();
      } 
      break;
    
    case UX_SLAVE_CLASS_CDC_ACM_SET_CONTROL_LINE_STATE:
    default:
      break;
  }

  return;
}

VOID usbx_cdc_acm_write_thread_entry(ULONG thread_input)
{
  UX_PARAMETER_NOT_USED(thread_input);
  ULONG actual_length;

  // Wait for semaphore then transmit message on USB
  while (1)
  {
    tx_semaphore_get(&semaphore, TX_WAIT_FOREVER);

    ux_device_class_cdc_acm_write(cdc_acm, (UCHAR *)(&Tx_Buffer), strlen(Tx_Buffer), &actual_length);
  }
}
