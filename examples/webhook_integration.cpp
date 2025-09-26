// LicenseChain C++ SDK - Webhook Integration Example
// This example demonstrates webhook integration with the LicenseChain C++ SDK

#include <licensechain/licensechain_client.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <map>
#include <vector>
#include <mutex>

class WebhookManager {
private:
    LicenseChain::Client& client;
    std::map<std::string, std::function<void(const std::map<std::string, std::string>&)>> eventHandlers;
    std::thread webhookThread;
    bool running = false;
    std::mutex handlerMutex;
    
public:
    WebhookManager(LicenseChain::Client& client) : client(client) {}
    
    // Set up webhook handler
    void setupWebhookHandler() {
        client.setWebhookHandler([this](const std::string& event, 
                                      const std::map<std::string, std::string>& data) {
            std::lock_guard<std::mutex> lock(handlerMutex);
            
            std::cout << "📨 Webhook received: " << event << std::endl;
            
            // Track webhook event
            client.trackEvent("webhook_received", {
                {"event", event},
                {"timestamp", std::to_string(std::time(nullptr))}
            });
            
            // Handle specific events
            if (event == "license.created") {
                handleLicenseCreated(data);
            } else if (event == "license.updated") {
                handleLicenseUpdated(data);
            } else if (event == "license.revoked") {
                handleLicenseRevoked(data);
            } else if (event == "license.expired") {
                handleLicenseExpired(data);
            } else if (event == "user.registered") {
                handleUserRegistered(data);
            } else if (event == "payment.completed") {
                handlePaymentCompleted(data);
            } else if (event == "payment.failed") {
                handlePaymentFailed(data);
            } else if (event == "payment.refunded") {
                handlePaymentRefunded(data);
            } else if (event == "hardware.bound") {
                handleHardwareBound(data);
            } else if (event == "hardware.unbound") {
                handleHardwareUnbound(data);
            } else if (event == "system.maintenance") {
                handleSystemMaintenance(data);
            } else if (event == "system.update") {
                handleSystemUpdate(data);
            }
        });
        
        std::cout << "🔔 Webhook handler set up successfully!" << std::endl;
    }
    
    // Start webhook listener
    void startWebhookListener() {
        client.startWebhookListener();
        std::cout << "🔔 Webhook listener started!" << std::endl;
    }
    
    // Stop webhook listener
    void stopWebhookListener() {
        client.stopWebhookListener();
        std::cout << "🔔 Webhook listener stopped!" << std::endl;
    }
    
    // Register custom event handler
    void registerEventHandler(const std::string& event, 
                             std::function<void(const std::map<std::string, std::string>&)> handler) {
        std::lock_guard<std::mutex> lock(handlerMutex);
        eventHandlers[event] = handler;
        std::cout << "📝 Registered handler for event: " << event << std::endl;
    }
    
private:
    // Event handlers
    void handleLicenseCreated(const std::map<std::string, std::string>& data) {
        std::cout << "🎉 New license created: " << data.at("licenseKey") << std::endl;
        
        // Notify relevant users
        std::cout << "📢 Notifying users about new license..." << std::endl;
        
        // In a real application, you would:
        // - Send notifications to relevant users
        // - Update user interfaces
        // - Log the event
        // - Update analytics
    }
    
    void handleLicenseUpdated(const std::map<std::string, std::string>& data) {
        std::cout << "🔄 License updated: " << data.at("licenseKey") << std::endl;
        
        // Update license data
        std::cout << "📝 Updating license data..." << std::endl;
        
        // In a real application, you would:
        // - Update cached license data
        // - Refresh user interfaces
        // - Log the changes
    }
    
    void handleLicenseRevoked(const std::map<std::string, std::string>& data) {
        std::cout << "❌ License revoked: " << data.at("licenseKey") << std::endl;
        
        // Remove premium features
        std::cout << "🚫 Removing premium features..." << std::endl;
        
        // In a real application, you would:
        // - Revoke access to premium features
        // - Update user interfaces
        // - Send notifications
        // - Log the revocation
    }
    
    void handleLicenseExpired(const std::map<std::string, std::string>& data) {
        std::cout << "⏰ License expired: " << data.at("licenseKey") << std::endl;
        
        // Handle expired license
        std::cout << "⏳ Handling expired license..." << std::endl;
        
        // In a real application, you would:
        // - Show renewal options
        // - Update user interfaces
        // - Send renewal reminders
        // - Log the expiration
    }
    
    void handleUserRegistered(const std::map<std::string, std::string>& data) {
        std::cout << "👤 User registered: " << data.at("username") << std::endl;
        
        // Send welcome message
        std::cout << "👋 Sending welcome message..." << std::endl;
        
        // In a real application, you would:
        // - Send welcome email
        // - Create user profile
        // - Set up initial settings
        // - Log the registration
    }
    
    void handlePaymentCompleted(const std::map<std::string, std::string>& data) {
        std::cout << "💳 Payment completed: " << data.at("transactionId") << std::endl;
        
        // Grant premium features
        std::cout << "⭐ Granting premium features..." << std::endl;
        
        // In a real application, you would:
        // - Activate premium features
        // - Send confirmation email
        // - Update user account
        // - Log the payment
    }
    
    void handlePaymentFailed(const std::map<std::string, std::string>& data) {
        std::cout << "❌ Payment failed: " << data.at("transactionId") << std::endl;
        
        // Handle payment failure
        std::cout << "⚠️ Handling payment failure..." << std::endl;
        
        // In a real application, you would:
        // - Send failure notification
        // - Retry payment
        // - Update user account
        // - Log the failure
    }
    
    void handlePaymentRefunded(const std::map<std::string, std::string>& data) {
        std::cout << "💰 Payment refunded: " << data.at("transactionId") << std::endl;
        
        // Handle refund
        std::cout << "🔄 Processing refund..." << std::endl;
        
        // In a real application, you would:
        // - Revoke premium features
        // - Send refund notification
        // - Update user account
        // - Log the refund
    }
    
    void handleHardwareBound(const std::map<std::string, std::string>& data) {
        std::cout << "🔗 Hardware bound: " << data.at("hardwareId") << std::endl;
        
        // Handle hardware binding
        std::cout << "🖥️ Processing hardware binding..." << std::endl;
        
        // In a real application, you would:
        // - Update license binding
        // - Send confirmation
        // - Log the binding
    }
    
    void handleHardwareUnbound(const std::map<std::string, std::string>& data) {
        std::cout << "🔓 Hardware unbound: " << data.at("hardwareId") << std::endl;
        
        // Handle hardware unbinding
        std::cout << "🖥️ Processing hardware unbinding..." << std::endl;
        
        // In a real application, you would:
        // - Update license binding
        // - Send notification
        // - Log the unbinding
    }
    
    void handleSystemMaintenance(const std::map<std::string, std::string>& data) {
        std::cout << "🔧 System maintenance: " << data.at("message") << std::endl;
        
        // Handle maintenance mode
        std::cout << "⚠️ Entering maintenance mode..." << std::endl;
        
        // In a real application, you would:
        // - Show maintenance message
        // - Disable certain features
        // - Log the maintenance
    }
    
    void handleSystemUpdate(const std::map<std::string, std::string>& data) {
        std::cout << "🔄 System update: " << data.at("version") << std::endl;
        
        // Handle system update
        std::cout << "📦 Processing system update..." << std::endl;
        
        // In a real application, you would:
        // - Update system components
        // - Notify users
        // - Log the update
    }
};

class NotificationManager {
private:
    std::vector<std::string> notifications;
    std::mutex notificationMutex;
    
public:
    void addNotification(const std::string& message) {
        std::lock_guard<std::mutex> lock(notificationMutex);
        notifications.push_back(message);
        std::cout << "📢 Notification: " << message << std::endl;
    }
    
    std::vector<std::string> getNotifications() {
        std::lock_guard<std::mutex> lock(notificationMutex);
        return notifications;
    }
    
    void clearNotifications() {
        std::lock_guard<std::mutex> lock(notificationMutex);
        notifications.clear();
        std::cout << "🗑️ Notifications cleared" << std::endl;
    }
};

int main() {
    std::cout << "🚀 LicenseChain C++ SDK - Webhook Integration Example" << std::endl;
    std::cout << "=" << std::string(60, '=') << std::endl;
    
    // Initialize the client
    LicenseChain::Client client({
        .apiKey = "your-api-key-here",
        .appName = "WebhookCppApp",
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
    
    // Initialize webhook manager
    WebhookManager webhookManager(client);
    NotificationManager notificationManager;
    
    // Set up webhook handler
    webhookManager.setupWebhookHandler();
    
    // Register custom event handlers
    webhookManager.registerEventHandler("custom.event", [&notificationManager](
        const std::map<std::string, std::string>& data) {
        notificationManager.addNotification("Custom event received: " + data.at("message"));
    });
    
    // Start webhook listener
    webhookManager.startWebhookListener();
    
    // Simulate some webhook events (in a real application, these would come from the server)
    std::cout << "\n🎭 Simulating webhook events..." << std::endl;
    
    // Simulate license created event
    std::cout << "\n📨 Simulating license.created event..." << std::endl;
    client.setWebhookHandler()("license.created", {
        {"licenseKey", "LICENSE-12345"},
        {"userId", "user123"},
        {"features", "premium,unlimited"}
    });
    
    // Simulate license updated event
    std::cout << "\n📨 Simulating license.updated event..." << std::endl;
    client.setWebhookHandler()("license.updated", {
        {"licenseKey", "LICENSE-12345"},
        {"status", "active"},
        {"expires", "2024-12-31"}
    });
    
    // Simulate payment completed event
    std::cout << "\n📨 Simulating payment.completed event..." << std::endl;
    client.setWebhookHandler()("payment.completed", {
        {"transactionId", "TXN-67890"},
        {"amount", "9.99"},
        {"currency", "USD"}
    });
    
    // Simulate custom event
    std::cout << "\n📨 Simulating custom.event..." << std::endl;
    client.setWebhookHandler()("custom.event", {
        {"message", "Hello from webhook!"},
        {"timestamp", std::to_string(std::time(nullptr))}
    });
    
    // Wait for webhook processing
    std::cout << "\n⏳ Waiting for webhook processing..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // Show notifications
    std::cout << "\n📢 Notifications received:" << std::endl;
    auto notifications = notificationManager.getNotifications();
    for (size_t i = 0; i < notifications.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << notifications[i] << std::endl;
    }
    
    // Demonstrate webhook verification
    std::cout << "\n🔐 Webhook Verification..." << std::endl;
    
    // In a real application, you would verify webhook signatures
    std::string payload = "{\"event\":\"test\",\"data\":{}}";
    std::string signature = "sha256=abc123...";
    std::string secret = "your-webhook-secret";
    
    // Verify signature (this would be implemented in the real SDK)
    std::cout << "🔍 Verifying webhook signature..." << std::endl;
    std::cout << "Payload: " << payload << std::endl;
    std::cout << "Signature: " << signature << std::endl;
    std::cout << "Secret: " << secret << std::endl;
    
    // Cleanup
    std::cout << "\n🧹 Cleaning up..." << std::endl;
    webhookManager.stopWebhookListener();
    client.logout();
    client.disconnect();
    
    std::cout << "✅ Cleanup completed!" << std::endl;
    std::cout << "\n🎉 Webhook integration example completed!" << std::endl;
    
    return 0;
}
