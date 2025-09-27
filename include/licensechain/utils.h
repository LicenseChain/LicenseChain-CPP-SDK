#pragma once

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <regex>
#include <random>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <functional>

namespace LicenseChain {

class Utils {
public:
    // Validation functions
    static bool validateEmail(const std::string& email);
    static bool validateLicenseKey(const std::string& licenseKey);
    static bool validateUuid(const std::string& uuid);
    static bool validateAmount(double amount);
    static bool validateCurrency(const std::string& currency);
    
    // Input sanitization
    static std::string sanitizeInput(const std::string& input);
    static std::map<std::string, std::string> sanitizeMetadata(const std::map<std::string, std::string>& metadata);
    
    // Generation functions
    static std::string generateLicenseKey();
    static std::string generateUuid();
    
    // String utilities
    static std::string capitalizeFirst(const std::string& text);
    static std::string toSnakeCase(const std::string& text);
    static std::string toPascalCase(const std::string& text);
    static std::string truncateString(const std::string& text, size_t maxLength);
    static std::string slugify(const std::string& text);
    
    // Formatting functions
    static std::string formatBytes(size_t bytes);
    static std::string formatDuration(int seconds);
    static std::string formatPrice(double price, const std::string& currency = "USD");
    static std::string formatTimestamp(const std::chrono::system_clock::time_point& timestamp);
    static std::chrono::system_clock::time_point parseTimestamp(const std::string& timestamp);
    
    // Validation helpers
    static void validateNotEmpty(const std::string& value, const std::string& fieldName);
    static void validatePositive(double value, const std::string& fieldName);
    static void validateRange(double value, double min, double max, const std::string& fieldName);
    
    // Pagination
    static std::pair<int, int> validatePagination(int page, int limit);
    
    // Date range validation
    static void validateDateRange(const std::chrono::system_clock::time_point& startDate, 
                                 const std::chrono::system_clock::time_point& endDate);
    
    // Crypto functions
    static std::string createWebhookSignature(const std::string& payload, const std::string& secret);
    static bool verifyWebhookSignature(const std::string& payload, const std::string& signature, const std::string& secret);
    static std::string sha256(const std::string& data);
    static std::string sha1(const std::string& data);
    static std::string md5(const std::string& data);
    
    // Encoding/Decoding
    static std::string base64Encode(const std::string& data);
    static std::string base64Decode(const std::string& data);
    static std::string urlEncode(const std::string& data);
    static std::string urlDecode(const std::string& data);
    
    // JSON utilities
    static bool isValidJson(const std::string& jsonString);
    static std::string jsonSerialize(const std::map<std::string, std::string>& data);
    static std::map<std::string, std::string> jsonDeserialize(const std::string& jsonString);
    
    // URL utilities
    static bool isValidUrl(const std::string& urlString);
    
    // Time utilities
    static std::chrono::system_clock::time_point getCurrentTimestamp();
    static std::string getCurrentDate();
    
    // Array utilities
    static std::vector<std::vector<std::string>> chunkArray(const std::vector<std::string>& array, size_t chunkSize);
    
    // Object utilities
    static std::map<std::string, std::string> deepMerge(const std::map<std::string, std::string>& target, 
                                                       const std::map<std::string, std::string>& source);
    static std::map<std::string, std::string> flattenObject(const std::map<std::string, std::string>& obj, 
                                                           const std::string& separator = ".");
    static std::map<std::string, std::string> unflattenObject(const std::map<std::string, std::string>& obj, 
                                                             const std::string& separator = ".");
    
    // Random generation
    static std::string generateRandomString(size_t length, const std::string& characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
    static std::vector<uint8_t> generateRandomBytes(size_t length);
    
    // Retry logic
    template<typename Func>
    static auto retryWithBackoff(Func func, int maxRetries = 3, int initialDelayMs = 1000) -> decltype(func()) {
        int delay = initialDelayMs;
        std::exception_ptr lastException;
        
        for (int i = 0; i < maxRetries; ++i) {
            try {
                return func();
            } catch (...) {
                lastException = std::current_exception();
                if (i < maxRetries - 1) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                    delay *= 2; // Exponential backoff
                }
            }
        }
        
        std::rethrow_exception(lastException);
    }
    
    // Sleep utility
    static void sleep(int milliseconds);

private:
    static std::mt19937& getRandomGenerator();
    static std::string toHex(const std::vector<uint8_t>& data);
    static std::vector<uint8_t> fromHex(const std::string& hex);
};

} // namespace LicenseChain
