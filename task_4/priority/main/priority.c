#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <esp_system.h>
#include "esp_log.h"

#define GPIO_NUM_15 15
#define GPIO_NUM_2 2

static const char *TAG = "LED STATUS";

SemaphoreHandle_t xMutex;

void LowPriority(void *arg)
{
    while (1)
    {
        xSemaphoreTake(xMutex, portMAX_DELAY);

        for (uint8_t i = 0; i < 10; i++)
        {
            ESP_LOGI(TAG, "Turning the LEDs on Low Priority %d", i);

            gpio_set_level(GPIO_NUM_2, 1);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            gpio_set_level(GPIO_NUM_2, 0);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
        xSemaphoreGive(xMutex);
    }
}
void HighPriority(void *arg)
{

    while (1)
    {
        xSemaphoreTake(xMutex, portMAX_DELAY);
        for (uint8_t i = 0; i < 10; i++)
        {
            ESP_LOGI(TAG, "Turning the LEDs on High Priority %d", i);
            gpio_set_level(GPIO_NUM_15, 1);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            gpio_set_level(GPIO_NUM_15, 0);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        xSemaphoreGive(xMutex);
        vTaskDelay(pdMS_TO_TICKS(400));
    }
}

void app_main()
{

    xMutex = xSemaphoreCreateMutex();

    esp_rom_gpio_pad_select_gpio(GPIO_NUM_15);
    gpio_set_direction(GPIO_NUM_15, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_15, 0);
    esp_rom_gpio_pad_select_gpio(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_2, 0);

    xTaskCreatePinnedToCore(LowPriority, "LowPriority", 4096, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(HighPriority, "HighPriority", 4096, NULL, 4, NULL, 0);
}