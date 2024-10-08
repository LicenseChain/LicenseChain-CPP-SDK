#include "LicenseChain.hpp"
#include <cassert>

int main() {
    LicenseChain licenseChain("test_api_key");
    
    // Test case: invalid license
    assert(!licenseChain.validateLicense("invalid_license_key"));

    // Test case: valid license (you'll need to provide actual test cases)
    // assert(licenseChain.validateLicense("valid_license_key"));

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
