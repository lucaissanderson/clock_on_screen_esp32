#include <stdio.h>
#include <sys/time.h>
#include <esp_log.h>
#include <esp_sntp.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

static const char *TAG = "SNTP";

// callback function after sync
void time_sync_notification_cb(struct timeval *tv) 
{
    ESP_LOGI(TAG,"Time synchronized");
}

void initialize_sntp()
{
    ESP_LOGI(TAG, "Initialize SNTP");

    esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
    esp_sntp_setservername(0, "pool.ntp.org");
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);
    esp_sntp_init();
}

void sync_time()
{
    initialize_sntp();

    while(sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET) {
        ESP_LOGI(TAG, "Waiting for time to synchronize...");
	vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}
