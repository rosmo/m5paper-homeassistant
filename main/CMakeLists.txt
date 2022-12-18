#idf_component_register(SRCS "hello_world_main.c"
#                    INCLUDE_DIRS "")

message(STATUS "Settings main")

set(COMPONENT_SRCDIRS ".")
set(COMPONENT_ADD_INCLUDEDIRS ".")

list(APPEND COMPONENT_REQUIRES "nvs_flash" "m5epd_lvgl" "spi_flash")

register_component()

component_compile_options(
        -Wno-unused-const-variable
	-Wno-missing-field-initializers
        -Wno-format)
