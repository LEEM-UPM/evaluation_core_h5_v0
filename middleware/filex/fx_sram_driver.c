/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** FileX Component                                                       */
/**                                                                       */
/** SRAM Disk Driver                                                      */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#include "fx_sram_driver.h"

VOID fx_sram_driver(FX_MEDIA *media_ptr)
{
    UCHAR *source_buffer;
    UCHAR *destination_buffer;
    UINT bytes_per_sector;

    switch (media_ptr->fx_media_driver_request)
    {
        case FX_DRIVER_INIT:
        {
            media_ptr->fx_media_driver_status = FX_SUCCESS;
            break;
        }

        case FX_DRIVER_UNINIT:
        {
            media_ptr->fx_media_driver_status = FX_SUCCESS;
            break;
        }

        case FX_DRIVER_READ:
        {
            source_buffer = ((UCHAR *)media_ptr->fx_media_driver_info) +
                            ((media_ptr->fx_media_driver_logical_sector + media_ptr->fx_media_hidden_sectors) * media_ptr->fx_media_bytes_per_sector);

            _fx_utility_memory_copy(source_buffer, media_ptr->fx_media_driver_buffer,
                                    media_ptr->fx_media_driver_sectors * media_ptr->fx_media_bytes_per_sector);

            media_ptr->fx_media_driver_status = FX_SUCCESS;
            break;
        }

        case FX_DRIVER_WRITE:
        {
            destination_buffer = ((UCHAR *)media_ptr->fx_media_driver_info) +
                                 ((media_ptr->fx_media_driver_logical_sector + media_ptr->fx_media_hidden_sectors) * media_ptr->fx_media_bytes_per_sector);

            _fx_utility_memory_copy(media_ptr->fx_media_driver_buffer, destination_buffer,
                                    media_ptr->fx_media_driver_sectors * media_ptr->fx_media_bytes_per_sector);

            media_ptr->fx_media_driver_status = FX_SUCCESS;
            break;
        }

        case FX_DRIVER_FLUSH:
        {
            media_ptr->fx_media_driver_status = FX_SUCCESS;
            break;
        }

        case FX_DRIVER_ABORT:
        {
            media_ptr->fx_media_driver_status = FX_SUCCESS;
            break;
        }

        case FX_DRIVER_BOOT_READ:
        {
            source_buffer = (UCHAR *)media_ptr->fx_media_driver_info;

            bytes_per_sector = _fx_utility_16_unsigned_read(&source_buffer[FX_BYTES_SECTOR]);

            if (bytes_per_sector > media_ptr->fx_media_memory_size)
            {
                media_ptr->fx_media_driver_status = FX_BUFFER_ERROR;
                break;
            }

            _fx_utility_memory_copy(source_buffer, media_ptr->fx_media_driver_buffer,
                                    bytes_per_sector);

            media_ptr->fx_media_driver_status = FX_SUCCESS;
            break;
        }

        case FX_DRIVER_BOOT_WRITE:
        {
            destination_buffer = (UCHAR *)media_ptr->fx_media_driver_info;

            _fx_utility_memory_copy(media_ptr->fx_media_driver_buffer, destination_buffer,
                                    media_ptr->fx_media_bytes_per_sector);

            media_ptr->fx_media_driver_status = FX_SUCCESS;
            break;
        }

        default:
        {
            media_ptr->fx_media_driver_status = FX_IO_ERROR;
            break;
        }
    }
}
