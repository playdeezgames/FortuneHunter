#!/bin/bash
# Serves build/web on http://localhost:8080 (override with PORT=...; check the port is free first).
cd "$(dirname "$0")/../build/web" && exec python3 -m http.server "${PORT:-8080}"
