// LicenseChain C++ SDK - Basic Usage Example
// This example demonstrates the basic usage of the LicenseChain C++ SDK

#include <licensechain/licensechain_client.h>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::cout << "🚀 LicenseChain C++ SDK - Basic Usage Example" << std::endl;
    std::cout << "=" << std::string(50, '=') << std::endl;
    
    // Initialize the client
    LicenseChain::Client client({
        .apiKey = "your-api-key-here",
        .appName = "MyCppApp",
        .version = "1.0.0",
        .debug = true
    });
    
    // Connect to LicenseChain
    std::cout << "\n🔌 Connecting to LicenseChain..." << std::endl;
    auto connectResult = client.connect();
    if (!connectResult.success) {
        std::cerr << "❌ Failed to connect to LicenseChain: " << connectResult.error << std::endl;
        return 1;
    }
    
    std::cout << "✅ Connected to LicenseChain successfully!" << std::endl;
    
    // Example 1: User Registration
    std::cout << "\n📝 Registering new user..." << std::endl;
    auto registerResult = client.register("testuser", "password123", "test@example.com");
    if (registerResult.success) {
        std::cout << "✅ User registered successfully!" << std::endl;
        std::cout << "Session ID: " << registerResult.sessionId << std::endl;
    } else {
        std::cerr << "❌ Registration failed: " << registerResult.error << std::endl;
    }
    
    // Example 2: User Login
    std::cout << "\n🔐 Logging in user..." << std::endl;
    auto loginResult = client.login("testuser", "password123");
    if (loginResult.success) {
        std::cout << "✅ User logged in successfully!" << std::endl;
        std::cout << "User ID: " << loginResult.user.id << std::endl;
        std::cout << "Username: " << loginResult.user.username << std::endl;
    } else {
        std::cerr << "❌ Login failed: " << loginResult.error << std::endl;
    }
    
    // Example 3: License Validation
    std::cout << "\n🔍 Validating license..." << std::endl;
    std::string licenseKey = "LICENSE-KEY-HERE"; // Replace with actual license key
    auto validateResult = client.validateLicense(licenseKey);
    
    if (validateResult.success) {
        std::cout << "✅ License is valid!" << std::endl;
        std::cout << "License Key: " << validateResult.license.key << std::endl;
        std::cout << "Status: " << validateResult.license.status << std::endl;
        std::cout << "Expires: " << validateResult.license.expires << std::endl;
        std::cout << "Features: ";
        for (const auto& feature : validateResult.license.features) {
            std::cout << feature << " ";
        }
        std::cout << std::endl;
        std::cout << "User: " << validateResult.license.user << std::endl;
    } else {
        std::cerr << "❌ License validation failed: " << validateResult.error << std::endl;
    }
    
    // Example 4: Get User Licenses
    std::cout << "\n📋 Getting user licenses..." << std::endl;
    auto licensesResult = client.getUserLicenses();
    if (licensesResult.success) {
        std::cout << "✅ Found " << licensesResult.licenses.size() << " licenses:" << std::endl;
        for (size_t i = 0; i < licensesResult.licenses.size(); ++i) {
            const auto& license = licensesResult.licenses[i];
            std::cout << "  " << (i + 1) << ". " << license.key 
                      << " - " << license.status 
                      << " (Expires: " << license.expires << ")" << std::endl;
        }
    } else {
        std::cerr << "❌ Failed to get licenses: " << licensesResult.error << std::endl;
    }
    
    // Example 5: Hardware ID Validation
    std::cout << "\n🖥️ Validating hardware ID..." << std::endl;
    std::string hardwareId = client.getHardwareId();
    std::cout << "Hardware ID: " << hardwareId << std::endl;
    
    auto hardwareResult = client.validateHardwareId(licenseKey, hardwareId);
    if (hardwareResult.success) {
        std::cout << "✅ Hardware ID is valid for this license!" << std::endl;
    } else {
        std::cerr << "❌ Hardware ID validation failed: " << hardwareResult.error << std::endl;
    }
    
    // Example 6: Analytics Tracking
    std::cout << "\n📊 Tracking analytics..." << std::endl;
    auto trackResult = client.trackEvent("app.started", {
        {"level", 1},
        {"playerCount", 10},
        {"timestamp", std::time(nullptr)}
    });
    
    if (trackResult.success) {
        std::cout << "✅ Event tracked successfully!" << std::endl;
    } else {
        std::cerr << "❌ Failed to track event: " << trackResult.error << std::endl;
    }
    
    // Example 7: Performance Metrics
    std::cout << "\n📈 Getting performance metrics..." << std::endl;
    auto metrics = client.getPerformanceMetrics();
    std::cout << "📊 Performance Metrics:" << std::endl;
    std::cout << "  Requests: " << metrics.requests << std::endl;
    std::cout << "  Errors: " << metrics.errors << std::endl;
    std::cout << "  Success Rate: " << (metrics.successRate * 100) << "%" << std::endl;
    std::cout << "  Avg Response Time: " << (metrics.avgResponseTime * 1000) << "ms" << std::endl;
    std::cout << "  Last Request: " << metrics.lastRequestTime << std::endl;
    
    // Example 8: Error Handling
    std::cout << "\n⚠️ Demonstrating error handling..." << std::endl;
    auto errorResult = client.validateLicense("invalid-license-key");
    if (!errorResult.success) {
        std::cout << "❌ Expected error: " << errorResult.error << std::endl;
        std::cout << "Error Type: " << static_cast<int>(errorResult.errorType) << std::endl;
        
        // Check if error is retryable
        if (errorResult.errorType == LicenseChain::ErrorType::NETWORK_ERROR) {
            std::cout << "🔄 This error can be retried" << std::endl;
        } else {
            std::cout << "🚫 This error cannot be retried" << std::endl;
        }
    }
    
    // Example 9: Cleanup
    std::cout << "\n🧹 Cleaning up..." << std::endl;
    client.logout();
    client.disconnect();
    
    std::cout << "✅ Cleanup completed!" << std::endl;
    std::cout << "\n🎉 All examples completed!" << std::endl;
    
    return 0;
}
