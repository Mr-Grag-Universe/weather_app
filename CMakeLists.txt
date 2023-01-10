cmake_minimum_required(VERSION 3.24)
project(weather_app)

set(CMAKE_CXX_STANDARD 17)
set (BOOST_ROOT "C:/boost_1_81_0") # Путь к библиотеке Boost
set(Boost_DEBUG 1)

if (WIN32)
    set(_WIN32_WINNT 0x0601)
endif()

set (Boost_NO_WARN_NEW_VERSIONS ON)
set (Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED COMPONENTS system program_options)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS} "C:/boost_1_81_0")
include_directories(C:/boost_1_81_0/boost)
add_executable(${PROJECT_NAME} main.cpp Client.cpp Client.h Client.cpp Client.h SimpleServer.cpp SimpleServer.h SimpleServer.h SimpleServer.cpp C_Weather.cpp C_Weather.h)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})