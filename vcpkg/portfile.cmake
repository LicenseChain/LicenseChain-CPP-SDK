vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO LicenseChain/LicenseChain-CPP-SDK
    REF "v${VERSION}"
    SHA512 10077ff00663a957863583ef40f6a672cee28ffc52ca8f726a50f15f7ca3bc983246aaf452e47cc304287023c63c9b701bc25cff988d438de3683e3af3ed03c7
    HEAD_REF main
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        -DCMAKE_CXX_STANDARD=20
)

vcpkg_cmake_install()
vcpkg_cmake_config_fixup(PACKAGE_NAME "LicenseChainCppSDK" CONFIG_PATH "lib/cmake/LicenseChainCppSDK")
vcpkg_copy_pdbs()

file(INSTALL "${SOURCE_PATH}/LICENSE" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}" RENAME copyright)
