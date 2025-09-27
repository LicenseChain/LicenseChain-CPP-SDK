#pragma once

#include "models.h"
#include "exceptions.h"
#include <string>
#include <vector>
#include <map>
#include <future>

namespace LicenseChain {

class LicenseService {
public:
    LicenseService(const std::string& apiKey, const std::string& baseUrl);
    
    // License operations
    std::future<License> createLicenseAsync(const CreateLicenseRequest& request);
    std::future<License> getLicenseAsync(const std::string& licenseId);
    std::future<License> updateLicenseAsync(const std::string& licenseId, const UpdateLicenseRequest& request);
    std::future<void> revokeLicenseAsync(const std::string& licenseId);
    std::future<bool> validateLicenseAsync(const std::string& licenseKey);
    std::future<LicenseListResponse> listUserLicensesAsync(const std::string& userId, int page = 1, int limit = 10);
    std::future<LicenseStats> getLicenseStatsAsync();
    
    // Synchronous versions
    License createLicense(const CreateLicenseRequest& request);
    License getLicense(const std::string& licenseId);
    License updateLicense(const std::string& licenseId, const UpdateLicenseRequest& request);
    void revokeLicense(const std::string& licenseId);
    bool validateLicense(const std::string& licenseKey);
    LicenseListResponse listUserLicenses(const std::string& userId, int page = 1, int limit = 10);
    LicenseStats getLicenseStats();

private:
    std::string api_key_;
    std::string base_url_;
    
    std::string makeRequest(const std::string& method, const std::string& endpoint, const std::string& body = "");
    std::map<std::string, std::string> getHeaders();
};

class UserService {
public:
    UserService(const std::string& apiKey, const std::string& baseUrl);
    
    // User operations
    std::future<User> createUserAsync(const CreateUserRequest& request);
    std::future<User> getUserAsync(const std::string& userId);
    std::future<User> updateUserAsync(const std::string& userId, const UpdateUserRequest& request);
    std::future<void> deleteUserAsync(const std::string& userId);
    std::future<UserListResponse> listUsersAsync(int page = 1, int limit = 10);
    std::future<UserStats> getUserStatsAsync();
    
    // Synchronous versions
    User createUser(const CreateUserRequest& request);
    User getUser(const std::string& userId);
    User updateUser(const std::string& userId, const UpdateUserRequest& request);
    void deleteUser(const std::string& userId);
    UserListResponse listUsers(int page = 1, int limit = 10);
    UserStats getUserStats();

private:
    std::string api_key_;
    std::string base_url_;
    
    std::string makeRequest(const std::string& method, const std::string& endpoint, const std::string& body = "");
    std::map<std::string, std::string> getHeaders();
};

class ProductService {
public:
    ProductService(const std::string& apiKey, const std::string& baseUrl);
    
    // Product operations
    std::future<Product> createProductAsync(const CreateProductRequest& request);
    std::future<Product> getProductAsync(const std::string& productId);
    std::future<Product> updateProductAsync(const std::string& productId, const UpdateProductRequest& request);
    std::future<void> deleteProductAsync(const std::string& productId);
    std::future<ProductListResponse> listProductsAsync(int page = 1, int limit = 10);
    std::future<ProductStats> getProductStatsAsync();
    
    // Synchronous versions
    Product createProduct(const CreateProductRequest& request);
    Product getProduct(const std::string& productId);
    Product updateProduct(const std::string& productId, const UpdateProductRequest& request);
    void deleteProduct(const std::string& productId);
    ProductListResponse listProducts(int page = 1, int limit = 10);
    ProductStats getProductStats();

private:
    std::string api_key_;
    std::string base_url_;
    
    std::string makeRequest(const std::string& method, const std::string& endpoint, const std::string& body = "");
    std::map<std::string, std::string> getHeaders();
};

class WebhookService {
public:
    WebhookService(const std::string& apiKey, const std::string& baseUrl);
    
    // Webhook operations
    std::future<Webhook> createWebhookAsync(const CreateWebhookRequest& request);
    std::future<Webhook> getWebhookAsync(const std::string& webhookId);
    std::future<Webhook> updateWebhookAsync(const std::string& webhookId, const UpdateWebhookRequest& request);
    std::future<void> deleteWebhookAsync(const std::string& webhookId);
    std::future<WebhookListResponse> listWebhooksAsync(int page = 1, int limit = 10);
    
    // Synchronous versions
    Webhook createWebhook(const CreateWebhookRequest& request);
    Webhook getWebhook(const std::string& webhookId);
    Webhook updateWebhook(const std::string& webhookId, const UpdateWebhookRequest& request);
    void deleteWebhook(const std::string& webhookId);
    WebhookListResponse listWebhooks(int page = 1, int limit = 10);

private:
    std::string api_key_;
    std::string base_url_;
    
    std::string makeRequest(const std::string& method, const std::string& endpoint, const std::string& body = "");
    std::map<std::string, std::string> getHeaders();
};

} // namespace LicenseChain
