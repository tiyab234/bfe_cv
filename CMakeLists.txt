cmake_minimum_required(VERSION 3.28)

project(bfe_cv)

option(USE_NATIVE_INSTRUCTIONS "Optimize for host CPU at the cost of portability !" OFF)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED YES)

file(GLOB_RECURSE SOURCES source/**.c)
file(GLOB_RECURSE HEADERS include/**.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE include)

if(USE_NATIVE_INSTRUCTIONS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native")
endif()
