cmake_minimum_required(VERSION 3.15)
project(LicenseChainCppSDK VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find required packages
find_package(nlohmann_json REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/licensechain_client.cpp
    src/http_client.cpp
    src/json_parser.cpp
    src/error_handler.cpp
)

# Header files
set(HEADERS
    include/licensechain/licensechain_client.h
    include/licensechain/http_client.h
    include/licensechain/json_parser.h
    include/licensechain/error_handler.h
    include/licensechain/models.h
    include/licensechain/exceptions.h
)

# Create library
add_library(LicenseChainCppSDK STATIC ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(LicenseChainCppSDK
    nlohmann_json::nlohmann_json
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
)

# Set properties
set_target_properties(LicenseChainCppSDK PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${HEADERS}"
)

# Install targets
install(TARGETS LicenseChainCppSDK
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

# Create example executable
add_executable(example examples/example.cpp)
target_link_libraries(example LicenseChainCppSDK)

# Create tests
enable_testing()
add_subdirectory(tests)

# Package configuration
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/LicenseChainCppSDKConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/LicenseChainCppSDKConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/LicenseChainCppSDKConfig.cmake"
    INSTALL_DESTINATION lib/cmake/LicenseChainCppSDK
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/LicenseChainCppSDKConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/LicenseChainCppSDKConfigVersion.cmake"
    DESTINATION lib/cmake/LicenseChainCppSDK
)
