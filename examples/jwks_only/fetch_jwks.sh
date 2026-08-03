#!/usr/bin/env sh
# Fetch public JWKS for license assertion JWT verification (no token verify; C++ integrators use this smoke test).
set -eu
URL="${LICENSECHAIN_JWKS_URL:-https://api.licensechain.app/v1/licenses/jwks}"
curl -sS -f "$URL" | head -c 4000
echo
