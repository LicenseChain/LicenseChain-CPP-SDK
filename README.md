# LicenseChain C++ SDK

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C++-17+-blue.svg)](https://en.cppreference.com/)
[![CMake](https://img.shields.io/badge/CMake-3.10+-green.svg)](https://cmake.org/)

Official C++ SDK for LicenseChain - Secure license management for C++ applications.

## ðŸš€ Features

- **ðŸ” Secure Authentication** - User registration, login, and session management
- **ðŸ“œ License Management** - Create, validate, update, and revoke licenses
- **ðŸ›¡ï¸ Hardware ID Validation** - Prevent license sharing and unauthorized access
- **ðŸ”” Webhook Support** - Real-time license events and notifications
- **ðŸ“Š Analytics Integration** - Track license usage and performance metrics
- **âš¡ High Performance** - Optimized for production workloads
- **ðŸ”„ Async Operations** - Non-blocking HTTP requests and data processing
- **ðŸ› ï¸ Easy Integration** - Simple API with comprehensive documentation

## ðŸ“¦ Installation

### Method 1: CMake (Recommended)

```bash
# Clone the repository
git clone https://github.com/LicenseChain/LicenseChain-CPP-SDK.git
cd LicenseChain-CPP-SDK

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the library
make -j$(nproc)

# Install (optional)
sudo make install
```

### Method 2: Package Manager

Add to your `CMakeLists.txt`:

```cmake
find_package(LicenseChain REQUIRED)
target_link_libraries(your_target LicenseChain::LicenseChain)
```

### Method 3: Manual Installation

1. Download the latest release from [GitHub Releases](https://github.com/LicenseChain/LicenseChain-CPP-SDK/releases)
2. Extract the headers and libraries to your project
3. Link against the LicenseChain library

## ðŸš€ Quick Start

### Basic Setup

```cpp
#include <licensechain/licensechain_client.h>
#include <iostream>

int main() {
    // Initialize the client
    LicenseChain::Client client({
        .apiKey = "your-api-key",
        .appName = "your-app-name",
        .version = "1.0.0"
    });
    
    // Connect to LicenseChain
    auto result = client.connect();
    if (!result.success) {
        std::cerr << "Failed to connect to LicenseChain: " << result.error << std::endl;
        return 1;
    }
    
    std::cout << "Connected to LicenseChain successfully!" << std::endl;
    return 0;
}
```

### User Authentication

```cpp
// Register a new user
auto registerResult = client.register("username", "password", "email@example.com");
if (registerResult.success) {
    std::cout << "User registered successfully!" << std::endl;
} else {
    std::cerr << "Registration failed: " << registerResult.error << std::endl;
}

// Login existing user
auto loginResult = client.login("username", "password");
if (loginResult.success) {
    std::cout << "User logged in successfully!" << std::endl;
    std::cout << "Session ID: " << loginResult.sessionId << std::endl;
} else {
    std::cerr << "Login failed: " << loginResult.error << std::endl;
}
```

### License Management

```cpp
// Validate a license
auto validateResult = client.validateLicense("LICENSE-KEY-HERE");
if (validateResult.success) {
    std::cout << "License is valid!" << std::endl;
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
    std::cerr << "License validation failed: " << validateResult.error << std::endl;
}

// Get user's licenses
auto licensesResult = client.getUserLicenses();
if (licensesResult.success) {
    std::cout << "Found " << licensesResult.licenses.size() << " licenses:" << std::endl;
    for (size_t i = 0; i < licensesResult.licenses.size(); ++i) {
        const auto& license = licensesResult.licenses[i];
        std::cout << "  " << (i + 1) << ". " << license.key 
                  << " - " << license.status 
                  << " (Expires: " << license.expires << ")" << std::endl;
    }
}
```

### Hardware ID Validation

```cpp
// Get hardware ID (automatically generated)
std::string hardwareId = client.getHardwareId();
std::cout << "Hardware ID: " << hardwareId << std::endl;

// Validate hardware ID with license
auto hardwareResult = client.validateHardwareId("LICENSE-KEY-HERE", hardwareId);
if (hardwareResult.success) {
    std::cout << "Hardware ID is valid for this license!" << std::endl;
} else {
    std::cerr << "Hardware ID validation failed: " << hardwareResult.error << std::endl;
}
```

### Webhook Integration

```cpp
// Set up webhook handler
client.setWebhookHandler([](const std::string& event, const std::map<std::string, std::string>& data) {
    std::cout << "Webhook received: " << event << std::endl;
    
    if (event == "license.created") {
        std::cout << "New license created: " << data.at("licenseKey") << std::endl;
    } else if (event == "license.updated") {
        std::cout << "License updated: " << data.at("licenseKey") << std::endl;
    } else if (event == "license.revoked") {
        std::cout << "License revoked: " << data.at("licenseKey") << std::endl;
    }
});

// Start webhook listener
client.startWebhookListener();
```

## ðŸ“š API Reference

### LicenseChain::Client

#### Constructor

```cpp
LicenseChain::Client client({
    .apiKey = "your-api-key",
    .appName = "your-app-name",
    .version = "1.0.0",
    .baseUrl = "https://api.licensechain.app"  // Optional
});
```

#### Methods

##### Connection Management

```cpp
// Connect to LicenseChain
auto result = client.connect();

// Disconnect from LicenseChain
client.disconnect();

// Check connection status
bool isConnected = client.isConnected();
```

##### User Authentication

```cpp
// Register a new user
auto result = client.register(username, password, email);

// Login existing user
auto result = client.login(username, password);

// Logout current user
client.logout();

// Get current user info
auto user = client.getCurrentUser();
```

##### License Management

```cpp
// Validate a license
auto result = client.validateLicense(licenseKey);

// Get user's licenses
auto result = client.getUserLicenses();

// Create a new license
auto result = client.createLicense(userId, features, expires);

// Update a license
auto result = client.updateLicense(licenseKey, updates);

// Revoke a license
auto result = client.revokeLicense(licenseKey);

// Extend a license
auto result = client.extendLicense(licenseKey, days);
```

##### Hardware ID Management

```cpp
// Get hardware ID
std::string hardwareId = client.getHardwareId();

// Validate hardware ID
auto result = client.validateHardwareId(licenseKey, hardwareId);

// Bind hardware ID to license
auto result = client.bindHardwareId(licenseKey, hardwareId);
```

##### Webhook Management

```cpp
// Set webhook handler
client.setWebhookHandler(handler);

// Start webhook listener
client.startWebhookListener();

// Stop webhook listener
client.stopWebhookListener();
```

##### Analytics

```cpp
// Track event
client.trackEvent(eventName, properties);

// Get analytics data
auto result = client.getAnalytics(timeRange);
```

## ðŸ”§ Configuration

### Environment Variables

Set these in your environment or through your build process:

```bash
# Required
export LICENSECHAIN_API_KEY=your-api-key
export LICENSECHAIN_APP_NAME=your-app-name
export LICENSECHAIN_APP_VERSION=1.0.0

# Optional
export LICENSECHAIN_BASE_URL=https://api.licensechain.app
export LICENSECHAIN_DEBUG=true
```

### Advanced Configuration

```cpp
LicenseChain::Client client({
    .apiKey = "your-api-key",
    .appName = "your-app-name",
    .version = "1.0.0",
    .baseUrl = "https://api.licensechain.app",
    .timeout = 30, // Request timeout in seconds
    .retries = 3,  // Number of retry attempts
    .debug = false // Enable debug logging
});
```

## ðŸ›¡ï¸ Security Features

### Hardware ID Protection

The SDK automatically generates and manages hardware IDs to prevent license sharing:

```cpp
// Hardware ID is automatically generated and stored
std::string hardwareId = client.getHardwareId();

// Validate against license
auto isValid = client.validateHardwareId(licenseKey, hardwareId);
```

### Secure Communication

- All API requests use HTTPS
- API keys are securely stored and transmitted
- Session tokens are automatically managed
- Webhook signatures are verified

### License Validation

- Real-time license validation
- Hardware ID binding
- Expiration checking
- Feature-based access control

## ðŸ“Š Analytics and Monitoring

### Event Tracking

```cpp
// Track custom events
client.trackEvent("app.started", {
    {"level", 1},
    {"playerCount", 10}
});

// Track license events
client.trackEvent("license.validated", {
    {"licenseKey", "LICENSE-KEY"},
    {"features", "premium,unlimited"}
});
```

### Performance Monitoring

```cpp
// Get performance metrics
auto metrics = client.getPerformanceMetrics();
std::cout << "API Response Time: " << metrics.avgResponseTime << "ms" << std::endl;
std::cout << "Success Rate: " << (metrics.successRate * 100) << "%" << std::endl;
std::cout << "Error Count: " << metrics.errorCount << std::endl;
```

## ðŸ”„ Error Handling

### Custom Error Types

```cpp
try {
    auto result = client.validateLicense("invalid-key");
    if (!result.success) {
        switch (result.errorType) {
            case LicenseChain::ErrorType::INVALID_LICENSE:
                std::cerr << "License key is invalid" << std::endl;
                break;
            case LicenseChain::ErrorType::EXPIRED_LICENSE:
                std::cerr << "License has expired" << std::endl;
                break;
            case LicenseChain::ErrorType::NETWORK_ERROR:
                std::cerr << "Network connection failed" << std::endl;
                break;
        }
    }
} catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
}
```

### Retry Logic

```cpp
// Automatic retry for network errors
LicenseChain::Client client({
    .apiKey = "your-api-key",
    .appName = "your-app-name",
    .version = "1.0.0",
    .retries = 3, // Retry up to 3 times
    .retryDelay = 1000 // Wait 1 second between retries
});
```

## ðŸ§ª Testing

### Unit Tests

```bash
# Run tests
cd build
ctest --output-on-failure
```

### Integration Tests

```bash
# Test with real API
./tests/integration_tests
```

## ðŸ“ Examples

See the `examples/` directory for complete examples:

- `basic_usage.cpp` - Basic SDK usage
- `advanced_features.cpp` - Advanced features and configuration
- `webhook_integration.cpp` - Webhook handling

## ðŸ¤ Contributing

We welcome contributions! Please see our [Contributing Guide](CONTRIBUTING.md) for details.

### Development Setup

1. Clone the repository
2. Install dependencies: `sudo apt-get install libcurl4-openssl-dev`
3. Build: `mkdir build && cd build && cmake .. && make`
4. Test: `ctest`

## ðŸ“„ License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## ðŸ†˜ Support

- **Documentation**: [https://docs.licensechain.app/cpp](https://docs.licensechain.app/cpp)
- **Issues**: [GitHub Issues](https://github.com/LicenseChain/LicenseChain-CPP-SDK/issues)
- **Discord**: [LicenseChain Discord](https://discord.gg/licensechain)
- **Email**: support@licensechain.app

## ðŸ”— Related Projects

- [LicenseChain JavaScript SDK](https://github.com/LicenseChain/LicenseChain-JavaScript-SDK)
- [LicenseChain Python SDK](https://github.com/LicenseChain/LicenseChain-Python-SDK)
- [LicenseChain Node.js SDK](https://github.com/LicenseChain/LicenseChain-NodeJS-SDK)
- [LicenseChain Customer Panel](https://github.com/LicenseChain/LicenseChain-Customer-Panel)

---

**Made with â¤ï¸ for the C++ community**


## API Endpoints

All endpoints automatically use the /v1 prefix when connecting to https://api.licensechain.app.

### Base URL
- **Production**: https://api.licensechain.app/v1\n- **Development**: https://api.licensechain.app/v1\n\n### Available Endpoints\n\n| Method | Endpoint | Description |\n|--------|----------|-------------|\n| GET | /v1/health | Health check |\n| POST | /v1/auth/login | User login |\n| POST | /v1/auth/register | User registration |\n| GET | /v1/apps | List applications |\n| POST | /v1/apps | Create application |\n| GET | /v1/licenses | List licenses |\n| POST | /v1/licenses/verify | Verify license |\n| GET | /v1/webhooks | List webhooks |\n| POST | /v1/webhooks | Create webhook |\n| GET | /v1/analytics | Get analytics |\n\n**Note**: The SDK automatically prepends /v1 to all endpoints, so you only need to specify the path (e.g., /auth/login instead of /v1/auth/login).

