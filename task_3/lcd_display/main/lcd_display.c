#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "HD44780.h"
#include "nvs_flash.h"

#define core_0 0
#define core_1 1

#define LCD_ADDR 0x27
#define SDA_PIN 21
#define SCL_PIN 22
#define LCD_COLS 16
#define LCD_ROWS 2

void display_text(void *pvParameter)
{
    char buff[] = "Hello";
    while (true)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        LCD_clearScreen();
        LCD_home();
        LCD_writeStr(buff);
    }
}
void hello_task_core_0(void *pvParameter)
{
    while (1)
    { // Print hello world with a delay
        printf("Hello world from core %d!\n", xPortGetCoreID());
        vTaskDelay(1323 / portTICK_PERIOD_MS);
        // clear (or flush) the output buffer and move the buffered data to console
        fflush(stdout);
    }
}

void app_main()
{ // init nvs flash storage
    nvs_flash_init();
    // Create task1
    xTaskCreatePinnedToCore(&hello_task_core_0, "hello_world", 1024 * 4, NULL, configMAX_PRIORITIES - 1, NULL, core_0);
    // Create task2
    xTaskCreatePinnedToCore(&display_text, "lcd_display", configMINIMAL_STACK_SIZE * 4, NULL, configMAX_PRIORITIES - 1, NULL, core_1);
}