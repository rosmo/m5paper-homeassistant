/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"

// App specific
#include "nv_config.hpp"
#include "application.hpp"

NonVolatileConfig nvConfig;
HelloWorldApplication app;
SemaphoreHandle_t applicationFinished = NULL;

void run_application(void *pvParameters) { 
    app.init();
    app.setup();
    app.run();
    if (applicationFinished != NULL) {
        printf("Application finished, releasing mutex...\n");
        xSemaphoreGive(applicationFinished);
    }
}

extern "C" void app_main(void) {
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), WiFi%s%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }

    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());

    // Load configuration from non-volatile storage
    nvConfig.loadNonvolatileConfiguration();
    if (nvConfig.isWifiConfigured()) {
        printf("Wifi is configured, SSID=%s\n", nvConfig.getWifiSSID());
    } else {
        printf("Wifi is not configured.\n");
    }

    // M5 specific stuff
    printf("Start M5\n");
    // M5.begin(false, false, true, true, false);
    // M5.EPD.SetRotation(90);

    
    // Create mutex for application
    // Semaphore is created as taken
    applicationFinished = xSemaphoreCreateBinary();

    // Create application task on core 0
    xTaskCreatePinnedToCore(run_application, "application", 4096, NULL, 1, NULL, 0);

    // Wait until task signals exit via semaphore
    xSemaphoreTake(applicationFinished, portMAX_DELAY); 

    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}