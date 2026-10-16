# LicenseChain C++ SDK Roadmap

## Current Focus

- Keep API v1 endpoint expectations aligned with `https://api.licensechain.app/v1`.
- Preserve thin-client guidance: backend RS256/JWKS verification for production.
- Keep CMake install-from-source path as the supported packaging route.

## Next Operational Tasks

- Re-run conformance checks after Core API verify/JWKS contract updates.
- Keep docs and examples synchronized with https://docs.licensechain.app/en/sdk.
- Record release-impacting changes in `CHANGELOG.md`; develop experiments on `dev`, release from `main`.


## Active Milestone (2026-10-16)

- **Conformance re-run**: workspace `sdk-conformance` validate reports `errors=0` (remaining WARN = optional README PATCH license lifecycle aliases; DELETE/update paths cover revoke).
- **Docs sync**: README points at `https://docs.licensechain.app/en/sdk`; default API base documented as `https://api.licensechain.app/v1`.
- **Branch opsec**: land experiments on `dev`; promote to `main` only for release-ready changes.

## Ecosystem Notes

- Do not reintroduce Conan/vcpkg skeletons unless a maintained publish path exists.
