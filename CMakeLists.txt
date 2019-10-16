cmake_minimum_required(VERSION 3.2.2)
project(nitelite)

add_definitions(-std=gnu++0x)

include_directories(core)

add_subdirectory(core)
add_subdirectory(test)
add_subdirectory(arduino)

target_link_libraries(niteliteCore)