#include "LicenseChain.hpp"
#include <iostream>

int main() {
    std::string apiKey = "your_api_key_here";
    std::string licenseKey = "license_to_validate";

    LicenseChain licenseChain(apiKey);

    if (licenseChain.validateLicense(licenseKey)) {
        std::cout << "License is valid!" << std::endl;
    } else {
        std::cout << "Invalid license!" << std::endl;
    }

    return 0;
}
