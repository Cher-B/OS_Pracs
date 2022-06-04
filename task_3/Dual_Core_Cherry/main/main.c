#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_log.h"

#define core_0 0
#define core_1 1

#define PIN 2

void blink_led_core_1()
{
    // Select GPIO pin
    gpio_pad_select_gpio(PIN);
    
    // set PIN 2 as output
    gpio_set_direction(PIN, GPIO_MODE_OUTPUT);

    // Initialize the signal
    int isON = 0;

    while (true)
    { // Set the output as signal isON
        gpio_set_level(PIN, isON);
        // A delay of 1 second
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
        printf("Turning the LED");
        isON == true ? printf("ON") : printf("OFF");
        // change the value of signal
        isON = !isON;
        fflush(stdout);
    }
    
}

void hello_task_core_0()
{
    while (1)
    { 
        printf("Hello world from core %d!\n", xPortGetCoreID());
        fflush(stdout);
    }
}

void app_main()
{ // init nvs flash storage
    nvs_flash_init();
    // Create task1
    xTaskCreatePinnedToCore(&hello_task_core_0, "core0_task", 1024 * 4, NULL, configMAX_PRIORITIES - 1, NULL, core_0);
    // Create task2
    xTaskCreatePinnedToCore(&blink_led_core_1, "core1_task", 1024 * 4, NULL, configMAX_PRIORITIES - 1, NULL, core_1);
}