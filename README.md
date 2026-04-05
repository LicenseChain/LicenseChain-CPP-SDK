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

## License assertion JWT (RS256 + JWKS)

**API base:** `https://api.licensechain.app/v1`

Successful **`POST /v1/licenses/verify`** may include **`license_token`**, **`license_token_expires_at`**, and **`license_jwks_uri`**. The JWT must carry **`token_use`** = **`licensechain_license_v1`** (see **`licensechain::LICENSE_TOKEN_USE_CLAIM`** in `include/licensechain/license_assertion.h`).

**RS256 + JWKS:** Fetch **`GET /v1/licenses/jwks`**, select the JWK by JWT **`kid`**, and verify RS256 with your preferred crypto stack (OpenSSL, etc.), or delegate verification to a **backend**.

**C++:** This package does not ship a full JWT implementation; integrators own HTTP/JWT. For a runnable JWKS-only reference in .NET, see [LicenseChain-CSharp-SDK/examples/jwks_only](https://github.com/LicenseChain/LicenseChain-CSharp-SDK/tree/main/examples/jwks_only). See [THIN_CLIENT_PARITY](https://github.com/LicenseChain/sdks/blob/main/docs/THIN_CLIENT_PARITY.md) and [JWKS_THIN_CLIENT_QUICKREF](https://github.com/LicenseChain/sdks/blob/main/docs/JWKS_THIN_CLIENT_QUICKREF.md).

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
    // Initialize API client
    licensechain::LicenseChainClient client(
        "your-api-key",
        "https://api.licensechain.app",
        30
    );

    // Example: health endpoint (via GetHealthCheckAsync)
    auto healthFuture = client.GetHealthCheckAsync();
    auto health = healthFuture.get();
    std::cout << "Health status request completed." << std::endl;

    return 0;
}
```

### User Authentication

```cpp
LicenseChain::UserRegistrationRequest registerRequest;
registerRequest.email = "email@example.com";
registerRequest.password = "strong-password";
registerRequest.name = "Example User";
auto user = client.RegisterUserAsync(registerRequest).get();
std::cout << "User registered: " << user.email << std::endl;
```

### License Management

```cpp
auto validation = client.ValidateLicenseAsync("LICENSE-KEY-HERE").get();
std::cout << "Valid: " << (validation.valid ? "true" : "false") << std::endl;

auto stats = client.GetAnalyticsAsync(LicenseChain::AnalyticsRequest{}).get();
std::cout << "Analytics request completed." << std::endl;
```

## ðŸ“š API Reference

### licensechain::LicenseChainClient

#### Constructor

```cpp
licensechain::LicenseChainClient client(
    "your-api-key",
    "https://api.licensechain.app",
    30
);
```

#### Methods

##### User Authentication

```cpp
// Register a new user
auto result = client.RegisterUserAsync(request).get();

// Get current user info
auto user = client.GetUserProfileAsync().get();
```

##### License Management

```cpp
// Validate a license
auto result = client.ValidateLicenseAsync(licenseKey).get();

// Create a new license
auto result = client.CreateLicenseAsync(request).get();

// Update a license
auto result = client.UpdateLicenseAsync(licenseId, request).get();

// Revoke a license
client.RevokeLicenseAsync(licenseId).get();

// Extend a license
client.ExtendLicenseAsync(licenseId, "2027-01-01T00:00:00Z").get();
```

##### Analytics

```cpp
// Get analytics data
auto result = client.GetAnalyticsAsync(request).get();
```

## ðŸ”§ Configuration

### Environment Variables

Set these in your environment or through your build process:

```bash
# Required
export LICENSECHAIN_API_KEY=your-api-key

# Optional
export LICENSECHAIN_BASE_URL=https://api.licensechain.app
export LICENSECHAIN_DEBUG=true
```

### Advanced Configuration

```cpp
licensechain::LicenseChainClient client(
    "your-api-key",
    "https://api.licensechain.app",
    30
);
```

## ðŸ›¡ï¸ Security Features

### Secure Communication

- All API requests use HTTPS
- API keys are securely stored and transmitted
- Webhook signatures are verified

### License Validation

- Real-time license validation
- Expiration checking

## ðŸ“Š Analytics and Monitoring

### Statistics

```cpp
auto analytics = client.GetAnalyticsAsync(request).get();
auto usage = client.GetUsageStatsAsync(request).get();
```

## ðŸ”„ Error Handling

### Custom Error Types

```cpp
try {
    auto result = client.ValidateLicenseAsync("invalid-key").get();
    (void)result;
} catch (const LicenseChain::ValidationException& e) {
    std::cerr << "Validation error: " << e.what() << std::endl;
} catch (const LicenseChain::NetworkException& e) {
    std::cerr << "Network error: " << e.what() << std::endl;
} catch (const LicenseChain::LicenseChainException& e) {
    std::cerr << "LicenseChain error: " << e.what() << std::endl;
} catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
}
```

### Retry Logic

```cpp
// Configure timeout at client construction
licensechain::LicenseChainClient client(
    "your-api-key",
    "https://api.licensechain.app",
    30
);
```

## ðŸ§ª Testing

### Unit Tests

```bash
# Run tests
cd build
ctest --output-on-failure
```

### Integration Tests

Integration tests are repository-specific and may not be present in all snapshots.

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
- **Production**: https://api.licensechain.app/v1
- **Development**: https://api.licensechain.app/v1

### Available Endpoints

| Method | Endpoint | Description |
|--------|----------|-------------|
| GET | /v1/health | Health check |
| POST | /v1/auth/register | User registration |
| GET | /v1/auth/me | Current authenticated user |
| GET | /v1/apps | List applications |
| POST | /v1/apps/:id/licenses | Create license for app |
| POST | /v1/licenses/verify | Verify license |
| PATCH | /v1/licenses/:id/revoke | Revoke license |
| PATCH | /v1/licenses/:id/activate | Activate license |
| PATCH | /v1/licenses/:id/extend | Extend license |
| GET | /v1/webhooks | List webhooks |
| POST | /v1/webhooks | Create webhook |
| GET | /v1/analytics/stats | Get analytics |

**Note**: The SDK automatically prepends /v1 to all endpoints.


## LicenseChain API (v1)

This SDK targets the **LicenseChain HTTP API v1** implemented by the open-source API service.

- **Production base URL:** https://api.licensechain.app/v1
- **API repository (source of routes & behavior):** https://github.com/LicenseChain/api
- **Baseline REST mapping (documented for integrators):**
  - GET /health
  - POST /auth/register
  - POST /licenses/verify
  - PATCH /licenses/:id/revoke
  - PATCH /licenses/:id/activate
  - PATCH /licenses/:id/extend
  - GET /analytics/stats

