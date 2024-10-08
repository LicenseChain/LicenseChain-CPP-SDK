#include "LicenseChain.hpp"
#include <iostream>
#include <curl/curl.h>

LicenseChain::LicenseChain(const std::string& apiKey)
    : apiKey(apiKey), apiUrl("https://licensechain.app/api/validation.php") {}

bool LicenseChain::validateLicense(const std::string& licenseKey) {
    std::string response = makeApiRequest(licenseKey);
    // Check response and return true if license is valid
    return response.find("valid") != std::string::npos;
}

std::string LicenseChain::makeApiRequest(const std::string& licenseKey) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        std::string url = apiUrl + "?license_key=" + licenseKey + "&api_key=" + apiKey;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](void* contents, size_t size, size_t nmemb, void* userp) {
            ((std::string*)userp)->append((char*)contents, size * nmemb);
            return size * nmemb;
        });
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}
