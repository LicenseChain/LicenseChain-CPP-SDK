# Conan recipe (LicenseChain C++ SDK)

In-repo Conan 2 recipe skeleton for `licensechain-cpp-sdk` **1.0.1**.

## License note

The SDK is licensed under **Elastic-2.0**. Conan Center Index generally prefers OSI-approved licenses; an upstream PR may be rejected or delayed for that reason. Keep this recipe in-repo for consumers who add a git remotes / local recipes folder.

## Local smoke test

```bash
# From this directory (requires Conan 2 + CMake + OpenSSL)
conan create . --version=1.0.1 -o:a="&:shared=False"
```

If `conan create` is run from `conan/` with the files laid out as CCI (`config.yml` + `all/`), use:

```bash
conan create all --version=1.0.1
```

## Opening a Conan Center Index PR

1. Fork [conan-io/conan-center-index](https://github.com/conan-io/conan-center-index).
2. Copy this tree into `recipes/licensechain-cpp-sdk/`:
   - `config.yml`
   - `all/conanfile.py` (copy of `conanfile.py`)
   - `all/conandata.yml` (copy of `conandata.yml`)
   - `all/test_package/` (optional but recommended)
3. Confirm `sha256` in `conandata.yml` matches
   `https://github.com/LicenseChain/LicenseChain-CPP-SDK/archive/refs/tags/v1.0.1.tar.gz`.
4. Run CCI linters / `conan create` per their docs.
5. Open a PR titled along the lines of `licensechain-cpp-sdk/1.0.1`.

Expected blocker: Elastic-2.0 vs CCI open-source policy — escalate to CCI maintainers if needed; git + CMake install remains the supported path.
