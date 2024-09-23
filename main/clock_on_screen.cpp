#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "wifi_setup.h"
#include "sntp_setup.h"
#include "DFRobot_LCD.h"

static const char *TAG = "Sys-Time";

extern "C" void app_main(void)
{

    /* initialize LCD */
    DFRobot_LCD lcd(16,2);
    lcd.init();

    /* initialize wifi from station AP example */
    initialize_wifi();

    /* synchronize time */
    sync_time();

    /* set locale */
    setenv("TZ", "PST8PDT,M3.2.0/2,M11.1.0/2",1);
    tzset();


    while(1) {

        /* declare sys-time stuff */
        time_t now;
        char strftime_buf[16];
        struct tm timeinfo;

        time(&now);
        localtime_r(&now,&timeinfo);

        strftime(strftime_buf, sizeof(strftime_buf), "%I:%M:%S %p", &timeinfo);

        /* send to serial */
        ESP_LOGI(TAG, "The current date/time locally is %s", strftime_buf);

        /* send to LCD */
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.printstr(strftime_buf);

        vTaskDelay(1000 / portTICK_PERIOD_MS);

    }

}
