#include <nvs.h>

class NonVolatileConfig {
    public:
        NonVolatileConfig() {};
        ~NonVolatileConfig() {
            if (wifiSSID != NULL) {
                free(wifiSSID);
            }
            if (wifiPassword != NULL) {
                free(wifiPassword);
            }
        };
        esp_err_t loadNonvolatileConfiguration();

        char *getWifiSSID() {
            return wifiSSID;
        };

        char *getWifiPassword() {
            return wifiPassword;
        };

        bool isWifiConfigured() {
            return wifiConfigured;
        }

    private:
        esp_err_t __espret__;

        bool wifiConfigured;
        char *wifiSSID = NULL;
        char *wifiPassword = NULL;
};
