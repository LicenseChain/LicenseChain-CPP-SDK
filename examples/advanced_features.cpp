// LicenseChain C++ SDK - Advanced Features Example
// This example demonstrates advanced features of the LicenseChain C++ SDK

#include <licensechain/licensechain_client.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <map>
#include <functional>

class AdvancedLicenseManager {
private:
    LicenseChain::Client& client;
    std::map<std::string, LicenseChain::License> licenseCache;
    std::chrono::seconds cacheTimeout{300}; // 5 minutes
    
public:
    AdvancedLicenseManager(LicenseChain::Client& client) : client(client) {}
    
    // Validate license with retry logic
    LicenseChain::Result<LicenseChain::License> validateLicenseWithRetry(
        const std::string& licenseKey, int maxRetries = 3) {
        
        for (int attempt = 1; attempt <= maxRetries; ++attempt) {
            auto result = client.validateLicense(licenseKey);
            
            if (result.success) {
                return result;
            }
            
            // Handle error
            std::cerr << "⚠️ License validation attempt " << attempt 
                      << " failed: " << result.error << std::endl;
            
            if (result.errorType != LicenseChain::ErrorType::NETWORK_ERROR || 
                attempt == maxRetries) {
                return result;
            }
            
            // Wait before retry (exponential backoff)
            std::this_thread::sleep_for(std::chrono::seconds(1 << attempt));
        }
        
        return LicenseChain::Result<LicenseChain::License>::error(
            LicenseChain::ErrorType::RETRY_EXHAUSTED, 
            "Maximum retry attempts exceeded");
    }
    
    // Validate license with caching
    LicenseChain::Result<LicenseChain::License> validateLicenseWithCache(
        const std::string& licenseKey) {
        
        // Check cache first
        auto cachedIt = licenseCache.find(licenseKey);
        if (cachedIt != licenseCache.end()) {
            auto now = std::chrono::system_clock::now();
            auto cacheTime = std::chrono::system_clock::from_time_t(cachedIt->second.cachedAt);
            
            if (now - cacheTime < cacheTimeout) {
                std::cout << "📋 Using cached license data" << std::endl;
                return LicenseChain::Result<LicenseChain::License>::success(cachedIt->second);
            }
        }
        
        // Validate license
        auto result = validateLicenseWithRetry(licenseKey);
        if (result.success) {
            // Cache the result
            result.license.cachedAt = std::time(nullptr);
            licenseCache[licenseKey] = result.license;
        }
        
        return result;
    }
    
    // Clear cache
    void clearCache() {
        licenseCache.clear();
        std::cout << "🗑️ License cache cleared" << std::endl;
    }
    
    // Get cache size
    size_t getCacheSize() const {
        return licenseCache.size();
    }
};

class AnalyticsTracker {
private:
    LicenseChain::Client& client;
    
public:
    AnalyticsTracker(LicenseChain::Client& client) : client(client) {}
    
    void trackLevelCompletion(int level, int score, int timeSpent) {
        client.trackEvent("level_completed", {
            {"level", level},
            {"score", score},
            {"timeSpent", timeSpent},
            {"difficulty", "normal"}
        });
    }
    
    void trackAchievementUnlocked(const std::string& achievementId, 
                                 const std::string& achievementName) {
        client.trackEvent("achievement_unlocked", {
            {"achievementId", achievementId},
            {"achievementName", achievementName},
            {"unlockedAt", std::time(nullptr)}
        });
    }
    
    void trackPurchaseMade(const std::string& itemId, 
                          const std::string& itemName, 
                          double price, 
                          const std::string& currency = "USD") {
        client.trackEvent("purchase_made", {
            {"itemId", itemId},
            {"itemName", itemName},
            {"price", price},
            {"currency", currency},
            {"purchaseTime", std::time(nullptr)}
        });
    }
    
    void trackFeatureUsage(const std::string& featureName, 
                          int usageCount = 1, 
                          int duration = 0) {
        client.trackEvent("feature_used", {
            {"featureName", featureName},
            {"usageCount", usageCount},
            {"duration", duration},
            {"timestamp", std::time(nullptr)}
        });
    }
    
    void trackError(const std::string& errorType, 
                   const std::string& errorMessage, 
                   const std::map<std::string, std::string>& context = {}) {
        client.trackEvent("error_occurred", {
            {"errorType", errorType},
            {"errorMessage", errorMessage},
            {"context", context},
            {"timestamp", std::time(nullptr)}
        });
    }
};

class PerformanceMonitor {
private:
    LicenseChain::Client& client;
    std::thread monitorThread;
    bool running = false;
    
public:
    PerformanceMonitor(LicenseChain::Client& client) : client(client) {}
    
    void startMonitoring() {
        running = true;
        monitorThread = std::thread([this]() {
            while (running) {
                std::this_thread::sleep_for(std::chrono::minutes(1));
                
                auto metrics = client.getPerformanceMetrics();
                std::cout << "📊 Performance Metrics:" << std::endl;
                std::cout << "  Requests: " << metrics.requests << std::endl;
                std::cout << "  Errors: " << metrics.errors << std::endl;
                std::cout << "  Success Rate: " << (metrics.successRate * 100) << "%" << std::endl;
                std::cout << "  Avg Response Time: " << (metrics.avgResponseTime * 1000) << "ms" << std::endl;
                
                // Track performance metrics
                client.trackEvent("performance_metrics", {
                    {"requests", metrics.requests},
                    {"errors", metrics.errors},
                    {"successRate", metrics.successRate},
                    {"avgResponseTime", metrics.avgResponseTime}
                });
            }
        });
        
        std::cout << "📈 Performance monitoring started" << std::endl;
    }
    
    void stopMonitoring() {
        running = false;
        if (monitorThread.joinable()) {
            monitorThread.join();
        }
        std::cout << "📈 Performance monitoring stopped" << std::endl;
    }
};

class ErrorHandler {
public:
    static void handleError(const LicenseChain::ResultBase& result, 
                           const std::string& context = "") {
        std::cerr << "⚠️ Error occurred: " << result.error << std::endl;
        
        if (!context.empty()) {
            std::cerr << "Context: " << context << std::endl;
        }
        
        // Handle specific error types
        switch (result.errorType) {
            case LicenseChain::ErrorType::NETWORK_ERROR:
                std::cerr << "🌐 Network error - attempting retry..." << std::endl;
                break;
            case LicenseChain::ErrorType::INVALID_LICENSE:
                std::cerr << "🔑 Invalid license - redirecting to purchase..." << std::endl;
                break;
            case LicenseChain::ErrorType::EXPIRED_LICENSE:
                std::cerr << "⏰ License expired - showing renewal options..." << std::endl;
                break;
            case LicenseChain::ErrorType::HARDWARE_MISMATCH:
                std::cerr << "🖥️ Hardware mismatch - license bound to different device..." << std::endl;
                break;
            default:
                std::cerr << "❌ Generic error - logging and continuing..." << std::endl;
                break;
        }
    }
};

int main() {
    std::cout << "🚀 LicenseChain C++ SDK - Advanced Features Example" << std::endl;
    std::cout << "=" << std::string(60, '=') << std::endl;
    
    // Initialize the client with advanced configuration
    LicenseChain::Client client({
        .apiKey = "your-api-key-here",
        .appName = "AdvancedCppApp",
        .version = "1.0.0",
        .debug = true,
        .timeout = 30,
        .retries = 5
    });
    
    // Connect to LicenseChain
    std::cout << "\n🔌 Connecting to LicenseChain..." << std::endl;
    auto connectResult = client.connect();
    if (!connectResult.success) {
        std::cerr << "❌ Failed to connect to LicenseChain: " << connectResult.error << std::endl;
        return 1;
    }
    
    std::cout << "✅ Connected to LicenseChain successfully!" << std::endl;
    
    // Initialize advanced managers
    AdvancedLicenseManager licenseManager(client);
    AnalyticsTracker analytics(client);
    PerformanceMonitor performanceMonitor(client);
    
    // Start performance monitoring
    performanceMonitor.startMonitoring();
    
    // Demonstrate advanced license validation
    std::cout << "\n🔍 Advanced License Validation..." << std::endl;
    std::string licenseKey = "LICENSE-KEY-HERE";
    
    // Validate with retry
    auto retryResult = licenseManager.validateLicenseWithRetry(licenseKey, 3);
    if (retryResult.success) {
        std::cout << "✅ License validated with retry logic" << std::endl;
    } else {
        std::cout << "❌ License validation failed: " << retryResult.error << std::endl;
        ErrorHandler::handleError(retryResult, "Advanced validation");
    }
    
    // Validate with cache
    auto cacheResult = licenseManager.validateLicenseWithCache(licenseKey);
    if (cacheResult.success) {
        std::cout << "✅ License validated with caching" << std::endl;
    } else {
        std::cout << "❌ License validation failed: " << cacheResult.error << std::endl;
    }
    
    // Demonstrate analytics tracking
    std::cout << "\n📊 Advanced Analytics Tracking..." << std::endl;
    
    analytics.trackLevelCompletion(1, 1000, 120);
    analytics.trackAchievementUnlocked("first_license", "First License");
    analytics.trackPurchaseMade("premium_license", "Premium License", 9.99, "USD");
    analytics.trackFeatureUsage("license_validation", 1, 0.5);
    analytics.trackError("network_error", "Connection timeout", {{"context", "license_validation"}});
    
    std::cout << "✅ Advanced analytics tracking completed" << std::endl;
    
    // Demonstrate error handling
    std::cout << "\n⚠️ Advanced Error Handling..." << std::endl;
    
    // Test different error scenarios
    auto invalidLicenseResult = client.validateLicense("invalid-license-key");
    if (!invalidLicenseResult.success) {
        ErrorHandler::handleError(invalidLicenseResult, "Invalid license test");
    }
    
    // Demonstrate cache management
    std::cout << "\n🗄️ Cache Management..." << std::endl;
    std::cout << "Cache size: " << licenseManager.getCacheSize() << std::endl;
    
    // Clear cache
    licenseManager.clearCache();
    std::cout << "Cache size after clear: " << licenseManager.getCacheSize() << std::endl;
    
    // Demonstrate performance metrics
    std::cout << "\n📈 Performance Metrics..." << std::endl;
    auto metrics = client.getPerformanceMetrics();
    std::cout << "📊 Current Performance Metrics:" << std::endl;
    std::cout << "  Requests: " << metrics.requests << std::endl;
    std::cout << "  Errors: " << metrics.errors << std::endl;
    std::cout << "  Success Rate: " << (metrics.successRate * 100) << "%" << std::endl;
    std::cout << "  Avg Response Time: " << (metrics.avgResponseTime * 1000) << "ms" << std::endl;
    std::cout << "  Last Request: " << metrics.lastRequestTime << std::endl;
    
    // Wait a bit to see performance monitoring in action
    std::cout << "\n⏳ Waiting for performance monitoring data..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    // Stop performance monitoring
    performanceMonitor.stopMonitoring();
    
    // Cleanup
    std::cout << "\n🧹 Cleaning up..." << std::endl;
    client.logout();
    client.disconnect();
    
    std::cout << "✅ Cleanup completed!" << std::endl;
    std::cout << "\n🎉 Advanced features demonstration completed!" << std::endl;
    
    return 0;
}
