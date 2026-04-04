# JWKS-only reference (C++)

The C++ SDK exposes claim constants in `license_assertion.h`; RS256 verification and JWKS fetch are **integrator-owned** (OpenSSL, jwt-cpp, or a small backend).

## Runnable: fetch JWKS (shell)

From this directory:

```bash
chmod +x fetch_jwks.sh
./fetch_jwks.sh
```

Uses `curl` to call `https://api.licensechain.app/v1/licenses/jwks` (override with `LICENSECHAIN_JWKS_URL`).

## Full token verify

Use the **C#** sample as the canonical runnable verifier:

- [LicenseChain-CSharp-SDK/examples/jwks_only](https://github.com/LicenseChain/LicenseChain-CSharp-SDK/tree/main/examples/jwks_only)

Claim contract: `token_use` = `licensechain_license_v1`; verify against keys from JWKS for the JWT `kid`.

See also [JWKS_THIN_CLIENT_QUICKREF.md](https://github.com/LicenseChain/sdks/blob/main/docs/JWKS_THIN_CLIENT_QUICKREF.md) in the umbrella **sdks** repo.
