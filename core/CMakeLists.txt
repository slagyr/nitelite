project(niteliteCore)

file(GLOB_RECURSE CORE_SOURCES *.h *.cpp)

add_library(niteliteCore ${CORE_SOURCES})