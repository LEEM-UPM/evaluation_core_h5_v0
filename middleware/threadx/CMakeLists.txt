cmake_minimum_required(VERSION 3.22)

project(threadx)
add_library(threadx INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(threadx INTERFACE 
	TX_INCLUDE_USER_DEFINE_FILE 
	TX_SINGLE_MODE_NON_SECURE=1 
)

target_include_directories(threadx INTERFACE
    common/inc
    ports/cortex_m33/gnu/inc
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(threadx INTERFACE
    common/src/tx_initialize_high_level.c
    common/src/tx_initialize_kernel_enter.c
    common/src/tx_initialize_kernel_setup.c
    common/src/tx_thread_stack_error_handler.c
    common/src/tx_thread_stack_error_notify.c
    common/src/tx_thread_system_resume.c
    common/src/tx_block_allocate.c
    common/src/tx_block_pool_cleanup.c
    common/src/tx_block_pool_create.c
    common/src/tx_block_pool_delete.c
    common/src/tx_block_pool_info_get.c
    common/src/tx_block_pool_initialize.c
    common/src/tx_block_pool_prioritize.c
    common/src/tx_block_release.c
    common/src/tx_byte_allocate.c
    common/src/tx_byte_pool_cleanup.c
    common/src/tx_byte_pool_create.c
    common/src/tx_byte_pool_delete.c
    common/src/tx_byte_pool_info_get.c
    common/src/tx_byte_pool_initialize.c
    common/src/tx_byte_pool_prioritize.c
    common/src/tx_byte_pool_search.c
    common/src/tx_byte_release.c
    common/src/tx_event_flags_cleanup.c
    common/src/tx_event_flags_create.c
    common/src/tx_event_flags_delete.c
    common/src/tx_event_flags_get.c
    common/src/tx_event_flags_info_get.c
    common/src/tx_event_flags_initialize.c
    common/src/tx_event_flags_set.c
    common/src/tx_event_flags_set_notify.c
    common/src/tx_mutex_cleanup.c
    common/src/tx_mutex_create.c
    common/src/tx_mutex_delete.c
    common/src/tx_mutex_get.c
    common/src/tx_mutex_info_get.c
    common/src/tx_mutex_initialize.c
    common/src/tx_mutex_prioritize.c
    common/src/tx_mutex_priority_change.c
    common/src/tx_mutex_put.c
    common/src/tx_queue_cleanup.c
    common/src/tx_queue_create.c
    common/src/tx_queue_delete.c
    common/src/tx_queue_flush.c
    common/src/tx_queue_front_send.c
    common/src/tx_queue_info_get.c
    common/src/tx_queue_initialize.c
    common/src/tx_queue_prioritize.c
    common/src/tx_queue_receive.c
    common/src/tx_queue_send.c
    common/src/tx_queue_send_notify.c
    common/src/tx_semaphore_ceiling_put.c
    common/src/tx_semaphore_cleanup.c
    common/src/tx_semaphore_create.c
    common/src/tx_semaphore_delete.c
    common/src/tx_semaphore_get.c
    common/src/tx_semaphore_info_get.c
    common/src/tx_semaphore_initialize.c
    common/src/tx_semaphore_prioritize.c
    common/src/tx_semaphore_put.c
    common/src/tx_semaphore_put_notify.c
    common/src/tx_thread_create.c
    common/src/tx_thread_delete.c
    common/src/tx_thread_entry_exit_notify.c
    common/src/tx_thread_identify.c
    common/src/tx_thread_info_get.c
    common/src/tx_thread_initialize.c
    common/src/tx_thread_preemption_change.c
    common/src/tx_thread_priority_change.c
    common/src/tx_thread_relinquish.c
    common/src/tx_thread_reset.c
    common/src/tx_thread_resume.c
    common/src/tx_thread_shell_entry.c
    common/src/tx_thread_sleep.c
    common/src/tx_thread_stack_analyze.c
    common/src/tx_thread_suspend.c
    common/src/tx_thread_system_preempt_check.c
    common/src/tx_thread_system_suspend.c
    common/src/tx_thread_terminate.c
    common/src/tx_thread_time_slice.c
    common/src/tx_thread_time_slice_change.c
    common/src/tx_thread_timeout.c
    common/src/tx_thread_wait_abort.c
    common/src/tx_time_get.c
    common/src/tx_time_set.c
    common/src/txe_block_allocate.c
    common/src/txe_block_pool_create.c
    common/src/txe_block_pool_delete.c
    common/src/txe_block_pool_info_get.c
    common/src/txe_block_pool_prioritize.c
    common/src/txe_block_release.c
    common/src/txe_byte_allocate.c
    common/src/txe_byte_pool_create.c
    common/src/txe_byte_pool_delete.c
    common/src/txe_byte_pool_info_get.c
    common/src/txe_byte_pool_prioritize.c
    common/src/txe_byte_release.c
    common/src/txe_event_flags_create.c
    common/src/txe_event_flags_delete.c
    common/src/txe_event_flags_get.c
    common/src/txe_event_flags_info_get.c
    common/src/txe_event_flags_set.c
    common/src/txe_event_flags_set_notify.c
    common/src/txe_mutex_create.c
    common/src/txe_mutex_delete.c
    common/src/txe_mutex_get.c
    common/src/txe_mutex_info_get.c
    common/src/txe_mutex_prioritize.c
    common/src/txe_mutex_put.c
    common/src/txe_queue_create.c
    common/src/txe_queue_delete.c
    common/src/txe_queue_flush.c
    common/src/txe_queue_front_send.c
    common/src/txe_queue_info_get.c
    common/src/txe_queue_prioritize.c
    common/src/txe_queue_receive.c
    common/src/txe_queue_send.c
    common/src/txe_queue_send_notify.c
    common/src/txe_semaphore_ceiling_put.c
    common/src/txe_semaphore_create.c
    common/src/txe_semaphore_delete.c
    common/src/txe_semaphore_get.c
    common/src/txe_semaphore_info_get.c
    common/src/txe_semaphore_prioritize.c
    common/src/txe_semaphore_put.c
    common/src/txe_semaphore_put_notify.c
    common/src/txe_thread_create.c
    common/src/txe_thread_delete.c
    common/src/txe_thread_entry_exit_notify.c
    common/src/txe_thread_info_get.c
    common/src/txe_thread_preemption_change.c
    common/src/txe_thread_priority_change.c
    common/src/txe_thread_relinquish.c
    common/src/txe_thread_reset.c
    common/src/txe_thread_resume.c
    common/src/txe_thread_suspend.c
    common/src/txe_thread_terminate.c
    common/src/txe_thread_time_slice_change.c
    common/src/txe_thread_wait_abort.c
    common/src/tx_timer_activate.c
    common/src/tx_timer_change.c
    common/src/tx_timer_create.c
    common/src/tx_timer_deactivate.c
    common/src/tx_timer_delete.c
    common/src/tx_timer_expiration_process.c
    common/src/tx_timer_info_get.c
    common/src/tx_timer_initialize.c
    common/src/tx_timer_system_activate.c
    common/src/tx_timer_system_deactivate.c
    common/src/tx_timer_thread_entry.c
    common/src/txe_timer_activate.c
    common/src/txe_timer_change.c
    common/src/txe_timer_create.c
    common/src/txe_timer_deactivate.c
    common/src/txe_timer_delete.c
    common/src/txe_timer_info_get.c
    tx_initialize_low_level.S
    ports/cortex_m33/gnu/src/tx_thread_context_restore.S
    ports/cortex_m33/gnu/src/tx_thread_context_save.S
    ports/cortex_m33/gnu/src/tx_thread_interrupt_control.S
    ports/cortex_m33/gnu/src/tx_thread_interrupt_disable.S
    ports/cortex_m33/gnu/src/tx_thread_interrupt_restore.S
    ports/cortex_m33/gnu/src/tx_thread_schedule.S
    ports/cortex_m33/gnu/src/tx_thread_stack_build.S
    ports/cortex_m33/gnu/src/tx_thread_system_return.S
    ports/cortex_m33/gnu/src/tx_timer_interrupt.S
)

target_link_directories(threadx INTERFACE
)

target_link_libraries(threadx INTERFACE
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


