cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(m5_homeassistant)

# Add some include paths to driver/i2c.h
set(IDF_PATH_CMAKE $ENV{IDF_PATH})
string(REPLACE "\\" "/" IDF_PATH_CMAKE "${IDF_PATH_CMAKE}")
set(COMPONENT_ADD_INCLUDEDIRS 
        "${IDF_PATH_CMAKE}/components/"
        "${IDF_PATH_CMAKE}/components/driver/include")

list(APPEND COMPONENT_REQUIRES "driver")

idf_build_set_property(COMPILE_OPTIONS "-Wno-missing-field-initializers" APPEND)
idf_build_set_property(COMPILE_OPTIONS "-Wno-maybe-uninitialized" APPEND)
idf_build_set_property(CXX_COMPILE_OPTIONS "-Wno-deprecated-enum-enum-conversion" APPEND)
