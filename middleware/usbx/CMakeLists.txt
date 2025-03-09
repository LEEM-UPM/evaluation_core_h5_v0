cmake_minimum_required(VERSION 3.22)

project(usbx)
add_library(usbx INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(usbx INTERFACE 
    UX_INCLUDE_USER_DEFINE_FILE
)

target_include_directories(usbx INTERFACE
    common/core/inc
    common/usbx_device_classes/inc
    common/usbx_stm32_device_controllers
    ports/generic/inc
    ../../app/hello_usbx_cdc_acm
# Threadx headers
    ../threadx/common/inc
    ../threadx/ports/cortex_m33/gnu/inc
)

target_sources(usbx INTERFACE
    common/usbx_stm32_device_controllers/ux_dcd_stm32_callback.c
    common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_create.c
    common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_destroy.c
    common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_reset.c
    common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_stall.c
    common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_status.c
    common/usbx_stm32_device_controllers/ux_dcd_stm32_frame_number_get.c
    common/usbx_stm32_device_controllers/ux_dcd_stm32_function.c
    common/usbx_stm32_device_controllers/ux_dcd_stm32_initialize.c
    common/usbx_stm32_device_controllers/ux_dcd_stm32_initialize_complete.c
    common/usbx_stm32_device_controllers/ux_dcd_stm32_interrupt_handler.c
    common/usbx_stm32_device_controllers/ux_dcd_stm32_transfer_abort.c
    common/usbx_stm32_device_controllers/ux_dcd_stm32_transfer_request.c
    common/usbx_stm32_device_controllers/ux_dcd_stm32_uninitialize.c
    common/core/src/ux_utility_debug_callback_register.c
    common/core/src/ux_utility_debug_log.c
    common/core/src/ux_utility_delay_ms.c
    common/core/src/ux_utility_descriptor_pack.c
    common/core/src/ux_utility_descriptor_parse.c
    common/core/src/ux_utility_error_callback_register.c
    common/core/src/ux_utility_event_flags_create.c
    common/core/src/ux_utility_event_flags_delete.c
    common/core/src/ux_utility_event_flags_get.c
    common/core/src/ux_utility_event_flags_set.c
    common/core/src/ux_utility_long_get.c
    common/core/src/ux_utility_long_get_big_endian.c
    common/core/src/ux_utility_long_put.c
    common/core/src/ux_utility_long_put_big_endian.c
    common/core/src/ux_utility_memory_allocate.c
    common/core/src/ux_utility_memory_allocate_add_safe.c
    common/core/src/ux_utility_memory_allocate_mulc_safe.c
    common/core/src/ux_utility_memory_allocate_mulv_safe.c
    common/core/src/ux_utility_memory_compare.c
    common/core/src/ux_utility_memory_copy.c
    common/core/src/ux_utility_memory_free.c
    common/core/src/ux_utility_memory_free_block_best_get.c
    common/core/src/ux_utility_memory_set.c
    common/core/src/ux_utility_mutex_create.c
    common/core/src/ux_utility_mutex_delete.c
    common/core/src/ux_utility_mutex_off.c
    common/core/src/ux_utility_mutex_on.c
    common/core/src/ux_utility_pci_class_scan.c
    common/core/src/ux_utility_pci_read.c
    common/core/src/ux_utility_pci_write.c
    common/core/src/ux_utility_physical_address.c
    common/core/src/ux_utility_semaphore_create.c
    common/core/src/ux_utility_semaphore_delete.c
    common/core/src/ux_utility_semaphore_get.c
    common/core/src/ux_utility_semaphore_put.c
    common/core/src/ux_utility_set_interrupt_handler.c
    common/core/src/ux_utility_short_get.c
    common/core/src/ux_utility_short_get_big_endian.c
    common/core/src/ux_utility_short_put.c
    common/core/src/ux_utility_short_put_big_endian.c
    common/core/src/ux_utility_string_length_check.c
    common/core/src/ux_utility_string_length_get.c
    common/core/src/ux_utility_string_to_unicode.c
    common/core/src/ux_utility_thread_create.c
    common/core/src/ux_utility_thread_delete.c
    common/core/src/ux_utility_thread_identify.c
    common/core/src/ux_utility_thread_relinquish.c
    common/core/src/ux_utility_thread_resume.c
    common/core/src/ux_utility_thread_schedule_other.c
    common/core/src/ux_utility_thread_sleep.c
    common/core/src/ux_utility_thread_suspend.c
    common/core/src/ux_utility_timer_create.c
    common/core/src/ux_utility_timer_delete.c
    common/core/src/ux_utility_unicode_to_string.c
    common/core/src/ux_utility_virtual_address.c
    common/core/src/ux_system_error_handler.c
    common/core/src/ux_system_initialize.c
    common/core/src/ux_system_uninitialize.c
    common/usbx_device_classes/src/ux_device_class_cdc_acm_activate.c
    common/usbx_device_classes/src/ux_device_class_cdc_acm_bulkin_thread.c
    common/usbx_device_classes/src/ux_device_class_cdc_acm_bulkout_thread.c
    common/usbx_device_classes/src/ux_device_class_cdc_acm_control_request.c
    common/usbx_device_classes/src/ux_device_class_cdc_acm_deactivate.c
    common/usbx_device_classes/src/ux_device_class_cdc_acm_entry.c
    common/usbx_device_classes/src/ux_device_class_cdc_acm_initialize.c
    common/usbx_device_classes/src/ux_device_class_cdc_acm_ioctl.c
    common/usbx_device_classes/src/ux_device_class_cdc_acm_read.c
    common/usbx_device_classes/src/ux_device_class_cdc_acm_unitialize.c
    common/usbx_device_classes/src/ux_device_class_cdc_acm_write.c
    common/usbx_device_classes/src/ux_device_class_cdc_acm_write_with_callback.c
    common/core/src/ux_device_stack_alternate_setting_get.c
    common/core/src/ux_device_stack_alternate_setting_set.c
    common/core/src/ux_device_stack_class_register.c
    common/core/src/ux_device_stack_class_unregister.c
    common/core/src/ux_device_stack_clear_feature.c
    common/core/src/ux_device_stack_configuration_get.c
    common/core/src/ux_device_stack_configuration_set.c
    common/core/src/ux_device_stack_control_request_process.c
    common/core/src/ux_device_stack_descriptor_send.c
    common/core/src/ux_device_stack_disconnect.c
    common/core/src/ux_device_stack_endpoint_stall.c
    common/core/src/ux_device_stack_get_status.c
    common/core/src/ux_device_stack_host_wakeup.c
    common/core/src/ux_device_stack_initialize.c
    common/core/src/ux_device_stack_interface_delete.c
    common/core/src/ux_device_stack_interface_get.c
    common/core/src/ux_device_stack_interface_set.c
    common/core/src/ux_device_stack_interface_start.c
    common/core/src/ux_device_stack_microsoft_extension_register.c
    common/core/src/ux_device_stack_set_feature.c
    common/core/src/ux_device_stack_transfer_abort.c
    common/core/src/ux_device_stack_transfer_all_request_abort.c
    common/core/src/ux_device_stack_transfer_request.c
    common/core/src/ux_device_stack_uninitialize.c

    ../../app/hello_usbx_cdc_acm
)

target_link_directories(usbx INTERFACE
)

target_link_libraries(usbx INTERFACE
    threadx
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()
