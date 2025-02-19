#pragma once

#include "button_gpio.h"
#include "iot_button.h"
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include "esp_log.h"

#define LCD 0
/*gpio 引脚定义*/

#define Key_Power               39
#define Key_Func                12
/*状态灯*/
#define POWER_LED_Pin           27
#define CHARGER_LED_Pin         14
#define NET_LED_Pin             13
#define GNSS_LED_Pin            15
#define DATA_LED_Pin            2

#define ESP32_BOOT_Pin          0
/*电台引脚*/
#define Radio_Config_Pin        5
#define Radio_RX_Pin            32
#define Radio_TX_Pin            33
#define Radio_PWR_Pin           4
/*gps模块串口引脚*/
#define GNSS_PWREN_Pin          25
#define MCU_98x_RX_Pin          17
#define MCU_98x_TX_Pin          16
/*BMS芯片输出引脚*/
// #define MP2762_ACOK_Pin         5

/*NAND flash 引脚*/
#define SDIO_SCK_Pin            GPIO_NUM_18
#define SDIO_MISO_Pin           GPIO_NUM_19
#define SDIO_MOSI_Pin           GPIO_NUM_23

/*电池引脚*/
#define VBUS_DEC                36
#define Charge_Status_Pin       35
#define MCU_ON_OFF_BAT_POWER    26
#define BAT_I2C_SDA_Pin         21
#define BAT_I2C_SCL_Pin         22

#if LCD
#define LCD_SCK_Pin             12
#define LCD_SDI_Pin             13
#define LCD_RS_Pin              11
#define LCD_CS_Pin              10
#define LCD_BLK_Pin             14
#endif // DEBUG

void Config_gpio(uint16_t pin, gpio_mode_t mode);
void Init_Pin();
void TrunOn_OFF_LED();