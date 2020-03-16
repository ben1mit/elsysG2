#include "esp_vfs_fat.h"
#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"
#include <stdio.h>

#include "sdcard.h"

esp_err_t sdcard_mount()
{
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();

    sdspi_slot_config_t slot_cfg = SDSPI_SLOT_CONFIG_DEFAULT();
    slot_cfg.gpio_miso = PIN_NUM_MISO;
    slot_cfg.gpio_mosi = PIN_NUM_MOSI;
    slot_cfg.gpio_sck  = PIN_NUM_CLK;
    slot_cfg.gpio_cs   = PIN_NUM_CS;

    esp_vfs_fat_sdmmc_mount_config_t mount_cfg = {
        .format_if_mount_failed = 0,
        .max_files = 5,
        .allocation_unit_size = 0
    };

    sdmmc_card_t* card;
    esp_err_t err = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_cfg, &mount_cfg, &card);

    if(err != ESP_OK)
    {
    	printf("Failed to mount sdcard\n");
    	return err;
    }
    sdmmc_card_print_info(stdout, card);

    return ESP_OK;
}

void sdcard_unmount()
{
	esp_vfs_fat_sdmmc_unmount();
}
