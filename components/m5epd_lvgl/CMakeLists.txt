message(STATUS "Settings M5EPDLVGL")

set(IDF_PATH_CMAKE $ENV{IDF_PATH})

string(REPLACE "\\" "/" IDF_PATH_CMAKE "${IDF_PATH_CMAKE}")

set(COMPONENT_SRCDIRS ".")

set(COMPONENT_ADD_INCLUDEDIRS 
        ".")

list(APPEND COMPONENT_REQUIRES "lvgl" "LovyanGFX")

register_component()

component_compile_options(
        -Wno-unused-const-variable
	-Wno-missing-field-initializers)

set(DEFINITIONS "ESP32")

list(APPEND DEFINITIONS "M5STACK")

list(APPEND DEFINITIONS "M5STACK_FIRE")

target_compile_definitions(${COMPONENT_TARGET} PUBLIC "-DESP32")