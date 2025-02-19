#include "main.h"
#include "Pin_Init.h"


static void led_task(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1)
    {
        gpio_set_level(DATA_LED_Pin, 1);
        vTaskDelay(1000);
        gpio_set_level(DATA_LED_Pin, 0);
        vTaskDelay(1000);
        // MP2762A_Configure();
        // esp32.process_command();
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(100));
        // ESP_LOGI("key_power", "key_power value :%d", digitalRead(Key_Power));
        // ESP_LOGI("mcu_on_key", "mcu_on_key value :%d", digitalRead(MCU_ON_OFF_BAT_POWER));
    }
}

static void Log_task(void* param)
{
    while(1)
    {
        vTaskDelay(pdTICKS_TO_MS(100));
    }
}

static void Power_CTL_task(void *pvParameters)
{
    static uint8_t time = 0;
    static bool is_power_on = false;
    static bool enable_turnoff = false;
    while (1)
    {
        int power_key = gpio_get_level(Key_Power);
        vTaskDelay(1000);
        switch (power_key)
        {
        case 1:
        is_power_on = true;
        if(time>0)time--;
            break;
        case 0:
        enable_turnoff = true;
        time++;
        }

        if (enable_turnoff&&time == 3)
        {
            TrunOn_OFF_LED();
            gpio_set_level(MCU_ON_OFF_BAT_POWER, 0);
            ESP_LOGI("shutdown", "device shutdown");
        }
        else if (is_power_on)
        {
            vTaskDelay(50);
        }
        vTaskDelay(100);
    }
}

TaskHandle_t Power_Handle = NULL;
TaskHandle_t Led_task = NULL;

void app_main(void)
{
    Init_NVS_FS();
    Init_Pin();
    TrunOn_OFF_LED();
    vTaskDelay(1000);
    gpio_set_level(MCU_ON_OFF_BAT_POWER, 1);

    xTaskCreate(Power_CTL_task, "power_task", 1024, NULL, 10, &Power_Handle);
    xTaskCreate(led_task, "led_task", 1024*2, NULL, 2, &Led_task);
    return;

}