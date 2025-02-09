#include "gpio.h"
#include "icache.h"
#include "tx_api.h"

#define THREAD_STACK_SIZE 1024

uint8_t my_thread_stack[THREAD_STACK_SIZE];
TX_THREAD my_thread;

extern void SystemClock_Config(void);

VOID my_thread_entry(ULONG initial_input);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_ICACHE_Init();

    tx_kernel_enter();

    while (1);
}

VOID tx_application_define(VOID *first_unused_memory)
{
  tx_thread_create(&my_thread, "My Thread",
  my_thread_entry, 0x1234, my_thread_stack, THREAD_STACK_SIZE,
  3, 3, TX_NO_TIME_SLICE, TX_AUTO_START);
}

VOID my_thread_entry(ULONG initial_input)
{
  while(1)
  {
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
    HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
    tx_thread_sleep(50);
  }
}