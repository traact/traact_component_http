cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME traact_component_zenoh)

project(${TARGET_NAME} VERSION "0.0.0" LANGUAGES CXX)

find_package(traact_base)
list(APPEND CMAKE_MODULE_PATH ${traact_base_INCLUDE_DIR})

include(traact_default_library_setup)

# add your source files here
set(COMPONENT_SRC src/traact/component/HttpModule.cpp src/traact/component/HttpModule.h src/traact/component/HttpModuleComponent.cpp src/traact/component/HttpModuleComponent.h src/traact/component/HttpSink.cpp
        src/traact/util/ZenohServer.cpp
        src/traact/util/ZenohServer.h)


add_library(${TARGET_NAME} SHARED ${COMPONENT_SRC})

find_package(traact_spatial REQUIRED)
find_package(traact_vision REQUIRED)
find_package(traact_component_cereal REQUIRED)
find_package(zenoh-c REQUIRED)
find_package(fastcdr REQUIRED)
find_package(httplib REQUIRED)

target_link_libraries(${TARGET_NAME} traact_core::traact_core traact_spatial::traact_spatial traact_vision::traact_vision traact_component_cereal::traact_component_cereal fastcdr zenoh-c::zenoh-c httplib::httplib)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(traact_default_library_final)
