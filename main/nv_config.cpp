#include <string.h>
#include "nv_config.hpp"

#define NVS_CHECK(x)              \
    __espret__ = x;           \
    if (__espret__ != ESP_OK) \
    {                         \
        nvs_close(nvs_arg);   \
        return __espret__;    \
    }

esp_err_t NonVolatileConfig::loadNonvolatileConfiguration() {
    nvs_handle nvs_arg = (nvs_handle)0;
    char buf[128];
    size_t length = sizeof(buf) / sizeof(char);
    
    NVS_CHECK(nvs_open("Setting", NVS_READONLY, &nvs_arg));
    
    NVS_CHECK(nvs_get_str(nvs_arg, "ssid", buf, &length));
    wifiSSID = strdup(buf);

    length = sizeof(buf) / sizeof(char);
    NVS_CHECK(nvs_get_str(nvs_arg, "pswd", buf, &length));
    wifiPassword = strdup(buf);

    wifiConfigured = true;

    nvs_close(nvs_arg);
    return ESP_OK;
}