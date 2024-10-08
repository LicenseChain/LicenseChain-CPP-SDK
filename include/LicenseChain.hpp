#ifndef LICENSECHAIN_HPP
#define LICENSECHAIN_HPP

#include <string>

class LicenseChain {
public:
    LicenseChain(const std::string& apiKey);

    // Validate the license using LicenseChain API
    bool validateLicense(const std::string& licenseKey);

private:
    std::string apiKey;
    std::string apiUrl;

    std::string makeApiRequest(const std::string& licenseKey);
};

#endif // LICENSECHAIN_HPP
