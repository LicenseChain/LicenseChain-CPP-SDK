#pragma once

#include <stdexcept>
#include <string>

namespace LicenseChain {

class LicenseChainException : public std::runtime_error {
public:
    explicit LicenseChainException(const std::string& message)
        : std::runtime_error(message), error_code_("UNKNOWN_ERROR"), status_code_(500) {}
    
    LicenseChainException(const std::string& error_code, const std::string& message)
        : std::runtime_error(message), error_code_(error_code), status_code_(500) {}
    
    LicenseChainException(const std::string& error_code, const std::string& message, int status_code)
        : std::runtime_error(message), error_code_(error_code), status_code_(status_code) {}
    
    const std::string& getErrorCode() const { return error_code_; }
    int getStatusCode() const { return status_code_; }

private:
    std::string error_code_;
    int status_code_;
};

class NetworkException : public LicenseChainException {
public:
    explicit NetworkException(const std::string& message)
        : LicenseChainException("NETWORK_ERROR", message, 0) {}
};

class ValidationException : public LicenseChainException {
public:
    explicit ValidationException(const std::string& message)
        : LicenseChainException("VALIDATION_ERROR", message, 400) {}
};

class AuthenticationException : public LicenseChainException {
public:
    explicit AuthenticationException(const std::string& message)
        : LicenseChainException("AUTHENTICATION_ERROR", message, 401) {}
};

class NotFoundException : public LicenseChainException {
public:
    explicit NotFoundException(const std::string& message)
        : LicenseChainException("NOT_FOUND_ERROR", message, 404) {}
};

class RateLimitException : public LicenseChainException {
public:
    explicit RateLimitException(const std::string& message)
        : LicenseChainException("RATE_LIMIT_ERROR", message, 429) {}
};

class ServerException : public LicenseChainException {
public:
    explicit ServerException(const std::string& message)
        : LicenseChainException("SERVER_ERROR", message, 500) {}
};

class ConfigurationException : public LicenseChainException {
public:
    explicit ConfigurationException(const std::string& message)
        : LicenseChainException("CONFIGURATION_ERROR", message, 500) {}
};

} // namespace LicenseChain
