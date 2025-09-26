#pragma once

#include <string>
#include <memory>
#include <future>
#include <map>
#include <vector>
#include "models.h"
#include "exceptions.h"

namespace licensechain {

/**
 * Main client for interacting with the LicenseChain API
 */
class LicenseChainClient {
public:
    /**
     * Constructor
     * @param apiKey Your LicenseChain API key
     * @param baseUrl Base URL for the LicenseChain API (optional)
     * @param timeout Request timeout in seconds (optional, default: 30)
     */
    LicenseChainClient(const std::string& apiKey, 
                      const std::string& baseUrl = "https://api.licensechain.app",
                      int timeout = 30);

    /**
     * Destructor
     */
    ~LicenseChainClient();

    // Authentication Methods

    /**
     * Register a new user
     * @param request User registration request
     * @return Future containing the registered user
     */
    std::future<User> RegisterUserAsync(const UserRegistrationRequest& request);

    /**
     * Login with email and password
     * @param request Login request
     * @return Future containing the login response
     */
    std::future<LoginResponse> LoginAsync(const LoginRequest& request);

    /**
     * Logout the current user
     * @return Future that completes when logout is done
     */
    std::future<void> LogoutAsync();

    /**
     * Refresh authentication token
     * @param refreshToken The refresh token
     * @return Future containing the token refresh response
     */
    std::future<TokenRefreshResponse> RefreshTokenAsync(const std::string& refreshToken);

    /**
     * Get current user profile
     * @return Future containing the user profile
     */
    std::future<User> GetUserProfileAsync();

    /**
     * Update user profile
     * @param request User update request
     * @return Future containing the updated user
     */
    std::future<User> UpdateUserProfileAsync(const UserUpdateRequest& request);

    /**
     * Change user password
     * @param request Password change request
     * @return Future that completes when password is changed
     */
    std::future<void> ChangePasswordAsync(const PasswordChangeRequest& request);

    /**
     * Request password reset
     * @param email User email
     * @return Future that completes when request is sent
     */
    std::future<void> RequestPasswordResetAsync(const std::string& email);

    /**
     * Reset password with token
     * @param request Password reset request
     * @return Future that completes when password is reset
     */
    std::future<void> ResetPasswordAsync(const PasswordResetRequest& request);

    // Application Management

    /**
     * Create a new application
     * @param request Application create request
     * @return Future containing the created application
     */
    std::future<Application> CreateApplicationAsync(const ApplicationCreateRequest& request);

    /**
     * List applications with pagination
     * @param request Application list request
     * @return Future containing the paginated response
     */
    std::future<PaginatedResponse<Application>> ListApplicationsAsync(const ApplicationListRequest& request);

    /**
     * Get application details
     * @param appId Application ID
     * @return Future containing the application
     */
    std::future<Application> GetApplicationAsync(const std::string& appId);

    /**
     * Update application
     * @param appId Application ID
     * @param request Application update request
     * @return Future containing the updated application
     */
    std::future<Application> UpdateApplicationAsync(const std::string& appId, const ApplicationUpdateRequest& request);

    /**
     * Delete application
     * @param appId Application ID
     * @return Future that completes when application is deleted
     */
    std::future<void> DeleteApplicationAsync(const std::string& appId);

    /**
     * Regenerate API key for application
     * @param appId Application ID
     * @return Future containing the new API key
     */
    std::future<ApiKeyResponse> RegenerateApiKeyAsync(const std::string& appId);

    // License Management

    /**
     * Create a new license
     * @param request License create request
     * @return Future containing the created license
     */
    std::future<License> CreateLicenseAsync(const LicenseCreateRequest& request);

    /**
     * List licenses with filters
     * @param request License list request
     * @return Future containing the paginated response
     */
    std::future<PaginatedResponse<License>> ListLicensesAsync(const LicenseListRequest& request);

    /**
     * Get license details
     * @param licenseId License ID
     * @return Future containing the license
     */
    std::future<License> GetLicenseAsync(const std::string& licenseId);

    /**
     * Update license
     * @param licenseId License ID
     * @param request License update request
     * @return Future containing the updated license
     */
    std::future<License> UpdateLicenseAsync(const std::string& licenseId, const LicenseUpdateRequest& request);

    /**
     * Delete license
     * @param licenseId License ID
     * @return Future that completes when license is deleted
     */
    std::future<void> DeleteLicenseAsync(const std::string& licenseId);

    /**
     * Validate a license key
     * @param licenseKey License key to validate
     * @param appId Application ID (optional)
     * @return Future containing the validation result
     */
    std::future<LicenseValidationResult> ValidateLicenseAsync(const std::string& licenseKey, const std::string& appId = "");

    /**
     * Revoke a license
     * @param licenseId License ID
     * @param reason Revocation reason (optional)
     * @return Future that completes when license is revoked
     */
    std::future<void> RevokeLicenseAsync(const std::string& licenseId, const std::string& reason = "");

    /**
     * Activate a license
     * @param licenseId License ID
     * @return Future that completes when license is activated
     */
    std::future<void> ActivateLicenseAsync(const std::string& licenseId);

    /**
     * Extend license expiration
     * @param licenseId License ID
     * @param expiresAt New expiration date
     * @return Future that completes when license is extended
     */
    std::future<void> ExtendLicenseAsync(const std::string& licenseId, const std::string& expiresAt);

    // Webhook Management

    /**
     * Create a webhook
     * @param request Webhook create request
     * @return Future containing the created webhook
     */
    std::future<Webhook> CreateWebhookAsync(const WebhookCreateRequest& request);

    /**
     * List webhooks
     * @param request Webhook list request
     * @return Future containing the paginated response
     */
    std::future<PaginatedResponse<Webhook>> ListWebhooksAsync(const WebhookListRequest& request);

    /**
     * Get webhook details
     * @param webhookId Webhook ID
     * @return Future containing the webhook
     */
    std::future<Webhook> GetWebhookAsync(const std::string& webhookId);

    /**
     * Update webhook
     * @param webhookId Webhook ID
     * @param request Webhook update request
     * @return Future containing the updated webhook
     */
    std::future<Webhook> UpdateWebhookAsync(const std::string& webhookId, const WebhookUpdateRequest& request);

    /**
     * Delete webhook
     * @param webhookId Webhook ID
     * @return Future that completes when webhook is deleted
     */
    std::future<void> DeleteWebhookAsync(const std::string& webhookId);

    /**
     * Test webhook
     * @param webhookId Webhook ID
     * @return Future that completes when webhook is tested
     */
    std::future<void> TestWebhookAsync(const std::string& webhookId);

    // Analytics

    /**
     * Get analytics data
     * @param request Analytics request
     * @return Future containing the analytics data
     */
    std::future<Analytics> GetAnalyticsAsync(const AnalyticsRequest& request);

    /**
     * Get license analytics
     * @param licenseId License ID
     * @return Future containing the analytics data
     */
    std::future<Analytics> GetLicenseAnalyticsAsync(const std::string& licenseId);

    /**
     * Get usage statistics
     * @param request Usage stats request
     * @return Future containing the usage statistics
     */
    std::future<UsageStats> GetUsageStatsAsync(const UsageStatsRequest& request);

    // System Status

    /**
     * Get system status
     * @return Future containing the system status
     */
    std::future<SystemStatus> GetSystemStatusAsync();

    /**
     * Get health check
     * @return Future containing the health check
     */
    std::future<HealthCheck> GetHealthCheckAsync();

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace licensechain
