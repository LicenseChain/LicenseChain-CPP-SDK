# vcpkg port (LicenseChain C++ SDK)

Manifest + classic-port files for `licensechain-cpp-sdk` **1.0.1**.

## In-repo / overlay registry (works today)

```bash
# Overlay port
git clone https://github.com/LicenseChain/LicenseChain-CPP-SDK.git
vcpkg install --overlay-ports=./LicenseChain-CPP-SDK/vcpkg licensechain-cpp-sdk
```

Or add a git-based [vcpkg registry](https://learn.microsoft.com/en-us/vcpkg/concepts/registries) pointing at this repository’s `vcpkg/` folder.

## Opening a microsoft/vcpkg PR

1. Fork [microsoft/vcpkg](https://github.com/microsoft/vcpkg).
2. Copy:
   - `vcpkg/vcpkg.json` → `ports/licensechain-cpp-sdk/vcpkg.json`
   - `vcpkg/portfile.cmake` → `ports/licensechain-cpp-sdk/portfile.cmake`
3. Run `vcpkg x-add-version licensechain-cpp-sdk` (or the current equivalent) and commit version database updates.
4. Open a PR. Expect review questions around **Elastic-2.0** (not OSI) — document that consumers can still use the overlay/git registry if the curated registry rejects the license.

`SHA512` in `portfile.cmake` matches the GitHub tag archive for `v1.0.1`.
