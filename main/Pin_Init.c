#include "Pin_Init.h"


static void button_event_cb(void *arg, void *data)
{
    ESP_LOGI("double_click", "double_click");
    // esp32.Wifi_ReStart();
    // digitalWrite(GPIO_NUM_2, 1);
}

static void button_single_event_cb(void *arg, void *data)
{
    // esp32.STOP_Wifi();
    // digitalWrite(GPIO_NUM_2, 0);
    ESP_LOGI("power key", "level :%d", gpio_get_level(MCU_ON_OFF_BAT_POWER));
    ESP_LOGI("single_click", "single_click");
}

static void button_long_event_cb(void *arg, void *data)
{

    ESP_LOGI("single_click", "single_click");
}

void Config_gpio(uint16_t pin, gpio_mode_t mode)
{
    gpio_reset_pin((gpio_num_t)pin);
    gpio_set_direction((gpio_num_t)pin, mode);
}

void Init_Pin()
{
    // for radio config mode
    Config_gpio(Radio_Config_Pin, GPIO_MODE_OUTPUT);
    Config_gpio(Radio_PWR_Pin, GPIO_MODE_OUTPUT);
    gpio_set_level(Radio_Config_Pin, 1);
    gpio_set_level(Radio_PWR_Pin, 0);

    Config_gpio(GNSS_PWREN_Pin, GPIO_MODE_OUTPUT);
    gpio_set_level(GNSS_PWREN_Pin, 0);
    // for enable BAT
    Config_gpio(MCU_ON_OFF_BAT_POWER, GPIO_MODE_OUTPUT);
    gpio_set_level(MCU_ON_OFF_BAT_POWER, 1);

    // 按键设置
    button_config_t btn_cfg = {
        .long_press_time = 1000,
        .short_press_time = 180,
    };
    button_gpio_config_t gpio_cfg = {
        .gpio_num = Key_Func,
        .active_level = 0,
        .enable_power_save = true,
    };
    button_handle_t btn;
    esp_err_t ret = iot_button_new_gpio_device(&btn_cfg, &gpio_cfg, &btn);
    assert(ret == ESP_OK);

    ret |= iot_button_register_cb(btn, BUTTON_SINGLE_CLICK, NULL, button_single_event_cb, NULL);
    ret |= iot_button_register_cb(btn, BUTTON_DOUBLE_CLICK, NULL, button_event_cb, NULL);
    ret |= iot_button_register_cb(btn, BUTTON_LONG_PRESS_HOLD, NULL, button_long_event_cb, NULL);
    // //状态灯
    Config_gpio(POWER_LED_Pin, GPIO_MODE_OUTPUT);
    Config_gpio(CHARGER_LED_Pin, GPIO_MODE_OUTPUT);
    Config_gpio(NET_LED_Pin, GPIO_MODE_OUTPUT);
    Config_gpio(GNSS_LED_Pin, GPIO_MODE_OUTPUT);
    Config_gpio(DATA_LED_Pin, GPIO_MODE_OUTPUT);

    // Power
    Config_gpio(Key_Power, GPIO_MODE_INPUT);
    Config_gpio(VBUS_DEC, GPIO_MODE_INPUT);
    Config_gpio(Charge_Status_Pin, GPIO_MODE_INPUT);
}

void TrunOn_OFF_LED()
{
    gpio_set_level(POWER_LED_Pin, 1);
    gpio_set_level(CHARGER_LED_Pin, 1);
    gpio_set_level(NET_LED_Pin, 1);
    gpio_set_level(GNSS_LED_Pin, 1);
    gpio_set_level(DATA_LED_Pin, 1);
    vTaskDelay(pdMS_TO_TICKS(300));

    gpio_set_level(POWER_LED_Pin, 0);
    gpio_set_level(CHARGER_LED_Pin, 0);
    gpio_set_level(NET_LED_Pin, 0);
    gpio_set_level(GNSS_LED_Pin, 0);
    gpio_set_level(DATA_LED_Pin, 0);
}