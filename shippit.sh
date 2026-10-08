#!/bin/bash
# Ships the browser build. Builds and zips only; add --push to upload.
exec "$(dirname "$0")/tools/ship.sh" "$@"
