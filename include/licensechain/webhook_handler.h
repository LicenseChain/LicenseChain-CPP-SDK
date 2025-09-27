#pragma once

#include "models.h"
#include "exceptions.h"
#include <string>
#include <functional>
#include <map>

namespace LicenseChain {

class WebhookHandler {
public:
    using EventCallback = std::function<void(const WebhookEvent&)>;
    
    WebhookHandler(const std::string& secret);
    
    // Event registration
    void onEvent(const std::string& eventType, EventCallback callback);
    void onLicenseCreated(EventCallback callback);
    void onLicenseUpdated(EventCallback callback);
    void onLicenseRevoked(EventCallback callback);
    void onUserCreated(EventCallback callback);
    void onUserUpdated(EventCallback callback);
    void onProductCreated(EventCallback callback);
    void onProductUpdated(EventCallback callback);
    void onWebhookCreated(EventCallback callback);
    void onWebhookUpdated(EventCallback callback);
    void onWebhookDeleted(EventCallback callback);
    
    // Webhook processing
    bool processWebhook(const std::string& payload, const std::string& signature, const std::string& timestamp);
    WebhookEvent parseWebhookEvent(const std::string& payload);
    
    // Signature verification
    bool verifySignature(const std::string& payload, const std::string& signature, const std::string& timestamp);
    
    // Event handling
    void handleEvent(const WebhookEvent& event);
    
    // Configuration
    void setSecret(const std::string& secret);
    void setTolerance(int toleranceSeconds);
    
    // Utility methods
    static std::string createSignature(const std::string& payload, const std::string& secret);
    static bool verifyTimestamp(const std::string& timestamp, int toleranceSeconds = 300);
    static std::string getEventType(const std::string& payload);

private:
    std::string secret_;
    int tolerance_seconds_;
    std::map<std::string, std::vector<EventCallback>> event_callbacks_;
    
    void registerDefaultCallbacks();
    void callEventCallbacks(const std::string& eventType, const WebhookEvent& event);
    std::string extractTimestamp(const std::string& payload);
    bool isEventType(const std::string& eventType, const std::string& payload);
};

} // namespace LicenseChain
