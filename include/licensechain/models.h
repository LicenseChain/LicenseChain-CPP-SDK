#pragma once

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <optional>

namespace LicenseChain {

struct License {
    std::string id;
    std::string user_id;
    std::string product_id;
    std::string license_key;
    std::string status;
    std::chrono::system_clock::time_point created_at;
    std::chrono::system_clock::time_point updated_at;
    std::optional<std::chrono::system_clock::time_point> expires_at;
    std::map<std::string, std::string> metadata;
};

struct CreateLicenseRequest {
    std::string user_id;
    std::string product_id;
    std::map<std::string, std::string> metadata;
};

struct UpdateLicenseRequest {
    std::optional<std::string> status;
    std::optional<std::chrono::system_clock::time_point> expires_at;
    std::map<std::string, std::string> metadata;
};

struct LicenseListResponse {
    std::vector<License> data;
    int total;
    int page;
    int limit;
};

struct LicenseStats {
    int total;
    int active;
    int expired;
    int revoked;
    double revenue;
};

struct User {
    std::string id;
    std::string email;
    std::string name;
    std::chrono::system_clock::time_point created_at;
    std::chrono::system_clock::time_point updated_at;
    std::map<std::string, std::string> metadata;
};

struct CreateUserRequest {
    std::string email;
    std::string name;
    std::map<std::string, std::string> metadata;
};

struct UpdateUserRequest {
    std::optional<std::string> email;
    std::optional<std::string> name;
    std::map<std::string, std::string> metadata;
};

struct UserListResponse {
    std::vector<User> data;
    int total;
    int page;
    int limit;
};

struct UserStats {
    int total;
    int active;
    int inactive;
};

struct Product {
    std::string id;
    std::string name;
    std::optional<std::string> description;
    double price;
    std::string currency;
    std::chrono::system_clock::time_point created_at;
    std::chrono::system_clock::time_point updated_at;
    std::map<std::string, std::string> metadata;
};

struct CreateProductRequest {
    std::string name;
    std::optional<std::string> description;
    double price;
    std::string currency;
    std::map<std::string, std::string> metadata;
};

struct UpdateProductRequest {
    std::optional<std::string> name;
    std::optional<std::string> description;
    std::optional<double> price;
    std::optional<std::string> currency;
    std::map<std::string, std::string> metadata;
};

struct ProductListResponse {
    std::vector<Product> data;
    int total;
    int page;
    int limit;
};

struct ProductStats {
    int total;
    int active;
    double revenue;
};

struct Webhook {
    std::string id;
    std::string url;
    std::vector<std::string> events;
    std::optional<std::string> secret;
    std::chrono::system_clock::time_point created_at;
    std::chrono::system_clock::time_point updated_at;
};

struct CreateWebhookRequest {
    std::string url;
    std::vector<std::string> events;
    std::optional<std::string> secret;
};

struct UpdateWebhookRequest {
    std::optional<std::string> url;
    std::optional<std::vector<std::string>> events;
    std::optional<std::string> secret;
};

struct WebhookListResponse {
    std::vector<Webhook> data;
    int total;
    int page;
    int limit;
};

struct WebhookEvent {
    std::string id;
    std::string type;
    std::string data;
    std::chrono::system_clock::time_point timestamp;
    std::string signature;
};

struct HealthResponse {
    std::string status;
    std::string timestamp;
    std::string version;
};

struct PingResponse {
    std::string message;
    std::string time;
};

} // namespace LicenseChain
