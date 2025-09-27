#include "licensechain/utils.h"
#include <regex>
#include <random>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <thread>
#include <chrono>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

namespace LicenseChain {

// Validation functions
bool Utils::validateEmail(const std::string& email) {
    if (email.empty()) return false;
    
    std::regex emailRegex(R"(^[^\s@]+@[^\s@]+\.[^\s@]+$)");
    return std::regex_match(email, emailRegex);
}

bool Utils::validateLicenseKey(const std::string& licenseKey) {
    if (licenseKey.empty() || licenseKey.length() != 32) return false;
    
    std::regex keyRegex(R"(^[A-Z0-9]+$)");
    return std::regex_match(licenseKey, keyRegex);
}

bool Utils::validateUuid(const std::string& uuid) {
    if (uuid.empty()) return false;
    
    std::regex uuidRegex(R"(^[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$)");
    return std::regex_match(uuid, uuidRegex);
}

bool Utils::validateAmount(double amount) {
    return amount > 0 && amount != std::numeric_limits<double>::max() && amount != std::numeric_limits<double>::min();
}

bool Utils::validateCurrency(const std::string& currency) {
    const std::vector<std::string> validCurrencies = {"USD", "EUR", "GBP", "CAD", "AUD", "JPY", "CHF", "CNY"};
    return std::find(validCurrencies.begin(), validCurrencies.end(), currency) != validCurrencies.end();
}

// Input sanitization
std::string Utils::sanitizeInput(const std::string& input) {
    if (input.empty()) return input;
    
    std::string result = input;
    std::replace(result.begin(), result.end(), '&', '&');
    std::replace(result.begin(), result.end(), '<', '<');
    std::replace(result.begin(), result.end(), '>', '>');
    std::replace(result.begin(), result.end(), '"', '"');
    std::replace(result.begin(), result.end(), '\'', ''');
    
    return result;
}

std::map<std::string, std::string> Utils::sanitizeMetadata(const std::map<std::string, std::string>& metadata) {
    std::map<std::string, std::string> sanitized;
    for (const auto& pair : metadata) {
        sanitized[pair.first] = sanitizeInput(pair.second);
    }
    return sanitized;
}

// Generation functions
std::string Utils::generateLicenseKey() {
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    auto& rng = getRandomGenerator();
    std::uniform_int_distribution<> dist(0, chars.size() - 1);
    
    std::string result;
    for (int i = 0; i < 32; ++i) {
        result += chars[dist(rng)];
    }
    return result;
}

std::string Utils::generateUuid() {
    auto& rng = getRandomGenerator();
    std::uniform_int_distribution<> dist(0, 15);
    std::uniform_int_distribution<> dist2(8, 11);
    
    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++) {
        ss << dist(rng);
    }
    ss << "-";
    for (i = 0; i < 4; i++) {
        ss << dist(rng);
    }
    ss << "-4";
    for (i = 0; i < 3; i++) {
        ss << dist(rng);
    }
    ss << "-";
    ss << dist2(rng);
    for (i = 0; i < 3; i++) {
        ss << dist(rng);
    }
    ss << "-";
    for (i = 0; i < 12; i++) {
        ss << dist(rng);
    }
    return ss.str();
}

// String utilities
std::string Utils::capitalizeFirst(const std::string& text) {
    if (text.empty()) return text;
    
    std::string result = text;
    result[0] = std::toupper(result[0]);
    for (size_t i = 1; i < result.length(); ++i) {
        result[i] = std::tolower(result[i]);
    }
    return result;
}

std::string Utils::toSnakeCase(const std::string& text) {
    if (text.empty()) return text;
    
    std::string result;
    for (size_t i = 0; i < text.length(); ++i) {
        if (std::isupper(text[i]) && i > 0) {
            result += '_';
        }
        result += std::tolower(text[i]);
    }
    return result;
}

std::string Utils::toPascalCase(const std::string& text) {
    if (text.empty()) return text;
    
    std::string result;
    bool capitalizeNext = true;
    
    for (char c : text) {
        if (c == '_') {
            capitalizeNext = true;
        } else {
            result += capitalizeNext ? std::toupper(c) : std::tolower(c);
            capitalizeNext = false;
        }
    }
    return result;
}

std::string Utils::truncateString(const std::string& text, size_t maxLength) {
    if (text.length() <= maxLength) return text;
    return text.substr(0, maxLength - 3) + "...";
}

std::string Utils::slugify(const std::string& text) {
    if (text.empty()) return text;
    
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    std::replace(result.begin(), result.end(), ' ', '-');
    std::replace(result.begin(), result.end(), '_', '-');
    
    // Remove multiple consecutive dashes
    result = std::regex_replace(result, std::regex("-+"), "-");
    
    // Remove leading/trailing dashes
    if (!result.empty() && result[0] == '-') result = result.substr(1);
    if (!result.empty() && result.back() == '-') result.pop_back();
    
    return result;
}

// Formatting functions
std::string Utils::formatBytes(size_t bytes) {
    const std::vector<std::string> units = {"B", "KB", "MB", "GB", "TB", "PB"};
    double size = static_cast<double>(bytes);
    int unitIndex = 0;
    
    while (size >= 1024 && unitIndex < units.size() - 1) {
        size /= 1024;
        unitIndex++;
    }
    
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << size << " " << units[unitIndex];
    return ss.str();
}

std::string Utils::formatDuration(int seconds) {
    if (seconds < 60) {
        return std::to_string(seconds) + "s";
    } else if (seconds < 3600) {
        int minutes = seconds / 60;
        int remainingSeconds = seconds % 60;
        return std::to_string(minutes) + "m " + std::to_string(remainingSeconds) + "s";
    } else if (seconds < 86400) {
        int hours = seconds / 3600;
        int minutes = (seconds % 3600) / 60;
        return std::to_string(hours) + "h " + std::to_string(minutes) + "m";
    } else {
        int days = seconds / 86400;
        int hours = (seconds % 86400) / 3600;
        return std::to_string(days) + "d " + std::to_string(hours) + "h";
    }
}

std::string Utils::formatPrice(double price, const std::string& currency) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);
    
    if (currency == "USD") ss << "$";
    else if (currency == "EUR") ss << "€";
    else if (currency == "GBP") ss << "£";
    else if (currency == "JPY") ss << "¥";
    else ss << currency << " ";
    
    ss << price;
    return ss.str();
}

std::string Utils::formatTimestamp(const std::chrono::system_clock::time_point& timestamp) {
    auto time_t = std::chrono::system_clock::to_time_t(timestamp);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch()) % 1000;
    
    std::stringstream ss;
    ss << std::put_time(std::gmtime(&time_t), "%Y-%m-%dT%H:%M:%S");
    ss << "." << std::setfill('0') << std::setw(3) << ms.count() << "Z";
    return ss.str();
}

std::chrono::system_clock::time_point Utils::parseTimestamp(const std::string& timestamp) {
    std::tm tm = {};
    std::stringstream ss(timestamp);
    ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");
    
    auto time_t = std::mktime(&tm);
    return std::chrono::system_clock::from_time_t(time_t);
}

// Validation helpers
void Utils::validateNotEmpty(const std::string& value, const std::string& fieldName) {
    if (value.empty()) {
        throw ValidationException(fieldName + " cannot be empty");
    }
}

void Utils::validatePositive(double value, const std::string& fieldName) {
    if (value <= 0) {
        throw ValidationException(fieldName + " must be positive");
    }
}

void Utils::validateRange(double value, double min, double max, const std::string& fieldName) {
    if (value < min || value > max) {
        throw ValidationException(fieldName + " must be between " + std::to_string(min) + " and " + std::to_string(max));
    }
}

// Pagination
std::pair<int, int> Utils::validatePagination(int page, int limit) {
    int validPage = std::max(page, 1);
    int validLimit = std::min(std::max(limit, 1), 100);
    return {validPage, validLimit};
}

// Date range validation
void Utils::validateDateRange(const std::chrono::system_clock::time_point& startDate, 
                             const std::chrono::system_clock::time_point& endDate) {
    if (startDate > endDate) {
        throw ValidationException("Start date must be before or equal to end date");
    }
}

// Crypto functions
std::string Utils::createWebhookSignature(const std::string& payload, const std::string& secret) {
    unsigned char* result;
    unsigned int len = 32;
    
    result = HMAC(EVP_sha256(), secret.c_str(), secret.length(),
                  reinterpret_cast<const unsigned char*>(payload.c_str()), payload.length(),
                  nullptr, &len);
    
    return toHex(std::vector<uint8_t>(result, result + len));
}

bool Utils::verifyWebhookSignature(const std::string& payload, const std::string& signature, const std::string& secret) {
    std::string expectedSignature = createWebhookSignature(payload, secret);
    return signature == expectedSignature;
}

std::string Utils::sha256(const std::string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.length(), hash);
    return toHex(std::vector<uint8_t>(hash, hash + SHA256_DIGEST_LENGTH));
}

std::string Utils::sha1(const std::string& data) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(data.c_str()), data.length(), hash);
    return toHex(std::vector<uint8_t>(hash, hash + SHA_DIGEST_LENGTH));
}

std::string Utils::md5(const std::string& data) {
    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5(reinterpret_cast<const unsigned char*>(data.c_str()), data.length(), hash);
    return toHex(std::vector<uint8_t>(hash, hash + MD5_DIGEST_LENGTH));
}

// Encoding/Decoding
std::string Utils::base64Encode(const std::string& data) {
    BIO* bio, *b64;
    BUF_MEM* bufferPtr;
    
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, data.c_str(), data.length());
    BIO_flush(bio);
    
    BIO_get_mem_ptr(bio, &bufferPtr);
    std::string result(bufferPtr->data, bufferPtr->length);
    
    BIO_free_all(bio);
    return result;
}

std::string Utils::base64Decode(const std::string& data) {
    BIO* bio, *b64;
    
    int decodeLen = (data.length() * 3) / 4;
    char* buffer = new char[decodeLen + 1];
    
    bio = BIO_new_mem_buf(data.c_str(), data.length());
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);
    
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    int length = BIO_read(bio, buffer, data.length());
    BIO_free_all(bio);
    
    std::string result(buffer, length);
    delete[] buffer;
    return result;
}

std::string Utils::urlEncode(const std::string& data) {
    std::stringstream ss;
    for (char c : data) {
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            ss << c;
        } else {
            ss << '%' << std::uppercase << std::hex << (int)c;
        }
    }
    return ss.str();
}

std::string Utils::urlDecode(const std::string& data) {
    std::string result;
    for (size_t i = 0; i < data.length(); ++i) {
        if (data[i] == '%' && i + 2 < data.length()) {
            int value;
            std::stringstream ss;
            ss << std::hex << data.substr(i + 1, 2);
            ss >> value;
            result += static_cast<char>(value);
            i += 2;
        } else {
            result += data[i];
        }
    }
    return result;
}

// JSON utilities
bool Utils::isValidJson(const std::string& jsonString) {
    // Simple JSON validation - in production, use a proper JSON library
    if (jsonString.empty()) return false;
    
    int braceCount = 0;
    int bracketCount = 0;
    bool inString = false;
    bool escaped = false;
    
    for (char c : jsonString) {
        if (escaped) {
            escaped = false;
            continue;
        }
        
        if (c == '\\') {
            escaped = true;
            continue;
        }
        
        if (c == '"') {
            inString = !inString;
            continue;
        }
        
        if (!inString) {
            if (c == '{') braceCount++;
            else if (c == '}') braceCount--;
            else if (c == '[') bracketCount++;
            else if (c == ']') bracketCount--;
        }
    }
    
    return braceCount == 0 && bracketCount == 0 && !inString;
}

std::string Utils::jsonSerialize(const std::map<std::string, std::string>& data) {
    std::stringstream ss;
    ss << "{";
    bool first = true;
    for (const auto& pair : data) {
        if (!first) ss << ",";
        ss << "\"" << pair.first << "\":\"" << pair.second << "\"";
        first = false;
    }
    ss << "}";
    return ss.str();
}

std::map<std::string, std::string> Utils::jsonDeserialize(const std::string& jsonString) {
    std::map<std::string, std::string> result;
    // Simple JSON parsing - in production, use a proper JSON library
    std::regex keyValueRegex(R"("([^"]+)"\s*:\s*"([^"]*)")");
    std::sregex_iterator iter(jsonString.begin(), jsonString.end(), keyValueRegex);
    std::sregex_iterator end;
    
    for (; iter != end; ++iter) {
        result[(*iter)[1]] = (*iter)[2];
    }
    
    return result;
}

// URL utilities
bool Utils::isValidUrl(const std::string& urlString) {
    std::regex urlRegex(R"(^https?://[^\s/$.?#].[^\s]*$)");
    return std::regex_match(urlString, urlRegex);
}

// Time utilities
std::chrono::system_clock::time_point Utils::getCurrentTimestamp() {
    return std::chrono::system_clock::now();
}

std::string Utils::getCurrentDate() {
    return formatTimestamp(getCurrentTimestamp());
}

// Array utilities
std::vector<std::vector<std::string>> Utils::chunkArray(const std::vector<std::string>& array, size_t chunkSize) {
    std::vector<std::vector<std::string>> chunks;
    for (size_t i = 0; i < array.size(); i += chunkSize) {
        std::vector<std::string> chunk;
        for (size_t j = i; j < std::min(i + chunkSize, array.size()); ++j) {
            chunk.push_back(array[j]);
        }
        chunks.push_back(chunk);
    }
    return chunks;
}

// Object utilities
std::map<std::string, std::string> Utils::deepMerge(const std::map<std::string, std::string>& target, 
                                                   const std::map<std::string, std::string>& source) {
    std::map<std::string, std::string> result = target;
    for (const auto& pair : source) {
        result[pair.first] = pair.second;
    }
    return result;
}

std::map<std::string, std::string> Utils::flattenObject(const std::map<std::string, std::string>& obj, 
                                                       const std::string& separator) {
    // Simple flattening implementation
    return obj;
}

std::map<std::string, std::string> Utils::unflattenObject(const std::map<std::string, std::string>& obj, 
                                                         const std::string& separator) {
    // Simple unflattening implementation
    return obj;
}

// Random generation
std::string Utils::generateRandomString(size_t length, const std::string& characters) {
    auto& rng = getRandomGenerator();
    std::uniform_int_distribution<> dist(0, characters.size() - 1);
    
    std::string result;
    for (size_t i = 0; i < length; ++i) {
        result += characters[dist(rng)];
    }
    return result;
}

std::vector<uint8_t> Utils::generateRandomBytes(size_t length) {
    std::vector<uint8_t> result(length);
    auto& rng = getRandomGenerator();
    std::uniform_int_distribution<uint8_t> dist(0, 255);
    
    for (size_t i = 0; i < length; ++i) {
        result[i] = dist(rng);
    }
    return result;
}

// Sleep utility
void Utils::sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// Private helper functions
std::mt19937& Utils::getRandomGenerator() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

std::string Utils::toHex(const std::vector<uint8_t>& data) {
    std::stringstream ss;
    for (uint8_t byte : data) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return ss.str();
}

std::vector<uint8_t> Utils::fromHex(const std::string& hex) {
    std::vector<uint8_t> result;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
        result.push_back(byte);
    }
    return result;
}

} // namespace LicenseChain
