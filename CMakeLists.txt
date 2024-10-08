cmake_minimum_required(VERSION 3.10)

project(LicenseChainCPP)

set(CMAKE_CXX_STANDARD 11)

# Find CURL
find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIRS})

# Add the executable
add_executable(LicenseChainCPP src/main.cpp src/LicenseChain.cpp tests/LicenseChainTest.cpp)

# Link CURL library
target_link_libraries(LicenseChainCPP ${CURL_LIBRARIES})
