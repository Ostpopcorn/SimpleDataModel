
if(ESP_PLATFORM)
    idf_component_register(SRC_DIRS src
            INCLUDE_DIRS include)
    component_compile_options(-std=gnu++17)
else()
    cmake_minimum_required(VERSION 3.16)
    project(data_model)
    set(CMAKE_CXX_STANDARD 17)
    add_executable(data_model main.cpp src/DataModel.cpp include/DataModel.h)
endif()
