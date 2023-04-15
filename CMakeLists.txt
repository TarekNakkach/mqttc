cmake_minimum_required(VERSION 2.8.9)
project(directory_test)

set(EXE_NAME mqttc)

file(GLOB SOURCES "src/*/*.c")

include_directories(include)

add_executable(${EXE_NAME} ${SOURCES})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb")

target_link_libraries (${EXE_NAME} LINK_PUBLIC json-c mosquitto)

install(TARGETS ${EXE_NAME} DESTINATION bin)
