#include "usb.h"
#include "ux_api.h"
#include "ux_device_cdc_acm.h"
#include "ux_device_descriptors.h"
#include "ux_dcd_stm32.h"

#define USBX_DEVICE_MEMORY_STACK_SIZE      10*1024
#define UX_DEVICE_APP_THREAD_STACK_SIZE    1024
#define UX_CDC_ACM_WRITE_THREAD_STACK_SIZE 1024

static ULONG cdc_acm_interface_number;
static ULONG cdc_acm_configuration_number;
static UX_SLAVE_CLASS_CDC_ACM_PARAMETER cdc_acm_parameter;
static TX_THREAD ux_device_app_thread;

static TX_THREAD ux_cdc_write_thread;
TX_SEMAPHORE semaphore;
// stack for usbx memory
UCHAR usbx_device_memory_stack[USBX_DEVICE_MEMORY_STACK_SIZE];
// stack for the device application main thread
UCHAR ux_device_app_thread_stack[UX_DEVICE_APP_THREAD_STACK_SIZE];
// stack for usbx cdc acm write thread
UCHAR ux_cdc_acm_write_thread_stack[UX_CDC_ACM_WRITE_THREAD_STACK_SIZE];

static VOID app_ux_device_thread_entry(ULONG thread_input);
static UINT usbx_device_init(VOID);
extern void SystemClock_Config(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_ICACHE_Init();
    
    tx_kernel_enter();

    while(1)
    {
        HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
        HAL_Delay(1000);
    }
}

VOID tx_application_define(VOID *first_unused_memory)
{
    TX_PARAMETER_NOT_USED(first_unused_memory);

    if (usbx_device_init() != UX_SUCCESS)
    {
        while (1);
    }
}

UINT usbx_device_init(VOID)
{
  UCHAR *device_framework_high_speed;
  UCHAR *device_framework_full_speed;
  ULONG device_framework_hs_length;
  ULONG device_framework_fs_length;
  ULONG string_framework_length;
  ULONG language_id_framework_length;
  UCHAR *string_framework;
  UCHAR *language_id_framework;

  if (ux_system_initialize(usbx_device_memory_stack, USBX_DEVICE_MEMORY_STACK_SIZE, UX_NULL, 0) != UX_SUCCESS)
  {
    return UX_ERROR;
  }

  device_framework_high_speed = USBD_Get_Device_Framework_Speed(USBD_HIGH_SPEED,
                                                                &device_framework_hs_length);

  device_framework_full_speed = USBD_Get_Device_Framework_Speed(USBD_FULL_SPEED,
                                                                &device_framework_fs_length);

  string_framework = USBD_Get_String_Framework(&string_framework_length);

  language_id_framework = USBD_Get_Language_Id_Framework(&language_id_framework_length);

  if (ux_device_stack_initialize(device_framework_high_speed,
                                 device_framework_hs_length,
                                 device_framework_full_speed,
                                 device_framework_fs_length,
                                 string_framework,
                                 string_framework_length,
                                 language_id_framework,
                                 language_id_framework_length,
                                 UX_NULL) != UX_SUCCESS)
  {
    return UX_ERROR;
  }

  // Initialize the cdc acm class parameters for the device
  cdc_acm_parameter.ux_slave_class_cdc_acm_instance_activate   = USBD_CDC_ACM_Activate;
  cdc_acm_parameter.ux_slave_class_cdc_acm_instance_deactivate = USBD_CDC_ACM_Deactivate;
  cdc_acm_parameter.ux_slave_class_cdc_acm_parameter_change    = USBD_CDC_ACM_ParameterChange;

  cdc_acm_configuration_number = USBD_Get_Configuration_Number(CLASS_TYPE_CDC_ACM, 0);

  cdc_acm_interface_number = USBD_Get_Interface_Number(CLASS_TYPE_CDC_ACM, 0);

  if (ux_device_stack_class_register(_ux_system_slave_class_cdc_acm_name,
                                     ux_device_class_cdc_acm_entry,
                                     cdc_acm_configuration_number,
                                     cdc_acm_interface_number,
                                     &cdc_acm_parameter) != UX_SUCCESS)
  {
    return UX_ERROR;
  }

  // Create the device application main thread
  if (tx_thread_create(&ux_device_app_thread, "USBX Device App Main Thread", app_ux_device_thread_entry,
                       0, ux_device_app_thread_stack, UX_DEVICE_APP_THREAD_STACK_SIZE, 10,
                       10, TX_NO_TIME_SLICE,
                       TX_AUTO_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

  // Create semaphore to signal user push-button press
  tx_semaphore_create(&semaphore, "semaphore", 1);

  if (tx_thread_create(&ux_cdc_write_thread, "cdc_acm_write_usbx_app_thread_entry",
                       usbx_cdc_acm_write_thread_entry, 1, ux_cdc_acm_write_thread_stack,
                       UX_CDC_ACM_WRITE_THREAD_STACK_SIZE, 9, 9, TX_NO_TIME_SLICE,
                       TX_AUTO_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

  return UX_SUCCESS;
}

static VOID app_ux_device_thread_entry(ULONG thread_input)
{
  TX_PARAMETER_NOT_USED(thread_input);

  HAL_PWREx_EnableVddUSB();

  MX_USB_PCD_Init();

  // USB packet memory area configuration
  HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x00, PCD_SNG_BUF, 0x14);
  HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x80, PCD_SNG_BUF, 0x54);
  HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, USBD_CDCACM_EPOUT_ADDR, PCD_SNG_BUF, 0x94);
  HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, USBD_CDCACM_EPIN_ADDR, PCD_SNG_BUF, 0x98);
  HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, USBD_CDCACM_EPINCMD_ADDR, PCD_SNG_BUF, 0x9C);

  // Initialize the device controller driver
  ux_dcd_stm32_initialize((ULONG)USB_DRD_FS, (ULONG)&hpcd_USB_DRD_FS);

  // Start device USB
  HAL_PCD_Start(&hpcd_USB_DRD_FS);

  while(1);
}

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == USER_BUTTON_Pin)
  {
    tx_semaphore_put(&semaphore);
  }
}
