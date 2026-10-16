# LicenseChain C++ SDK Roadmap

## Current Focus

- Keep API v1 endpoint expectations aligned with `https://api.licensechain.app/v1`.
- Preserve thin-client guidance: backend RS256/JWKS verification for production.
- Keep CMake install-from-source path as the supported packaging route.

## Next Operational Tasks

- Re-run conformance checks after Core API verify/JWKS contract updates.
- Keep docs and examples synchronized with https://docs.licensechain.app/en/sdk.
- Record release-impacting changes in `CHANGELOG.md`; develop experiments on `dev`, release from `main`.

## Ecosystem Notes

- Do not reintroduce Conan/vcpkg skeletons unless a maintained publish path exists.
