# ---------------------------------------------------------------
# MinUI
# A minimalist X11 GUI toolkit
# Author: B. Halimi - 2021 - <bhalimi@outlook.fr>
# ---------------------------------------------------------------
cmake_minimum_required (VERSION 3.1)

project (MinUI)

# Check the OS -----------------------------------------------------------------
if(NOT UNIX)
	message(FATAL_ERROR " Only Unix based systems are supported")
endif()

# Check the CMake usage --------------------------------------------------------
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message(FATAL_ERROR " Inappropriate CMake usage. \n" 
	                    " Should be called in a build directory: \n" 
	                    " $ mkdir build; cmake ..")
endif()

# Find Dependencies ------------------------------------------------------------
find_package(X11 REQUIRED)
find_package(Threads REQUIRED)

if(NOT Threads_FOUND)
	message(FATAL_ERROR " Could not locate the pthread library. \n"
	                    " Please ensure it is installed on your machine.")
endif()

# Set the compiler flags -------------------------------------------------------
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-O2 -s -Wall -pthread")
endif()

# Gather the sources -----------------------------------------------------------
file(GLOB_RECURSE MINUI_SRC "MinUI/*.cpp")

# Declare the lib -----------------------------------------------------------
add_library(MinUI STATIC ${MINUI_SRC})

# Build the example ---------------------------------------------------------
add_executable(Example
	Example/main.cpp
)

# Link MinUI ---------------------------------------------------------
target_link_libraries(Example
	MinUI
	${X11_LIBRARIES}
)

# Copy the fonts -----------------------------------------------------------
file(COPY "MinUI/Fonts" DESTINATION ".")



