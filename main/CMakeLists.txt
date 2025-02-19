idf_component_register(
    SRCS "main.c" "Pin_Init.c" "_NVS.c"
    INCLUDE_DIRS "include"
)

# littlefs_create_partition_image(webfs ../webui FLASH_IN_PROJECT)