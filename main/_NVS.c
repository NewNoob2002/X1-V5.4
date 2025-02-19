#include "_NVS_.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"

void Init_NVS_FS()
{
  ESP_LOGI("nvs", "nvs_flash_init");
  esp_err_t err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    const esp_partition_t *partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, NULL);
    if (partition != NULL)
    {
      err = esp_partition_erase_range(partition, 0, partition->size);
      if (!err)
      {
        err = nvs_flash_init();
      }
    }
  }
  // 文件系统初始化
//   if (LittleFS.begin(true, "/www", 10, "webfs"))
//   {
//     ESP_LOGI("littlefs info", "Fs Init Ok");
//     ESP_LOGI("littlefs info", "Partition size: total: %d, used: %d",
//              LittleFS.totalBytes(), LittleFS.usedBytes());
//   }
}