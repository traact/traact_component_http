cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME traact_component_http)

project(${TARGET_NAME} VERSION "0.0.0" LANGUAGES CXX)

find_package(traact_base)
list(APPEND CMAKE_MODULE_PATH ${traact_base_INCLUDE_DIR})

include(traact_default_library_setup)

# add your source files here
set(COMPONENT_SRC src/traact/component/HttpModule.cpp src/traact/component/HttpModule.h src/traact/component/HttpModuleComponent.cpp src/traact/component/HttpModuleComponent.h src/traact/component/HttpSink.cpp)


add_library(${TARGET_NAME} SHARED ${COMPONENT_SRC})

find_package(traact_spatial REQUIRED)
find_package(traact_vision REQUIRED)
find_package(traact_component_cereal REQUIRED)
find_package(httplib REQUIRED)

target_link_libraries(${TARGET_NAME} traact_core::traact_core traact_spatial::traact_spatial traact_vision::traact_vision traact_component_cereal::traact_component_cereal httplib::httplib)

include(traact_default_library_final)
