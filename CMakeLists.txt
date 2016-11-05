cmake_minimum_required (VERSION 2.6)
project (testpi)

set (testpi_VERSION_MAJOR 0)
set (testpi_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS "-O3")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/I2Cdev/I2Cdev.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/I2C/I2C.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/MPU6050/MPU6050.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/SSD1306/SSD1306.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

# configure_file (
#  	"${PROJECT_SOURCE_DIR}/lib/global.h.in"
#  	"${PROJECT_BINARY_DIR}/lib/global.h"
# )

include_directories(
	"${PROJECT_SOURCE_DIR}/lib"
)


add_executable(testpi ${SOURCE})
target_link_libraries (testpi bcm2835 wiringPi)
