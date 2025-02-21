#include "gpio.h"
#include "icache.h"
#include "usart.h"
#include "fx_api.h"
#include "fx_sram_driver.h"

#define THREAD_STACK_SIZE 2048U
#define SECTOR_SIZE       512U
#define TOTAL_SECTORS     64U
#define FX_SRAM_DISK_SIZE (SECTOR_SIZE * TOTAL_SECTORS)

TX_THREAD my_thread;
UCHAR my_thread_stack[THREAD_STACK_SIZE];

VOID my_thread_entry(ULONG thread_input);

FX_MEDIA ram_disk;
UCHAR media_memory[SECTOR_SIZE];
UCHAR sram_disk_memory[FX_SRAM_DISK_SIZE];

FX_FILE my_file;

extern void SystemClock_Config(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_ICACHE_Init();
    MX_UART4_Init();

    tx_kernel_enter();

    while(1);
    {
        HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
        HAL_Delay(1000);
    }
}

VOID tx_application_define(VOID *first_unused_memory)
{
    tx_thread_create(&my_thread, "My Thread",
                     my_thread_entry, 0, my_thread_stack, THREAD_STACK_SIZE,
                     1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);

    fx_system_initialize();
}

VOID my_thread_entry(ULONG thread_input)
{
    UINT status;
    ULONG actual;
    CHAR local_buffer[30] = {"ERROR\n"};

    fx_media_format(&ram_disk,
                    fx_sram_driver,               // Driver entry
                    sram_disk_memory,             // RAM disk memory pointer
                    media_memory,                 // Media buffer pointer
                    sizeof(media_memory),         // Media buffer size
                    "MY_RAM_DISK",                // Volume Name
                    1,                            // Number of FATs
                    32,                           // Directory Entries
                    0,                            // Hidden sectors
                    TOTAL_SECTORS,                // Total sectors
                    SECTOR_SIZE,                  // Sector size
                    8,                            // Sectors per cluster
                    1,                            // Heads
                    1);                           // Sectors per track

    do
    {
        if (fx_media_open(&ram_disk, "MY_RAM_DISK", fx_sram_driver, sram_disk_memory, media_memory, sizeof(media_memory)) != FX_SUCCESS)
        {
            break;
        }

        status = fx_file_create(&ram_disk, "TEST.TXT");
        if (status != FX_SUCCESS && status != FX_ALREADY_CREATED)
        {
            break;
        }

        if (fx_file_open(&ram_disk, &my_file, "TEST.TXT", FX_OPEN_FOR_WRITE) != FX_SUCCESS)
        {
            break;
        }

        if (fx_file_seek(&my_file, 0) != FX_SUCCESS)
        {
            break;
        }

        if (fx_file_write(&my_file, "JOSE\r\n", 5) != FX_SUCCESS)
        {
            break;
        }

        if (fx_file_seek(&my_file, 0) != FX_SUCCESS)
        {
            break;
        }

        status = fx_file_read(&my_file, local_buffer, 5, &actual);
        if ((status != FX_SUCCESS) || (actual != 5))
        {
            break;
        }

        if (HAL_UART_Transmit(&huart4, local_buffer, 6, HAL_MAX_DELAY) != HAL_OK)
        {
            break;
        }

        if (fx_file_close(&my_file) != FX_SUCCESS)
        {
            break;
        }

        if (fx_media_close(&ram_disk) != FX_SUCCESS)
        {
            break;
        }

        tx_thread_sleep(100);
    } while (1);

    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);

    return;
}
