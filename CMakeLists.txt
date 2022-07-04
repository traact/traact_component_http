cmake_minimum_required(VERSION 3.16)

if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
else ()
    message(FATAL_ERROR "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif ()

list(APPEND CMAKE_MODULE_PATH ${CONAN_TRAACT_RUN_ENV_ROOT}/cmake)

project(${CONAN_PACKAGE_NAME}_PROJECT VERSION ${CONAN_PACKAGE_VERSION})

include(traact_default_library_setup)

# add your source files here
set(COMPONENT_SRC src/traact/component/HttpModule.cpp src/traact/component/HttpModule.h src/traact/component/HttpModuleComponent.cpp src/traact/component/HttpModuleComponent.h src/traact/component/HttpSink.cpp)


add_library(${CONAN_PACKAGE_NAME} SHARED ${COMPONENT_SRC})

conan_target_link_libraries(${CONAN_PACKAGE_NAME})